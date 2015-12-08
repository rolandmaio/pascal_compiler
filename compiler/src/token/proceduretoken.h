#ifndef LEXER_PROCEDURE_TOKEN
#define LEXER_PROCEDURE_TOKEN

#include<string>
using std::string;
#include "token.h"
#include "tag.h"

class ProcedureToken : public Token {

    public:
        ProcedureToken(string lexeme) : Token(TK_A_PROC){ this->lexeme = lexeme; }
        string getLexeme(){ return lexeme; }

    private:
        string lexeme;

};

#endif
