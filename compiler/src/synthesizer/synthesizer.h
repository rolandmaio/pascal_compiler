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
#include "../type/kind.h"

class Synthesizer {

    public:
        Synthesizer(string outFileName);
        void genPrintCode(Type t);
        void genPrintLn();
        void writeToFile();
        void genOpCode(Opcode opcode);
        void genPushVarOpcode(Kind k);
        void genPushVarBackwardsOpcode(Kind k);
        void genPushLocalVarOpcode(Kind k);
        void genPopVarOpcode(Kind k);
        void genAddress(size_t addr);
        void genAddress(int reladdr);
        void genBoolean(bool val);
        void writeFile();
        void writeToInstructions(size_t s);
        void writeToInstructions(char c);
        void writeKind(Kind k);
        size_t writeStringLiteralToHeader(StringToken strtok);
        size_t allocateStringVariableInHeader();
        size_t allocatIntegerVariableInHeader();
        size_t allocateCharVariableInHeader();
        size_t allocateRealVariableInHeader();
        size_t allocateBooleanVariableInHeader();
        size_t allocateArrayVariableInHeader(Type t);
        size_t writeUnsignedIntegerLiteralToHeader(Token tok);
        size_t writeUnsignedRealLiteralToHeader(Token tok);
        Type genAdditionCode(Type t1, Type t2);
        Type genMultiplicationCode(Type t1, Type t2);
        Type genSubtractionCode(Type t1, Type t2);
        Type genEqualityCode(Type t);
        Type genEqualityCode(Type t1, Type t2);
        Type genInequalityCode(Type t);
        Type genInequalityCode(Type t1, Type t2);
        Type genLessThanCode(Type t);
        Type genLessThanCode(Type t1, Type t2);
        Type genGreaterThanCode(Type t);
        Type genGreaterThanCode(Type t1, Type t2);
        Type genLessOrEqualCode(Type t);
        Type genLessOrEqualCode(Type t1, Type t2);
        Type genGreaterOrEqualCode(Type t);
        Type genGreaterOrEqualCode(Type t1, Type t2);
        size_t makePlaceHolderAddress();
        void fillPlaceHolderAddress(size_t placeHolder);
        void fillPlaceHolderAddress(size_t placeHolder, size_t address);
        size_t getVariableAddress();
        size_t getInstructionAddress();
        void genAddOne(Kind k);
        void genSubOne(Kind k);

    private:
        string outFileName;
        void *headerBuffer,
             *headerPtr,
             *instructionBuffer,
             *instructionPtr;
        size_t headerSize,
               instructionSize,
               variableAddress;

};

#endif
