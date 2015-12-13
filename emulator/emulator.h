#ifndef EMULATOR
#define EMULATOR

#include<cstdio>
using std::size_t;
#include "stackelement.h"
#include "../compiler/src/opcode/opcode.h"

class Emulator{

    public:
        Emulator(const char* fileName);
        void run();

    private:
        char *file_data,
             *code_ptr,
             *data_ptr;
        StackElement stack[1 << 10], // Ditto.
                     *stack_ptr = stack,
                     *base_ptr = NULL;
        size_t headerSize;

        void executeInstruction();
        void* getPointer(size_t address);
        size_t readAddress();
        int readIntAddress();

};

#endif
