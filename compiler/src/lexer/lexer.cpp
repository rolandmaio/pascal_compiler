#ifndef LEXER_IMP
#define LEXER_IMP

#include<cstring>
using std::strcpy;
#include<cctype>
using std::isspace;
using std::isdigit;
using std::isalpha;
#include<cstdlib>
using std::exit;
#include<utility>
using std::make_pair;
#include<string>
using std::string;
#include<fstream>
using std::ifstream;
using std::istreambuf_iterator;
#include<iostream>
using std::cout;
using std::endl;
#include "lexer.h"
#include "../token/token.h"
#include "../token/identifiertoken.h"
#include "../token/integertoken.h"
#include "../token/stringtoken.h"
#include "../token/realtoken.h"
#include "../parser/parser.h"

#define ENDOFFILE 127

Lexer::Lexer(const char* sourceFile, unordered_map<string, Token> *symboltable){

    curline = 1;
    curcol = 1;
    this->symboltable = symboltable;

    for(int i = 0; i < defaultTokens.size(); ++i){
        this->symboltable->insert(defaultTokens[i]);
    }

    ifstream file(sourceFile);
    string program((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer = new char[1<<10];//(char*) malloc(1000);
    scanp = strcpy(buffer, program.c_str());
    cout << "Source program: " << program << endl;

}

void Lexer::setParser(Parser* parser){
    this->parser = parser;
}

void Lexer::addToStack(Token tok){
    stack.push_back(tok);
}

void Lexer::advanceScanp(){

    cout << "advancing scanp value before: " << (int)*scanp << endl;
    cout << "address of scanp before: " << scanp << endl;
    if(*scanp == '\n'){
        ++curline;
        curcol = 1;
    } else {
        ++curcol;
    }
    ++scanp;
    cout << "value after: " << (int)*scanp << endl;
    cout << "String at scanp after: " << scanp << endl;
    printf("address of scanp: %p\n", scanp);
    printf("address of buffer: %p\n", buffer);

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

    cout << "Entering Lexer::getToken()" << endl;
    if(!stack.empty()){
        cout << "The Lexer's stack is nonempty; returning top element" << endl;
        Token tok = stack.back();
        stack.pop_back();
        return tok;
    }
    cout << "String at scanp: " << scanp << endl;
    printf("address of scanp: %p\n", scanp);
    // Strip white space and comments.
    cout << "White space check on: " << (int)*scanp << ":" << endl;
    cout << "isspace(*scanp): " << isspace(*scanp) << endl;
    while(isspace(*scanp)){

        advanceScanp();
        // Check if ( denotes the beginning of a comment
        // or an actual left parenthesis special-symbol.
        if(*scanp == '('){

            advanceScanp();
            if(*scanp != '*'){
                return (*symboltable)["("];
            }
            stripComments(PSTAR);

        }
        if(*scanp == '/'){
            advanceScanp();
            if(*scanp != '/'){
                return (*symboltable)["/"];
            }
            stripComments(LINE);
        }
        if(*scanp == '{'){
            advanceScanp();
            stripComments(BRACE);
        }

    }

    // Process identifiers and keywords.
    cout << "Alphabetic check on: " << *scanp << endl;
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
        if((parser->lookupLexeme(curname)).getTag() == BAD){
            symboltable->insert(
                make_pair<string, Token>(curname, Token(ID, curname))
            );
        }

        return parser->lookupLexeme(curname);

    }

    // Process literal numeric values.
    cout << "Numeric check on: " << *scanp << endl;
    if(isdigit(*scanp)){
        int value = 0;
        do{
            value = value*10 + (*scanp - '0');
            advanceScanp();
        } while(isdigit(*scanp));
        if(*scanp != '.' || (*scanp == '.' && *(scanp + 1) == '.')){
            cout << "lexer value: " << value << endl;
            Token tok(INT, value);
            cout << "tok.getValue(): " << tok.getValue() << endl;
            return tok;
        } else {
            advanceScanp();
        }
        float fraction = 0.0,
              multiplier = 1.0 / 10.0;
        do{
            fraction += (*scanp - '0') * multiplier;
            multiplier /= 10.0;
            advanceScanp();
        } while(isdigit(*scanp));
        return Token(REAL, value + fraction);
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
                    curname[i] = '\0';
                    return StringToken(string(curname));
                }
            }
        }
    }

    char anchor = *scanp;
    advanceScanp();
    // Process operators.
    switch(anchor){
        case '+':
            return (*symboltable)["+"];
        case '-':
            return (*symboltable)["-"];
        case '*':
            return (*symboltable)["*"];
        case '/':
            return (*symboltable)["/"];
        case '=':
            return (*symboltable)["="];
        case '<':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '>'){
                return (*symboltable)["<>"];
            } else if (anchor == '='){
                return (*symboltable)["<="];
            } else {
                return (*symboltable)["<"];
            }
        case '>':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '='){
                return (*symboltable)[">="];
            } else {
                return (*symboltable)[">"];
            }
        case '[':
            return (*symboltable)["["];
        case ']':
            return (*symboltable)["]"];
        case '.':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '.'){
                return (*symboltable)[".."];
            } else {
                return (*symboltable)["."];
            }
        case ',':
            return (*symboltable)[","];
        case ':':
            anchor = *scanp;
            advanceScanp();
            if(anchor == '='){
                return (*symboltable)[":="];
            } else {
                return (*symboltable)[":"];
            }
        case ';':
            return (*symboltable)[";"];
        case '(':
            return (*symboltable)["("];
        case ')':
            return (*symboltable)[")"];
        case '\x7f':
            return Token(END_OF_FILE);
    }

    return Token(END_OF_FILE);

}

#endif
