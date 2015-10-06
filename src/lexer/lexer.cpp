#ifndef LEXER_IMP
#define LEXER_IMP

#include<cctype>
using std::isspace;
using std::isdigit;
using std::isalpha;
#include<cstdlib>
using std::exit;
#include<iostream>
using std::cout;
using std::endl;
#include<utility>
using std::make_pair;
#include<string>
using std::string;
#include "lexer.h"
#include "../token/token.h"
#include "../token/identifiertoken.h"
#include "../token/integertoken.h"
#include "../token/stringtoken.h"
#include "../token/realtoken.h"

#define ENDOFFILE 127

Lexer::Lexer(const char* scanp){

    curline = 1;
    curcol = 1;
    this->scanp = scanp;

    for(int i = 0; i < defaultTokens.size(); ++i){
        lexemes.insert(defaultTokens[i]);
    }

}

void Lexer::advanceScanp(){

    if(*scanp == '\n'){
        ++curline;
        curcol = 1;
    } else {
        ++curcol;
    }
    ++scanp;

}

/*
 * Precondition:
 *  scanp points to the second character in the character sequence
 *  of some comment in the source code.
 *      e.g. (* abcd *)                     *scanp == '*' && *(++scanp) == ' '
 *           {this is a brace comment}      *scanp == 't' && *(++scanp) == 'h'
 *           //A line comment.              *scanp == '/' && *(++scanp) == 'A'
 *
 * Postcondition:
 *  scanp points to the character which immediately proceeds the comment in the
 *  source code.
 */
void Lexer::stripComments(CommentType commentType){

    switch(commentType){

        case PSTAR:
            do{
                advanceScanp();
                // Check for the start of a nested comment.
                if(*scanp == '{'){
                    advanceScanp();
                    stripComments(BRACE);
                }
                if(*scanp == '('){
                    advanceScanp();
                    if(*scanp == '*'){
                        stripComments(PSTAR);
                    }
                }
                // Check for the end of this comment.
                if(*scanp == '*'){
                    advanceScanp();
                    if(*scanp == ')'){
                        advanceScanp();
                        return;
                    }
                }
            } while (*scanp != LEXER_EOF);
            break;
        case BRACE:
            do{
                advanceScanp();
                // Check for the start of a nested comment.
                if(*scanp == '{'){
                    advanceScanp();
                    stripComments(BRACE);
                }
                if(*scanp == '('){
                    advanceScanp();
                    if(*scanp == '*'){
                        stripComments(PSTAR);
                    }
                }
                // Check for the end of this comment.
                if(*scanp == '}'){
                    advanceScanp();
                    return;
                }
            } while (*scanp != LEXER_EOF);
            break;
        case LINE:
            while(*scanp != '\n'){
                advanceScanp();
            }
            advanceScanp();
            return;
            break;
    }

}

Token Lexer::getToken(){

    // Strip white space and comments.
    while(isspace(*scanp)){

        advanceScanp();
        // Check if ( denotes the beginning of a comment
        // or an actual left parenthesis special-symbol.
        if(*scanp == '('){

            advanceScanp();
            if(*scanp != '*'){
                return lexemes["("];
            }
            stripComments(PSTAR);

        }
        if(*scanp == '/'){
            advanceScanp();
            if(*scanp != '/'){
                return lexemes["/"];
            }
            stripComments(LINE);
        }
        if(*scanp == '{'){
            advanceScanp();
            stripComments(BRACE);
        }

    }

    // Process identifiers and keywords.
    if(isalpha(*scanp)){
        int i = 0;
        while(
            i < MAX_IDLEN &&
            (isalpha(*scanp) || isdigit(*scanp))
        ){

            curname[i++] = tolower(*scanp);
            advanceScanp();

        }
        curname[i] = '\0';
        string lexeme(curname);
        if(!lexemes.count(lexeme)){
            lexemes.insert(
                make_pair<string, Token>(lexeme.c_str(), IdentifierToken(lexeme))
            );
        }
        return lexemes[lexeme];
    }

    // Process literal numeric values.
    if(isdigit(*scanp)){
        int value = 0;
        do{
            value = value*10 + (*scanp - '0');
            advanceScanp();
        } while(isdigit(*scanp));
        if(*scanp != '.'){
            return IntegerToken(value);
        } else {
            advanceScanp();
        }
        double fraction = 0.0,
               multiplier = 1.0 / 10.0;
        do{
            fraction += (*scanp - '0') * multiplier;
            multiplier /= 10.0;
            advanceScanp();
        } while(isdigit(*scanp));
        return RealToken(value + fraction);
    }

    // Process literal string values.
    if(*scanp == '\''){
        int i = 0;
        while(true){
            advanceScanp();
            if(*scanp != '\''){
                curname[i++] = *scanp;
            } else {
                advanceScanp();
                if(*scanp == '\''){
                    curname[i++] = '\'';
                } else {
                    curname[i] == '\0';
                    return StringToken(curname);
                }
            }
        }
    }

    char anchor = *scanp;
    advanceScanp();
    // Process operators.
    switch(anchor){
        case '+':
            return lexemes["+"];
        case '-':
            return lexemes["-"];
        case '*':
            return lexemes["*"];
        case '/':
            return lexemes["/"];
        case '=':
            return lexemes["="];
        case '<':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '>'){
                return lexemes["<>"];
            } else if (anchor == '='){
                return lexemes["<="];
            } else {
                return lexemes["<"];
            }
        case '>':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '='){
                return lexemes[">="];
            } else {
                return lexemes[">"];
            }
        case '[':
            return lexemes["["];
        case ']':
            return lexemes["]"];
        case '.':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '.'){
                return lexemes[".."];
            } else {
                return lexemes["."];
            }
        case ',':
            return lexemes[","];
        case ':':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '='){
                return lexemes[":="];
            } else {
                return lexemes[":"];
            }
        case ';':
            return lexemes[";"];
        case '(':
            return lexemes["("];
        case ')':
            return lexemes[")"];
        case '\x7f':
            return Token(END_OF_FILE);
    }

    return Token(END_OF_FILE);

}

#endif
