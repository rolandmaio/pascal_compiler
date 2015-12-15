#ifndef EMULATOR_IMPL
#define EMULATOR_IMPL

#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include<fstream>
using std::ifstream;
using std::istreambuf_iterator;
#include "emulator.h"
#include "../compiler/src/type/kind.h"

Emulator::Emulator(const char* fileName){

    ifstream file(fileName);
    string program((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file_data = (char*) program.c_str();
    code_ptr = file_data;
    data_ptr = file_data;
    headerSize = readAddress();
    code_ptr = file_data + headerSize;

}

void Emulator::run(){

    while((Opcode) *code_ptr != TERMINATE_PROGRAM){
        executeInstruction();
    }

}

void Emulator::executeInstruction(){
    int x, y, *int_ptr, int_addr;
    float fx, fy, *float_ptr;
    char *addr, *char_ptr, **char_ptr_ptr, ca, cb, char_idx_low, char_idx;
    bool bu, bv, *bool_ptr;
    size_t address, idx, idx_low, elem_size;
    StackElement temp_stackelement;
    switch((Opcode) *code_ptr){
        case PUSH_STRING:
            code_ptr = code_ptr + 1;
            stack_ptr->string_ptr = (char*) getPointer(readAddress());
            ++stack_ptr;
            break;
        case PUSH_INT:
            code_ptr = code_ptr + 1;
            stack_ptr->integer = *((int*) getPointer(readAddress()));
            ++stack_ptr;
            break;
        case PUSH_INT_BACKWARDS:
            code_ptr = code_ptr + 1;
            stack_ptr->integer = *((int*) getPointer((stack_ptr - 1)->address));
            ++stack_ptr;
            break;
        case PUSH_LOCAL_INT:
            code_ptr = code_ptr + 1;
            int_addr = readIntAddress();
            if(int_addr < 0){
                --int_addr;
            }
            stack_ptr->integer = (base_ptr + int_addr)->integer;
            ++stack_ptr;
            break;
        case PUSH_REAL:
            code_ptr = code_ptr + 1;
            stack_ptr->real = *((float*) getPointer(readAddress()));
            ++stack_ptr;
            break;
        case PUSH_BOOLEAN:
            code_ptr = code_ptr + 1;
            stack_ptr->boolean = *(bool*)code_ptr;
            code_ptr = code_ptr + sizeof(bool);
            ++stack_ptr;
            break;
        case PUSH_ADDRESS:
            code_ptr = code_ptr + 1;
            stack_ptr->address = readAddress();
            ++stack_ptr;
            break;
        case PUSH_LOCAL_ADDRESS:
            code_ptr = code_ptr + 1;
            int_addr = readIntAddress();
            if(int_addr < 0){
                --int_addr;
            }
            stack_ptr->int_address = int_addr;
            ++stack_ptr;
            break;
        case PUSH_ARRAY_ADDRESS:
            code_ptr = code_ptr + 1;
            switch((Kind) *code_ptr){
                case Kind::INTEGER:
                    code_ptr = code_ptr + sizeof(Kind);
                    idx_low = readAddress();
                    elem_size = readAddress();
                    address = readAddress();
                    idx = (size_t)(stack_ptr - 1)->integer;
                    --stack_ptr;
                    stack_ptr->address = address + (idx - idx_low)*elem_size;
                    ++stack_ptr;
                    break;
                case Kind::CHAR:
                    code_ptr = code_ptr + sizeof(Kind);
                    char_idx_low = *(char*) code_ptr;
                    code_ptr = code_ptr + sizeof(char);
                    elem_size = readAddress();
                    address = readAddress();
                    char_idx = (size_t)(stack_ptr - 1)->string_ptr[0];
                    --stack_ptr;
                    stack_ptr->address = address + (char_idx - char_idx_low)*elem_size;
                    ++stack_ptr;
                    break;
                case Kind::BOOLEAN:
                    code_ptr = code_ptr + sizeof(Kind);
                    elem_size = readAddress();
                    address = readAddress();
                    --stack_ptr;
                    bu = stack_ptr->boolean;
                    stack_ptr->address = address + (bu ? elem_size : 0);
                    ++stack_ptr;
                    break;
                default:
                    throw "Array index type not implemented!";
                    break;
            }
            break;
        case WRITE_INT:
            code_ptr = code_ptr + 1;
            --stack_ptr;
            printf("%d", stack_ptr->integer);
            break;
        case WRITE_CHAR:
            code_ptr = code_ptr + 1;
            --stack_ptr;
            printf("%c", stack_ptr->string_ptr[0]);
            break;
        case WRITE_REAL:
            code_ptr = code_ptr + 1;
            --stack_ptr;
            printf("%f", stack_ptr->real);
            break;
        case WRITE_BOOLEAN:
            code_ptr = code_ptr + 1;
            --stack_ptr;
            printf(stack_ptr->boolean ? "True" : "False");
            break;
        case WRITE_STRING:
            code_ptr = code_ptr + 1;
            --stack_ptr;
            printf("%s", stack_ptr->string_ptr);
            break;
        case WRITE_LINE:
            code_ptr = code_ptr + 1;
            printf("\n");
            break;
        case INTEGER_ADDITION:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->integer = x + y;
            ++stack_ptr;
            break;
        case INTEGER_MULTIPLICATION:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->integer = x * y;
            ++stack_ptr;
            break;
        case INTEGER_DIVISION:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->integer = x / y;
            ++stack_ptr;
            break;
        case INTEGER_SUBTRACTION:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->integer = x - y;
            ++stack_ptr;
            break;
        case INTEGER_SUB_ONE:
            code_ptr = code_ptr + 1;
            x = (stack_ptr - 1)->integer;
            (stack_ptr - 1)->integer = x - 1;
            break;
        case INTEGER_ADD_ONE:
            code_ptr = code_ptr + 1;
            x = (stack_ptr - 1)->integer;
            (stack_ptr - 1)->integer = x + 1;
            break;
        case CHAR_ADD_ONE:
            code_ptr = code_ptr + 1;
            ca = (stack_ptr - 1)->string_ptr[0];
            (stack_ptr - 1)->string_ptr[0] = ca + 1;
            break;
        case CHAR_SUB_ONE:
            code_ptr = code_ptr + 1;
            ca = (stack_ptr - 1)->string_ptr[0];
            (stack_ptr - 1)->string_ptr[0] = ca - 1;
            break;
        case EQ_INTEGER:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->boolean = x == y;
            ++stack_ptr;
            break;
        case NEQ_INTEGER:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->boolean = x != y;
            ++stack_ptr;
            break;
        case LT_INTEGER:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->boolean = x < y;
            ++stack_ptr;
            break;
        case GT_INTEGER:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->boolean = x > y;
            ++stack_ptr;
            break;
        case LEQ_INTEGER:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->boolean = x <= y;
            ++stack_ptr;
            break;
        case GEQ_INTEGER:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->boolean = x >= y;
            ++stack_ptr;
            break;
        case EQ_REAL:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->boolean = fx == fy;
            ++stack_ptr;
            break;
        case NEQ_REAL:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->boolean = fx != fy;
            ++stack_ptr;
            break;
        case LT_REAL:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->boolean = fx < fy;
            ++stack_ptr;
            break;
        case GT_REAL:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->boolean = fx > fy;
            ++stack_ptr;
            break;
        case LEQ_REAL:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->boolean = fx <= fy;
            ++stack_ptr;
            break;
        case GEQ_REAL:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->boolean = fx >= fy;
            ++stack_ptr;
            break;
        case EQ_CHAR:
            code_ptr = code_ptr + 1;
            cb = (--stack_ptr)->string_ptr[0];
            ca = (--stack_ptr)->string_ptr[0];
            stack_ptr->boolean = ca == cb;
            ++stack_ptr;
            break;
        case NEQ_CHAR:
            code_ptr = code_ptr + 1;
            cb = (--stack_ptr)->string_ptr[0];
            ca = (--stack_ptr)->string_ptr[0];
            stack_ptr->boolean = ca != cb;
            ++stack_ptr;
            break;
        case LT_CHAR:
            code_ptr = code_ptr + 1;
            cb = (--stack_ptr)->string_ptr[0];
            ca = (--stack_ptr)->string_ptr[0];
            stack_ptr->boolean = ca < cb;
            ++stack_ptr;
            break;
        case GT_CHAR:
            code_ptr = code_ptr + 1;
            cb = (--stack_ptr)->string_ptr[0];
            ca = (--stack_ptr)->string_ptr[0];
            stack_ptr->boolean = ca > cb;
            ++stack_ptr;
            break;
        case LEQ_CHAR:
            code_ptr = code_ptr + 1;
            cb = (--stack_ptr)->string_ptr[0];
            ca = (--stack_ptr)->string_ptr[0];
            stack_ptr->boolean = ca <= cb;
            ++stack_ptr;
            break;
        case GEQ_CHAR:
            code_ptr = code_ptr + 1;
            cb = (--stack_ptr)->string_ptr[0];
            ca = (--stack_ptr)->string_ptr[0];
            stack_ptr->boolean = ca >= cb;
            ++stack_ptr;
            break;
        case REAL_ADDITION:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->real = fx + fy;
            ++stack_ptr;
            break;
        case REAL_MULTIPLICATION:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->real = fx * fy;
            ++stack_ptr;
            break;
        case REAL_DIVISION:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->real = fx / fy;
            ++stack_ptr;
            break;
        case REAL_SUBTRACTION:
            code_ptr = code_ptr + 1;
            fy = (--stack_ptr)->real;
            fx = (--stack_ptr)->real;
            stack_ptr->real = fx - fy;
            ++stack_ptr;
            break;
        case EQ_BOOLEAN:
            code_ptr = code_ptr + 1;
            bu = (stack_ptr - 2)->boolean;
            bv = (stack_ptr - 1)->boolean;
            (stack_ptr - 2)->boolean = bu == bv;
            --stack_ptr;
            break;
        case NEQ_BOOLEAN:
            code_ptr = code_ptr + 1;
            bu = (stack_ptr - 2)->boolean;
            bv = (stack_ptr - 1)->boolean;
            (stack_ptr - 2)->boolean = bu != bv;
            --stack_ptr;
            break;
        case SWAP:
            code_ptr = code_ptr + 1;
            *stack_ptr = *(stack_ptr - 1);          // Save y.
            *(stack_ptr - 1) = *(stack_ptr - 2);    // Store x in y.
            *(stack_ptr - 2) = *stack_ptr;          // Store y in x.
            break;
        case CONVERT_INTEGER_TO_REAL:
            code_ptr = code_ptr + 1;
            (stack_ptr - 1)->real = (stack_ptr - 1)->integer;
            break;
        case INTEGER_MOD_DIVISION:
            code_ptr = code_ptr + 1;
            y = (--stack_ptr)->integer;
            x = (--stack_ptr)->integer;
            stack_ptr->integer = x % y;
            ++stack_ptr;
            break;
        case POP_STRING:
            code_ptr = code_ptr + 1;
            char_ptr_ptr = (char**) getPointer((stack_ptr - 2)->address);
            *char_ptr_ptr = (stack_ptr - 1)->string_ptr;
            stack_ptr = stack_ptr - 2;
            break;
        case POP_INTEGER:
            code_ptr = code_ptr + 1;
            int_ptr = (int*) getPointer((stack_ptr - 2)->address);
            *int_ptr = (stack_ptr - 1)->integer;
            stack_ptr = stack_ptr - 2;
            break;
        case POP_CHAR:
            code_ptr = code_ptr + 1;
            char_ptr = (char*) getPointer((stack_ptr - 2)->address);
            *char_ptr = ((stack_ptr - 1)->string_ptr)[0];
            stack_ptr = stack_ptr - 2;
            break;
        case POP_LOCAL_INTEGER:
            code_ptr = code_ptr + 1;
            x = (--stack_ptr)->integer;
            int_addr = (--stack_ptr)->int_address;
            (base_ptr + int_addr)->integer = x;
            break;
        case POP_REAL:
            code_ptr = code_ptr + 1;
            float_ptr = (float*) getPointer((stack_ptr - 2)->address);
            *float_ptr = (stack_ptr - 1)->real;
            stack_ptr = stack_ptr - 2;
            break;
        case POP_BOOLEAN:
            code_ptr = code_ptr + 1;
            bool_ptr = (bool*) getPointer((stack_ptr - 2)->address);
            *bool_ptr = (stack_ptr - 1)->boolean;
            stack_ptr = stack_ptr - 2;
            break;
        case PUSH_STRING_VAR:
            code_ptr = code_ptr + 1;
            stack_ptr->string_ptr = *(char**) getPointer(readAddress());
            ++stack_ptr;
            break;
        case PUSH_CHAR_VAR:
            code_ptr = code_ptr + 1;
            stack_ptr->string_ptr = (char*) getPointer(readAddress());
            ++stack_ptr;
            break;
        case PUSH_BOOLEAN_VAR:
            code_ptr = code_ptr + 1;
            stack_ptr->boolean = *(bool*) getPointer(readAddress());
            ++stack_ptr;
            break;
        case JUMP_FALSE:
            code_ptr = code_ptr + 1;
            if((stack_ptr - 1)->boolean){
                readAddress();
            } else {
                address = headerSize + readAddress();
                code_ptr = file_data + address;
            }
            --stack_ptr;
            break;
        case JUMP_TRUE:
            code_ptr = code_ptr + 1;
            if(!(stack_ptr - 1)->boolean){
                readAddress();
            } else {
                address = headerSize + readAddress();
                code_ptr = file_data + address;
            }
            --stack_ptr;
            break;
        case JUMP:
            code_ptr = code_ptr + 1;
            address = headerSize + readAddress();
            code_ptr = file_data + address;
            break;
        case CALL:
            code_ptr = code_ptr + 1;
            address = headerSize + readAddress();
            stack_ptr->ret_ptr = code_ptr;
            ++stack_ptr;
            stack_ptr->prev_bp = base_ptr;
            base_ptr = stack_ptr;
            ++stack_ptr;
            code_ptr = file_data + address;
            break;
        case RETURN:
            code_ptr = (base_ptr - 1)->ret_ptr;
            // "Deallocate" local variables on stack.
            stack_ptr = base_ptr;
            base_ptr = base_ptr->prev_bp;
            break;
        case POP_STACK_ELEMENTS:
            code_ptr = code_ptr + 1;
            stack_ptr = stack_ptr - (readIntAddress() + 1);
            break;
        case DUPLICATE:
            code_ptr = code_ptr + 1;
            *stack_ptr = *(stack_ptr - 1);
            ++stack_ptr;
            break;
        default:
            cout << "We shouldn't be here. Opcode: " << (Opcode) *code_ptr << endl;
            exit(1);
    }
}

void* Emulator::getPointer(size_t address){
    return (void*) data_ptr + address;
}

/*
 * Precondition: code_ptr points to the first byte of a sequence of sizeof(size_t) bytes
 *               that corresponds to the address of a value, n, in the eml file
 *               header.
 * Postcondition: code_ptr points to the first byte after n in the code array
 *                and the value of n is returned.
 */
size_t Emulator::readAddress(){
    size_t addr = (*((size_t*) code_ptr));
    code_ptr = code_ptr + sizeof(size_t);
    return addr;
}

int Emulator::readIntAddress(){
    int addr = (*((int*) code_ptr));
    code_ptr = code_ptr + sizeof(int);
    return addr;
}

#endif
