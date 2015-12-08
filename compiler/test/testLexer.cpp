#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;
#include "../src/lexer/lexer.h"
#include "../src/token/token.h"

int main(){

    cout << "Executing testLexer.cpp" << endl;

    /*
    ifstream file();
    string program((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    cout << "program: " << endl << program << endl;
    int fileSize = program.length();
    const char* buffer = program.c_str();

    const char* scanp = buffer;
    */
    unordered_map<string, Token> symboltable;//, *symboltable_ptr;
    Lexer lexer = Lexer("./pascalPrograms/helloworld.pas", &symboltable);

    Token tok;
    int i = 0;

    while(tok.getTag() != END_OF_FILE){
        i++;
        tok = lexer.getToken();
        cout << "The " << i << "th token: " << tok.getTag() << endl;
    }

    return 0;

}
