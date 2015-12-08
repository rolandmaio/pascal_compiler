#include<unordered_map>
using std::unordered_map;
#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include "compiler/src/synthesizer/synthesizer.h"
#include "compiler/src/parser/parser.h"
#include "compiler/src/parsetreelogger/parsetreelogger.h"
#include "compiler/src/lexer/lexer.h"
#include "emulator/emulator.h"

int main(int argc, char* argv[]){

    cout << "Entering main." << endl;

    string sourceFile(argv[1]);// = "pascalPrograms/array.pas";//
    cout << "sourceFile: " << sourceFile << endl;

    string outFile = "test_outfile.eml";
    cout << "outFile: " << outFile << endl;

    cout << "Instantiating Synthesizer." << endl;
    Synthesizer synthesizer(outFile);

    cout << "Instantiating ParseTreeLogger." << endl;
    ParseTreeLogger parseTreeLogger(sourceFile);

    cout << "Instantiating symbol table." << endl;
    unordered_map<string, Token> symboltable;

    cout << "Instantiating lexer." << endl;
    Lexer lexer(sourceFile.c_str(), &symboltable);

    cout << "Instantiating Parser." << endl;
    Parser parser(
        sourceFile.c_str(),
        &lexer,
        &synthesizer,
        &parseTreeLogger,
        &symboltable
    );

    cout << "parsing" << endl;
    parser.parse();

    cout << "synthesizing" << endl;
    synthesizer.writeFile();

    cout << "Exiting" << endl;

}
