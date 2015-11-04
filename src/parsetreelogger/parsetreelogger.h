#ifndef PARSETREELOGGER
#define PARSETREELOGGER

#include<string>;
using std::string;

class ParseTreeLogger {

    public:
        ParseTreeLogger(string sourceProgram);
        void logEntry(string functionName);
        void logExit(string functionName);

    private:

};

#endif
