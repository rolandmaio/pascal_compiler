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
        Tag getTag(){ return tag; }
        string getLexeme(){ return lexeme; }

    private:
        Tag tag;
        string lexeme;

};

extern vector<pair<string, Token> > defaultTokens;

#endif
