#ifndef TYPE_IMPL
#define TYPE_IMPL

#include "type.h"

Type::Type(string kindName){
    if(kindName == "string"){
        kind = STRING_K;
    } else if(kindName == "integer"){
        kind = INTEGER_K;
    } else if(kindName == "real"){
        kind = REAL_K;
    } else if(kindName == "boolean"){
        kind = BOOLEAN_K;
    } else {
        throw "Type(string kindName) not implemented for: " + kindName;
    }
}

#endif
