#ifndef LEXER_IDENTIFIER_TOKEN
#define LEXER_IDENTIFIER_TOKEN

#include<string>
using std::string;
#include "token.h"
#include "tag.h"

class IdentifierToken : public Token {

    public:
        IdentifierToken(string lexeme) : Token(ID){ this->lexeme = lexeme; };
        string getLexeme(){ return lexeme; }

    private:
        string lexeme;

};

#endif
