#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;
#include "../src/lexer/lexer.h"

int main(){

    cout << "Executing testLexer.cpp" << endl;

    ifstream file("./pascalPrograms/helloworld.pas");
    string program((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    cout << "program: " << endl << program << endl;
    int fileSize = program.length();
    const char* buffer = program.c_str();

    const char* scanp = buffer;

    Lexer lexer = Lexer(scanp);

    Token tok;
    int i = 0;

    while(tok.getTag() != END_OF_FILE){
        i++;
        tok = lexer.getToken();
        cout << "The " << i << "th token: " << tok.getTag() << endl;
    }

    return 0;

}
