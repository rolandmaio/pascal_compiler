#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;
#include "parser/parser.h"

int main(int argc, char *argv[]){
    cout << "Entering main." << endl;
    //char *sourceFile = argv[1];
    string sourceFile = "../test/pascalPrograms/helloworld.pas";
    cout << "Instantiating parser." << endl;
    Parser parser(sourceFile.c_str());
    cout << "Calling Parser.parse" << endl;
    parser.parse();
}
