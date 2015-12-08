#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include "emulator/emulator.h"

int main(int argc, char* argv[]){

    //cout << "Entering main." << endl;
    //cout << "Instantiating Emulator" << endl;
    Emulator emulator("test_outfile.eml");
    //cout << "emulating" << endl;
    //cout << "OUTPUT:\n\n\n" << endl;
    emulator.run();
    //cout << "\n\n\nEND OUTPUT" << endl;

}
