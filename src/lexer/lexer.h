#ifndef LEXER
#define LEXER

#include<string>
#include<vector>
#include<unordered_map>
#include "../token/token.h"
#include "commenttype.h"

#define LEXER_EOF 257
#define MAX_IDLEN 255

using namespace std;

class Lexer{

    public:
        Token getToken();
        Lexer(const char* scanp);

    private:
        // Helper functions.
        void stripComments(CommentType commentType);
        void advanceScanp();

        // Members.
        unordered_map<string, Token> lexemes;
        unsigned int curline;
        unsigned int curcol;
        const char* scanp;
        char curname[MAX_IDLEN + 1]; // + 1 for the null character \0

};

#endif
