#ifndef TYPE
#define TYPE

#include<string>
using std::string;
#include "kind.h"

class Type {

    public:
        Type(Kind k) : kind(k) {}

    private:
        Kind kind;

};

#endif
