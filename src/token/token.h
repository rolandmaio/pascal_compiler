#ifndef LEXER_TOKENS
#define LEXER_TOKENS

#include<string>
#include<vector>
#include<utility>
#include "tag.h"
using namespace std;

class Token {

    public:
        Token() : tag(BAD) {}
        Token(Tag t) : tag(t) {}
        Tag getTag(){ return tag; }

    private:
        Tag tag;

};

extern vector<pair<string, Token> > defaultTokens;

#endif
