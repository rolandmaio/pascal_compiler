#ifndef PARSETREELOGGER
#define PARSETREELOGGER

#include<cstdlib>
using std::size_t;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<fstream>
using std::ofstream;

/*
 * The ParseTreeLogger class provides logging facilities for building an xml
 * representation of the parse tree built, at least conceptually, by the
 * compiler as it parses the source program.
 *
 * The idea is that knowing which nonterminals in the parse tree are actually
 * being used can help focus development efforts.
 */
class ParseTreeLogger {

    public:
        ParseTreeLogger(string sourceProgramFile);
        ~ParseTreeLogger();
        void logEntry(string functionName);
        void logExit(string functionName);

    private:
        ofstream logFile;
        string logFileName;
        string sourceProgramFile;
        size_t indent;
        vector<string> openTagsStack;

        void openFile();
        void closeFile();
        void printHeader();
        void printOpeningTag(string tagName);
        void printClosingTag(string tagName);
        void printIndent();
        void incrementIndent();
        void decrementIndent();
        bool matchTagStack(string tagName);
        void printErrorTag(string tagName);
        string computeFileName();
        string currentDateTime();

};

#endif
