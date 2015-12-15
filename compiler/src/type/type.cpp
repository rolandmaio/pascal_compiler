#ifndef TYPE_IMPL
#define TYPE_IMPL

#include "type.h"

Type::Type(string kindName){
    if(kindName == "string"){
        kind = Kind::STRING;
    } else if(kindName == "integer"){
        kind = Kind::INTEGER;
    } else if(kindName == "real"){
        kind = Kind::REAL;
    } else if(kindName == "boolean"){
        kind = Kind::BOOLEAN;
    } else if(kindName == "char"){
        kind = Kind::CHAR;
    } else {
        throw "Type(string kindName) not implemented for: " + kindName;
    }
}

Type::Type(Kind k, Kind index_k, int low, int high){
    kind = k;
    index_kind = index_k;
    int_low = low;
    int_high = high;
}

#endif
