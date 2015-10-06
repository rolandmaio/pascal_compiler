#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<string>
using std::string;
#include "token.h"

vector<pair<string, Token> > defaultTokens = {

    make_pair<string, Token>("+", Token(PLUS)),
    make_pair<string, Token>("-", Token(MINUS)),
    make_pair<string, Token>("*", Token(STAR)),
    make_pair<string, Token>("/", Token(FSLASH)),
    make_pair<string, Token>("=", Token(EQ)),
    make_pair<string, Token>("<", Token(LT)),
    make_pair<string, Token>(">", Token(GT)),
    make_pair<string, Token>("[", Token(LBRACKET)),
    make_pair<string, Token>("]", Token(RBRACKET)),
    make_pair<string, Token>(".", Token(DOT)),
    make_pair<string, Token>(",", Token(COMMA)),
    make_pair<string, Token>(":", Token(COLON)),
    make_pair<string, Token>(";", Token(SEMICOLON)),
    // Ignore this one for now.
    // make_pair<string, Token>("<UP ARROW>", Token(SEMICOLON)),
    make_pair<string, Token>("(", Token(LPAREN)),
    make_pair<string, Token>(")", Token(RPAREN)),
    make_pair<string, Token>("<>", Token(NEQ)),
    make_pair<string, Token>("<=", Token(LEQ)),
    make_pair<string, Token>(">=", Token(GEQ)),
    make_pair<string, Token>(":=", Token(ASSIGN)),
    make_pair<string, Token>("..", Token(RANGE)),
    make_pair<string, Token>("and", Token(AND)),
    make_pair<string, Token>("array", Token(ARRAY)),
    make_pair<string, Token>("begin", Token(BEGIN)),
    make_pair<string, Token>("case", Token(CASE)),
    make_pair<string, Token>("const", Token(CONST)),
    make_pair<string, Token>("div", Token(DIV)),
    make_pair<string, Token>("do", Token(DO)),
    make_pair<string, Token>("downto", Token(DOWNTO)),
    make_pair<string, Token>("else", Token(ELSE)),
    make_pair<string, Token>("end", Token(END)),
    make_pair<string, Token>("file", Token(PFILE)),
    make_pair<string, Token>("for", Token(FOR)),
    make_pair<string, Token>("function", Token(FUNCTION)),
    make_pair<string, Token>("goto", Token(GOTO)),
    make_pair<string, Token>("if", Token(IF)),
    make_pair<string, Token>("in", Token(IN)),
    make_pair<string, Token>("label", Token(LABEL)),
    make_pair<string, Token>("mod", Token(MOD)),
    make_pair<string, Token>("nil", Token(NIL)),
    make_pair<string, Token>("not", Token(NOT)),
    make_pair<string, Token>("of", Token(OF)),
    make_pair<string, Token>("or", Token(OR)),
    make_pair<string, Token>("packed", Token(PACKED)),
    make_pair<string, Token>("procedure", Token(PROCEDURE)),
    make_pair<string, Token>("program", Token(PROGRAM)),
    make_pair<string, Token>("record", Token(RECORD)),
    make_pair<string, Token>("repeat", Token(REPEAT)),
    make_pair<string, Token>("set", Token(SET)),
    make_pair<string, Token>("then", Token(THEN)),
    make_pair<string, Token>("to", Token(TO)),
    make_pair<string, Token>("type", Token(TYPE)),
    make_pair<string, Token>("until", Token(UNTIL)),
    make_pair<string, Token>("var", Token(VAR)),
    make_pair<string, Token>("while", Token(WHILE)),
    make_pair<string, Token>("with", Token(WITH)),

};
