#ifndef OPCODE
#define OPCODE

enum Opcode{

    WRITE_INT,                  // 0
    WRITE_CHAR,
    WRITE_REAL,
    WRITE_STRING,
    WRITE_BOOLEAN,
    WRITE_LINE,                 // 5

    PUSH_STRING,
    PUSH_INT,
    PUSH_CHAR,
    PUSH_REAL,
    PUSH_BOOLEAN,
    PUSH_ADDRESS,
    PUSH_ARRAY_ADDRESS,
    PUSH_INT_BACKWARDS,
    SWAP,

    PUSH_STRING_VAR,
    PUSH_BOOLEAN_VAR,
    PUSH_ARRAY_VAR,
    PUSH_CHAR_VAR,

    PUSH_LOCAL_INT,
    PUSH_LOCAL_ADDRESS,

    POP_STRING,
    POP_INTEGER,
    POP_CHAR,
    POP_REAL,
    POP_BOOLEAN,

    POP_LOCAL_STRING,
    POP_LOCAL_INTEGER,
    POP_LOCAL_CHAR,
    POP_LOCAL_REAL,
    POP_LOCAL_BOOLEAN,

    INTEGER_ADDITION,
    INTEGER_MULTIPLICATION,
    INTEGER_DIVISION,
    INTEGER_MOD_DIVISION,
    INTEGER_SUBTRACTION,
    INTEGER_SUB_ONE,
    INTEGER_ADD_ONE,
    REAL_ADDITION,
    REAL_MULTIPLICATION,
    REAL_DIVISION,
    REAL_SUBTRACTION,
    CHAR_SUB_ONE,
    CHAR_ADD_ONE,

    EQ_BOOLEAN,
    NEQ_BOOLEAN,
    EQ_INTEGER,
    NEQ_INTEGER,
    LT_INTEGER,
    GT_INTEGER,
    LEQ_INTEGER,
    GEQ_INTEGER,
    EQ_REAL,
    NEQ_REAL,
    LT_REAL,
    GT_REAL,
    LEQ_REAL,
    GEQ_REAL,
    EQ_CHAR,
    NEQ_CHAR,
    LT_CHAR,
    GT_CHAR,
    LEQ_CHAR,
    GEQ_CHAR,

    CONVERT_INTEGER_TO_REAL,
    CONVERT_STRING_TO_CHAR,

    JUMP_FALSE,
    JUMP_TRUE,
    JUMP,

    CALL,
    RETURN,

    POP_STACK_ELEMENTS,
    DUPLICATE,

    TERMINATE_PROGRAM

};

#endif
