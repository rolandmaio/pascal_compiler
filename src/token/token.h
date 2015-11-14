#ifndef LEXER_TOKENS
#define LEXER_TOKENS

#include<string>
using std::string;
#include<vector>
#include<utility>
#include "tag.h"
using namespace std;

class Token {

    public:
        Token() : tag(BAD) {}
        Token(Tag t) : tag(t) {}
        Token(Tag t, string l) : tag(t), lexeme(l) {}
        Token(Tag t, int v) : tag(t), value(v) {}
        Tag getTag(){ return tag; }
        string getLexeme(){ return lexeme; }
        int getValue(){ return value; }

    private:
        Tag tag;
        string lexeme;
        int value;

};

extern vector<pair<string, Token> > defaultTokens;

#endif
