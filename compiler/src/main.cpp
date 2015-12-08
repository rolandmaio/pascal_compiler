#include<string>
using std::string;
#include<iostream>
using std::cout;
using std::endl;
#include "parser/parser.h"
#include "synthesizer/synthesizer.h"

int main(int argc, char *argv[]){
    cout << "Entering main." << endl;
    //char *sourceFile = argv[1];
    string sourceFile = "../test/pascalPrograms/helloworld_2times.pas";
    cout << "Instantiating parser." << endl;
    Synthesizer synthesizer("helloworld_2times.eml");
    Parser parser(sourceFile.c_str(), &synthesizer);
    cout << "Calling Parser.parse" << endl;
    parser.parse();
    synthesizer.writeFile();
    cout << "Exited Parser.parse" << endl;
}
