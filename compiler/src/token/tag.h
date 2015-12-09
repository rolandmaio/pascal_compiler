#ifndef COMPILER_TAGS
#define COMPILER_TAGS

enum Tag{

    // Identifiers.
    ID,
    // Operators and special symbols
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    FSLASH,     // /
    EQ,         // =
    LT,         // <
    GT,         // >
    LBRACKET,   // [
    RBRACKET,   // ]
    DOT,        // .
    COMMA,      // ,
    COLON,      // :
    SEMICOLON,  // ;
    EXP,        // (up arrow)
    LPAREN,     // (
    RPAREN,     // )
    NEQ,        // <>
    LEQ,        // <=
    GEQ,        // >=
    ASSIGN,     // :=
    RANGE,      // ..
    // word-symbols, except where otherwise noted, the word-symbol
    // will be the Tag name but lowercased. Note, Pascal itself is case
    // insensitive with respect to these symbols.
    AND,
    ARRAY,
    BEGIN,
    CASE,
    CONST,
    DIV,
    DO,
    DOWNTO,
    ELSE,
    END,
    PFILE,
    FOR,
    FORWARD,
    FUNCTION,
    GOTO,
    IF,
    IN,
    LABEL,
    MOD,
    NIL,
    NOT,
    OF,
    OR,
    PACKED,
    PROCEDURE,
    PROGRAM,
    RECORD,
    REPEAT,
    SET,
    THEN,
    TO,
    TYP,
    UNTIL,
    VAR,
    WHILE,
    WITH,
    // Literal values
    INT,
    REAL,
    STRING,
    BOOLEAN,

    // End of file flag.
    END_OF_FILE,
    // Flag value for bad syntax.
    BAD,

    // Token types that can only be determined by the parser as they require
    // knowledge of the grammar.
    TK_A_LABEL,
    TK_A_VAR,
    TK_A_PROC,
    TK_A_FUNC,
    TK_A_ARRAY,
    TK_A_RECORD,
    TK_A_PTR,
    TK_A_FILE,
    TK_A_CONST,
    TK_GOTO

};

#endif
