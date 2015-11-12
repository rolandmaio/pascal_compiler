#ifndef LEXER
#define LEXER

#include<string>
using std::string;
#include<unordered_map>
using std::unordered_map;
#include "../token/token.h"
#include "commenttype.h"

#define LEXER_EOF 257
#define MAX_IDLEN 255

class Lexer{

    public:
        Token getToken();
        Lexer(const char* sourceFile, unordered_map<string, Token> *symboltable);
        Lexer(){}

    private:
        // Helper functions.
        void stripComments(CommentType commentType);
        void advanceScanp();

        // Members.
        unordered_map<string, Token> *symboltable;
        unsigned int curline;
        unsigned int curcol;
        const char* scanp;
        char curname[MAX_IDLEN + 1]; // + 1 for the null character \0

};

#endif
