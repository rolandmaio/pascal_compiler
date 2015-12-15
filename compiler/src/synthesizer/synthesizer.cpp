#ifndef SYNTHESIZER_IMPL
#define SYNTHESIZER_IMPL

#include<iostream>
using std::cout;
using std::endl;
#include<cstring>
using std::strlen;
using std::memcpy;
#include<fstream>
using std::ofstream;
#include<cstdlib>
using std::malloc;
#include "synthesizer.h"

#define ADDR_SIZE sizeof(size_t)

Synthesizer::Synthesizer(string outFileName) : outFileName(outFileName){
    headerBuffer = malloc(INITIAL_BUFFER_SIZE);
    headerPtr = headerBuffer;
    headerSize = ADDR_SIZE;
    instructionBuffer = malloc(INITIAL_BUFFER_SIZE);
    instructionPtr = instructionBuffer;
    instructionSize = 0;
}

void Synthesizer::writeFile(){

    cout << "headerSize: " << headerSize << endl;
    genOpCode(TERMINATE_PROGRAM);
    ofstream outFile(outFileName.c_str(), std::ofstream::out | std::ofstream::binary);
    outFile.write((const char*) &headerSize, ADDR_SIZE);
    outFile.write((const char*) headerBuffer, headerSize - ADDR_SIZE);
    outFile.write((const char*) instructionBuffer, instructionSize);
    free(headerBuffer);
    free(instructionBuffer);

}

size_t Synthesizer::writeStringLiteralToHeader(StringToken strtok){
    size_t addr = headerSize,
           size = strlen(strtok.getValue().c_str());
    cout << "strtok.getValue().c_str(): " << strtok.getValue().c_str() << endl;
    strcpy((char*)headerPtr, strtok.getValue().c_str());
    headerPtr = headerPtr + size + 1;
    headerSize += size + 1;
    return addr;
}

size_t Synthesizer::allocateStringVariableInHeader(){
    size_t addr = headerSize,
           size = sizeof(char*);
    headerPtr = headerPtr + size;
    headerSize += size;
    return addr;
}

size_t Synthesizer::allocatIntegerVariableInHeader(){
    size_t addr = headerSize,
           size = sizeof(int);
    headerPtr = headerPtr + size;
    headerSize += size;
    return addr;
}

size_t Synthesizer::allocateCharVariableInHeader(){
    size_t addr = headerSize;
    headerPtr = headerPtr + sizeof(char);
    headerSize += sizeof(char);
    return addr;
}

size_t Synthesizer::allocateRealVariableInHeader(){
    size_t addr = headerSize,
           size = sizeof(float);
    headerPtr = headerPtr + size;
    headerSize += size;
    return addr;
}

size_t Synthesizer::allocateBooleanVariableInHeader(){
    size_t addr = headerSize,
           size = sizeof(bool);
    headerPtr = headerPtr + size;
    headerSize += size;
    return addr;
}

size_t Synthesizer::allocateArrayVariableInHeader(Type t){
    size_t addr = headerSize,
           size;
    switch(t.getElemKind()){
        case Kind::INTEGER:
            size = sizeof(int) * (t.getIntHigh() - t.getIntLow() + 1);
            break;
        default:
            throw "Array variable element type not implemented.";
            break;
    }
    headerPtr = headerPtr + size;
    headerSize += size;
    return addr;
}

size_t Synthesizer::writeUnsignedIntegerLiteralToHeader(Token tok){
    size_t addr = headerSize;
    unsigned int value = tok.getValue();
    cout << "value: " << value << endl;
    memcpy(headerPtr, (void*) &value, sizeof(int));
    headerPtr = headerPtr + sizeof(int);
    headerSize += sizeof(int);
    return addr;
}

size_t Synthesizer::writeUnsignedRealLiteralToHeader(Token tok){
    size_t addr = headerSize;
    float value = tok.getRealValue();
    memcpy(headerPtr, (void*) &value, sizeof(float));
    headerPtr = headerPtr + sizeof(float);
    headerSize += sizeof(float);
    return addr;
}

void Synthesizer::writeKind(Kind k){
    memcpy(instructionPtr, (void*)&k, sizeof(Kind));
    instructionPtr = instructionPtr + sizeof(Kind);
    instructionSize = instructionSize + sizeof(Kind);
}

void Synthesizer::writeToInstructions(size_t s){
    genAddress(s);
}

void Synthesizer::genAddress(size_t addr){
    memcpy(instructionPtr, (void*)&addr, ADDR_SIZE);
    instructionPtr = instructionPtr + ADDR_SIZE;
    instructionSize = instructionSize + ADDR_SIZE;
    variableAddress = addr;
}

void Synthesizer::genAddress(int reladdr){
    memcpy(instructionPtr, (void*)&reladdr, sizeof(int));
    instructionPtr = instructionPtr + sizeof(int);
    instructionSize = instructionSize + sizeof(int);
}

void Synthesizer::genOpCode(Opcode opcode){
    unsigned char chr = opcode;
    memcpy(instructionPtr, (void*)&chr, 1);
    instructionPtr = instructionPtr + 1;
    ++instructionSize;
}

void Synthesizer::genPrintCode(Type t){
    switch(t.getKind()){
        case Kind::INTEGER:
            genOpCode(WRITE_INT);
            break;
        case Kind::REAL:
            genOpCode(WRITE_REAL);
            break;
        case Kind::BOOLEAN:
            genOpCode(WRITE_BOOLEAN);
            break;
        case Kind::STRING:
            genOpCode(WRITE_STRING);
            break;
        case Kind::CHAR:
            genOpCode(WRITE_CHAR);
            break;
        default:
            throw "genPrintCode not implemented for this Type";
            break;
    }
}

void Synthesizer::genPrintLn(){
    genOpCode(WRITE_LINE);
}

Type Synthesizer::genAdditionCode(Type t1, Type t2){
    if(t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::INTEGER){
        genOpCode(INTEGER_ADDITION);
        return Type(Kind::INTEGER);
    }
    if(t1.getKind() == Kind::REAL && t2.getKind() == Kind::REAL){
        genOpCode(REAL_ADDITION);
        return Type(Kind::REAL);
    }
    throw "Failed to look up addition code";
}

Type Synthesizer::genMultiplicationCode(Type t1, Type t2){
    if(t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::INTEGER){
        genOpCode(INTEGER_MULTIPLICATION);
        return Type(Kind::INTEGER);
    }
    if(t1.getKind() == Kind::REAL && t2.getKind() == Kind::REAL){
        genOpCode(REAL_MULTIPLICATION);
        return Type(Kind::REAL);
    }
    throw "Failed to look up multiplication code";
}

Type Synthesizer::genSubtractionCode(Type t1, Type t2){
    if(t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::INTEGER){
        genOpCode(INTEGER_SUBTRACTION);
        return Type(Kind::INTEGER);
    }
    if(t1.getKind() == Kind::REAL && t2.getKind() == Kind::REAL){
        genOpCode(REAL_SUBTRACTION);
        return Type(Kind::REAL);
    }
    throw "Failed to look up subraction code";
}

Type Synthesizer::genEqualityCode(Type t1, Type t2){
    if(t1.getKind() == t2.getKind()){
        return genEqualityCode(t1);
    } else if (t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::REAL){
        genOpCode(SWAP);
        genOpCode(CONVERT_INTEGER_TO_REAL);
        genOpCode(SWAP);
        return genEqualityCode(t2);
    } else if (t1.getKind() == Kind::REAL && t2.getKind() == Kind::INTEGER){
        genOpCode(CONVERT_INTEGER_TO_REAL);
        return genEqualityCode(t1);
    } else {
        throw "Equality comparison between t1 and t2 not implemented";
    }
}

Type Synthesizer::genEqualityCode(Type t){
    switch(t.getKind()){
        case Kind::BOOLEAN:
            genOpCode(EQ_BOOLEAN);
            break;
        case Kind::INTEGER:
            genOpCode(EQ_INTEGER);
            break;
        case Kind::REAL:
            genOpCode(EQ_REAL);
            break;
        case Kind::CHAR:
        case Kind::STRING:
            genOpCode(EQ_CHAR);
            break;
        default:
            throw "Equality comparison not implemented for this Kind.";
    }
    return Type(Kind::BOOLEAN);
}

Type Synthesizer::genInequalityCode(Type t){
    switch(t.getKind()){
        case Kind::BOOLEAN:
            genOpCode(NEQ_BOOLEAN);
            break;
        case Kind::INTEGER:
            genOpCode(NEQ_INTEGER);
            break;
        case Kind::REAL:
            genOpCode(NEQ_REAL);
            break;
        case Kind::CHAR:
        case Kind::STRING:
            genOpCode(NEQ_CHAR);
            break;
        default:
            throw "Inequality not implemented for this type.";
    }
    return Type(Kind::BOOLEAN);
}

Type Synthesizer::genInequalityCode(Type t1, Type t2){
    if(t1.getKind() == t2.getKind()){
        return genInequalityCode(t1);
    } else if (t1.getKind() == Kind::REAL && t2.getKind() == Kind::INTEGER){
        genOpCode(CONVERT_INTEGER_TO_REAL);
        return genInequalityCode(t1);
    } else if (t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::REAL){
        genOpCode(SWAP);
        genOpCode(CONVERT_INTEGER_TO_REAL);
        genOpCode(SWAP);
        return genInequalityCode(t2);
    } else {
        throw "Inequality beetween t1 and t2 not implemented.";
    }
}

Type Synthesizer::genLessThanCode(Type t1, Type t2){
    if(t1.getKind() == t2.getKind()){
        return genLessThanCode(t1);
    } else if (t1.getKind() == Kind::REAL && t2.getKind() == Kind::INTEGER){
        genOpCode(CONVERT_INTEGER_TO_REAL);
        return genLessThanCode(t1);
    } else if (t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::REAL){
        genOpCode(SWAP);
        genOpCode(CONVERT_INTEGER_TO_REAL);
        genOpCode(SWAP);
        return genLessThanCode(t2);
    } else if (t1.getKind() == Kind::CHAR && t2.getKind() == Kind::STRING){
        return genLessThanCode(t1);
    } else {
        throw "Less than between t1 and t2 not implemented.";
    }
}

Type Synthesizer::genLessThanCode(Type t){
    switch(t.getKind()){
        case Kind::INTEGER:
            genOpCode(LT_INTEGER);
            break;
        case Kind::REAL:
            genOpCode(LT_REAL);
            break;
        case Kind::CHAR:
        case Kind::STRING:
            genOpCode(LT_CHAR);
            break;
        default:
            throw "Less than not implemented for this type.";
    }
    return Type(Kind::BOOLEAN);
}

Type Synthesizer::genGreaterThanCode(Type t){
    switch(t.getKind()){
        case Kind::INTEGER:
            genOpCode(GT_INTEGER);
            break;
        case Kind::REAL:
            genOpCode(GT_REAL);
            break;
        case Kind::CHAR:
        case Kind::STRING:
            genOpCode(GT_CHAR);
            break;
        default:
            throw "Greater than not implemented for this type.";
    }
    return Type(Kind::BOOLEAN);
}

Type Synthesizer::genGreaterThanCode(Type t1, Type t2){
    if(t1.getKind() == t2.getKind()){
        return genGreaterThanCode(t1);
    } else if (t1.getKind() == Kind::REAL && t2.getKind() == Kind::INTEGER){
        genOpCode(CONVERT_INTEGER_TO_REAL);
        return genGreaterThanCode(t1);
    } else if (t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::REAL){
        genOpCode(SWAP);
        genOpCode(CONVERT_INTEGER_TO_REAL);
        genOpCode(SWAP);
        return genGreaterThanCode(t2);
    } else if (t1.getKind() == Kind::CHAR && t2.getKind() == Kind::STRING){
        return genGreaterThanCode(t1);
    } else {
        throw "Greater than between t1 and t2 not implemented.";
    }
}

Type Synthesizer::genLessOrEqualCode(Type t){
    switch(t.getKind()){
        case Kind::INTEGER:
            genOpCode(LEQ_INTEGER);
            break;
        case Kind::REAL:
            genOpCode(LEQ_REAL);
            break;
        case Kind::CHAR:
        case Kind::STRING:
            genOpCode(LEQ_CHAR);
            break;
        default:
            throw "Less or equal not implemented for this type.";
    }
    return Type(Kind::BOOLEAN);
}

Type Synthesizer::genLessOrEqualCode(Type t1, Type t2){
    if(t1.getKind() == t2.getKind()){
        return genLessOrEqualCode(t1);
    } else if (t1.getKind() == Kind::REAL && t2.getKind() == Kind::INTEGER){
        genOpCode(CONVERT_INTEGER_TO_REAL);
        return genLessOrEqualCode(t1);
    } else if (t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::REAL){
        genOpCode(SWAP);
        genOpCode(CONVERT_INTEGER_TO_REAL);
        genOpCode(SWAP);
        return genLessOrEqualCode(t2);
    } else if (t1.getKind() == Kind::CHAR && t2.getKind() == Kind::STRING){
        return genLessOrEqualCode(t1);
    } else {
        throw "Less or equal between t1 and t2 not implemented.";
    }
}

Type Synthesizer::genGreaterOrEqualCode(Type t){
    switch(t.getKind()){
        case Kind::INTEGER:
            genOpCode(GEQ_INTEGER);
            break;
        case Kind::REAL:
            genOpCode(GEQ_REAL);
            break;
        case Kind::CHAR:
        case Kind::STRING:
            genOpCode(GEQ_CHAR);
            break;
        default:
            throw "Greater or equal not implemented for this type.";
    }
    return Type(Kind::BOOLEAN);
}

Type Synthesizer::genGreaterOrEqualCode(Type t1, Type t2){
    if(t1.getKind() == t2.getKind()){
        return genGreaterOrEqualCode(t1);
    } else if (t1.getKind() == Kind::REAL && t2.getKind() == Kind::INTEGER){
        genOpCode(CONVERT_INTEGER_TO_REAL);
        return genGreaterOrEqualCode(t1);
    } else if (t1.getKind() == Kind::INTEGER && t2.getKind() == Kind::REAL){
        genOpCode(SWAP);
        genOpCode(CONVERT_INTEGER_TO_REAL);
        genOpCode(SWAP);
        return genGreaterOrEqualCode(t2);
    } else if (t1.getKind() == Kind::CHAR && t2.getKind() == Kind::STRING){
        return genGreaterOrEqualCode(t1);
    } else {
        throw "Greater or equal between t1 and t2 not implemented.";
    }
}

void Synthesizer::genPushVarOpcode(Kind k){
    switch(k){
        case Kind::STRING:
            genOpCode(PUSH_STRING_VAR);
            break;
        case Kind::INTEGER:
            genOpCode(PUSH_INT);
            break;
        case Kind::REAL:
            genOpCode(PUSH_REAL);
            break;
        case Kind::BOOLEAN:
            genOpCode(PUSH_BOOLEAN_VAR);
            break;
        case Kind::ARRAY:
            genOpCode(PUSH_ARRAY_VAR);
            break;
        case Kind::CHAR:
            genOpCode(PUSH_CHAR_VAR);
            break;
        default:
            throw "Push Var Opcode not implemented for this kind";
    }
}

void Synthesizer::genPushLocalVarOpcode(Kind k){
    switch(k){
        case Kind::INTEGER:
            genOpCode(PUSH_LOCAL_INT);
            break;
        default:
            throw "No opcode for this local variable kind";
            break;
    }
}

void Synthesizer::genPushVarBackwardsOpcode(Kind k){
    switch(k){
        case Kind::INTEGER:
            genOpCode(PUSH_INT_BACKWARDS);
            break;
        default:
            throw "Push Var Backwards Opcode not implemented for this kind";
    }
}

void Synthesizer::genPopVarOpcode(Kind k){
    switch(k){
        case Kind::INTEGER:
            genOpCode(POP_INTEGER);
            break;
        case Kind::CHAR:
            genOpCode(POP_CHAR);
            break;
        default:
            throw "genPopVarOpcode not implemented for this kind";
    }
}

void Synthesizer::genBoolean(bool val){
    memcpy(instructionPtr, (void*)&val, sizeof(bool));
    instructionPtr = instructionPtr + sizeof(bool);
    instructionSize = instructionSize + sizeof(bool);
}

size_t Synthesizer::makePlaceHolderAddress(){
    size_t addr = instructionSize;
    instructionSize = instructionSize + ADDR_SIZE;
    instructionPtr = instructionPtr + ADDR_SIZE;
    return addr;
}

void Synthesizer::fillPlaceHolderAddress(size_t placeHolder){
    void *hole = instructionBuffer + placeHolder;
    memcpy(hole, (void*)&instructionSize, ADDR_SIZE);
}

void Synthesizer::fillPlaceHolderAddress(size_t placeHolder, size_t address){
    void *hole = instructionBuffer + placeHolder;
    memcpy(hole, (void*)&address, ADDR_SIZE);
}

size_t Synthesizer::getVariableAddress(){
    return variableAddress;
}

size_t Synthesizer::getInstructionAddress(){
    return instructionSize;
}

void Synthesizer::genAddOne(Kind k){
    switch(k){
        case Kind::INTEGER:
            genOpCode(INTEGER_ADD_ONE);
            break;
        case Kind::CHAR:
            genOpCode(CHAR_ADD_ONE);
            break;
        default:
            throw "genAddOne not implemented for this kind";
    }
}

void Synthesizer::genSubOne(Kind k){
    switch(k){
        case Kind::INTEGER:
            genOpCode(INTEGER_SUB_ONE);
            break;
        case Kind::CHAR:
            genOpCode(CHAR_SUB_ONE);
            break;
        default:
            throw "genSubOne not implemented for this kind";
    }
}

#endif
