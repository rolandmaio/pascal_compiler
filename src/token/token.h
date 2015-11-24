#ifndef LEXER_TOKENS
#define LEXER_TOKENS

#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<list>
using std::list;
#include "tag.h"
#include "../type/kind.h"
#include "../goto/goto.h"

class Token {

    public:
        Token() : tag(BAD) {}
        Token(Tag t) : tag(t) {}
        Token(Tag t, string l) : tag(t), lexeme(l) {}
        Token(Tag t, string l, string p) : tag(t), lexeme(l), prevLab(p), seen(false) {}
        Token(Tag t, int v) : tag(t), value(v) {}
        Token(Tag t, float v) : tag(t), realValue(v) {}
        Token(Tag t, string l, Kind k, size_t a)
            : tag(t), lexeme(l), kind(k), address(a) {}
        Tag getTag(){ return tag; }
        string getLexeme(){ return lexeme; }
        string getPrevLab(){ return prevLab; }
        int getValue(){ return value; }
        float getRealValue(){ return realValue; }
        Kind getKind(){ return kind; }
        size_t getAddress(){ return address; }
        void setAddress(size_t addr){ address = addr; }
        void addGoto(Goto g){ listOfGotos.push_back(g); }
        bool getSeen(){ return seen; }
        void setSeen(bool b){ seen = b; }
        list<Goto> getListOfGotos(){ return listOfGotos; }

    private:
        Tag tag;
        string lexeme, str_val, prevLab;
        Kind kind;
        int value;
        float realValue;
        size_t address;
        list<Goto> listOfGotos;
        bool seen;

};

extern vector<pair<string, Token> > defaultTokens;

#endif
