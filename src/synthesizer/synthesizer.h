#ifndef SYNTHESIZER
#define SYNTHESIZER

#define INITIAL_BUFFER_SIZE (1 << 20) // 1 MiB 1,048,576 Bytes.

#include<cstdlib>
using std::size_t;
#include<string>
using std::string;
#include "../type/type.h"
#include "../token/token.h"
#include "../token/stringtoken.h"
#include "../token/integertoken.h"
#include "../opcode/opcode.h"

class Synthesizer {

    public:
        Synthesizer(string outFileName);
        void genPrintCode(Type t);
        void genPrintLn();
        void writeToFile();
        void genOpCode(Opcode opcode);
        void genAddress(size_t addr);
        void writeFile();
        size_t writeStringLiteralToHeader(StringToken strtok);
        size_t writeUnsignedIntegerLiteralToHeader(Token tok);
        Type genAdditionCode(Type t1, Type t2);

    private:
        string outFileName;
        void *headerBuffer,
             *headerPtr,
             *instructionBuffer,
             *instructionPtr;
        size_t headerSize,
               instructionSize;

};

#endif
