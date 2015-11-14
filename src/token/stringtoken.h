#ifndef LEXER_STRING_TOKEN
#define LEXER_STRING_TOKEN

#include<string>
using std::string;
#include "token.h"
#include "tag.h"

class StringToken : public Token {

    public:
        StringToken(string value) : Token(STRING, value), value(value){};
        string getValue(){ return value; }

    private:
        string value;

};

#endif
