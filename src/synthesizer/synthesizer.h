#ifndef SYNTHESIZER
#define SYNTHESIZER

#include<string>
using std::string;
#include "../type/type.h"

class Synthesizer {

    public:
        Synthesizer(string outFileName);
        void genPrintCode(Type t);
        void genPrintLn();
        void writeToFile();

    private:
        string outFileName;
        char *headerBuffer,
             *headerPtr,
             *instructionBuffer,
             *instructionPtr;

};

#endif
