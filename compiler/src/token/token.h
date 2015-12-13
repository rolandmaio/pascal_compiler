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
#include<unordered_map>
using std::unordered_map;
#include "tag.h"
#include "../type/kind.h"
#include "../goto/goto.h"

enum class ParameterType {

    UNDEFINED,
    VALUE,
    REFERENCE,
    PROCEDURE,
    FUNCTION

};

class Token {

    public:
        Token() : tag(BAD) {}
        Token(Tag t) : tag(t) {}
        Token(Tag t, string l) : tag(t), lexeme(l) {}
        Token(Tag t, string l, unordered_map<string, Token>* symbol_table)
            : tag(t), lexeme(l), local_symbol_table(symbol_table) {}
        Token(Tag t, string l, string p) : tag(t), lexeme(l), prevLab(p), seen(false) {}
        Token(Tag t, int v) : tag(t), value(v) {}
        Token(Tag t, float v) : tag(t), realValue(v) {}
        Token(Tag t, string l, Kind k, size_t a)
            : tag(t), lexeme(l), kind(k), address(a) { pt = ParameterType::VALUE; }
        Token(Tag t, string l, Kind k, size_t a, ParameterType p)
            : tag(t), lexeme(l), kind(k), address(a), pt(p) {}
        Token(Tag t, string l, Kind k, int a)
            : tag(t), lexeme(l), kind(k), reladdress(a) { }
        Token(Tag t, string l, Kind elem_k, Kind index_k, int low, int high, size_t addr)
            : tag(t), lexeme(l), elem_k(elem_k), index_k(index_k),
              int_low(low), int_high(high), address(addr) { kind = ARRAY_K; }
        Tag getTag(){ return tag; }
        string getLexeme(){ return lexeme; }
        string getPrevLab(){ return prevLab; }
        int getValue(){ return value; }
        int getIntLow(){ return int_low; }
        int getIntHigh(){ return int_high; }
        float getRealValue(){ return realValue; }
        Kind getKind(){ return kind; }
        Kind getIndexKind(){ return index_k; }
        Kind getElemKind(){ return elem_k; }
        size_t getAddress(){ return address; }
        void setAddress(size_t addr){ address = addr; }
        void addGoto(Goto g){ listOfGotos.push_back(g); }
        bool getSeen(){ return seen; }
        void setSeen(bool b){ seen = b; }
        int getRelAddress(){ return reladdress; }
        void setRelAddress(int a){ reladdress = a; }
        int getNumParams(){ return num_params; }
        void setNumParams(int np){ num_params = np; }
        list<Goto> getListOfGotos(){ return listOfGotos; }
        unordered_map<string, Token> *getLocalSymbolTable(){ return local_symbol_table; }
        void addParameter(Token* tk_ptr){ listOfParameters.push_back(tk_ptr); }

    private:
        Tag tag;
        string lexeme, str_val, prevLab;
        Kind kind, index_k, elem_k;
        int value, int_low, int_high, reladdress, num_params;
        float realValue;
        size_t address;
        list<Goto> listOfGotos;
        list<size_t> listOfCalls;
        list<Token*> listOfParameters;
        unordered_map<string, Token> *local_symbol_table;
        bool seen;
        ParameterType pt = ParameterType::UNDEFINED;

};

extern vector<pair<string, Token> > defaultTokens;

#endif
