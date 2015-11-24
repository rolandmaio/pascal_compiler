#ifndef TYPE
#define TYPE

#include<string>
using std::string;
#include "kind.h"

class Type {

    public:
        Type() : kind(UNDEFINED_K) {}
        Type(Kind k) : kind(k) {}
        Type(string kindName);
        Kind getKind(){ return kind; }

    private:
        Kind kind;

};

#endif
