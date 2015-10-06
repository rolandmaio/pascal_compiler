#ifndef LEXER_REAL_TOKEN
#define LEXER_REAL_TOKEN

#include "token.h"

class RealToken : public Token {

    public:
        RealToken(double value) : Token(REAL), value(value){};
        double getValue(){ return value; }

    private:
        double value;

};

#endif
