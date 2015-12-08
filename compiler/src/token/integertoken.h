#ifndef LEXER_INTEGER_TOKEN
#define LEXER_INTEGER_TOKEN

#include "token.h"

class IntegerToken : public Token{

    public:
        IntegerToken(int value) : Token(INT), value(value){};
        int getValue(){ return value; }

    private:
        int value;

};

#endif
