#ifndef SYMBOLTABLEMANAGER
#define SYMBOLTABLEMANAGER

#define CAPACITY 2 << 4

#include<vector>
using std::vector;
#include<unordered_map>
using std::unordered_map;

#include "../token/token.h"

class SymbolTableManager{
    public:
        unordered_map<string, Token>* allocateSymbolTable(){
            if(index == CAPACITY){
                throw "Not enough symbol tables to allocate.";
            }
            return &(tables[index++]);
        }
    private:
        unordered_map<string, Token> tables[CAPACITY];
        int index = 0;
};

#endif
