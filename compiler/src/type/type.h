#ifndef TYPE
#define TYPE

#include<string>
using std::string;
#include "kind.h"

class Type {

    public:
        Type() : kind(Kind::UNDEFINED) {}
        Type(Kind k) : kind(k) {}
        Type(Kind k, Kind idx_k) : kind(k), index_kind(idx_k) {}
        Type(string kindName);
        Type(Kind k, Kind index_k, int low, int high);
        Type(Kind k, Kind index_k, char low, char high);
        Kind getKind(){ return kind; }
        int getIntLow(){ return int_low; }
        int getIntHigh(){ return int_high; }
        char getCharLow(){ return char_low; }
        char getCharHigh(){ return char_high; }
        void setElemKind(Kind k){ elem_kind = k; }
        void setKind(Kind k){ kind = k; }
        Kind getIndexKind(){ return index_kind; }
        Kind getElemKind(){ return elem_kind; }

    private:
        Kind kind,
             index_kind,
             elem_kind;
        int int_low,
            int_high;
        char char_low,
             char_high;

};

#endif
