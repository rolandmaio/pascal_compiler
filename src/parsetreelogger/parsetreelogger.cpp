#ifndef PARSETREELOGGER_IMPL
#define PARSETREELOGGER_IMPL

#include<string>
using std::string;
using std::to_string;
#include<cstdlib>
using std::size_t;
using std::getenv; // Access env variables.
#include<ctime>
using std::tm; // Struct to get current date.
using std::localtime;
using std::time_t;
using std::time;
#include<boost/filesystem.hpp>
using namespace boost::filesystem;
#include "parsetreelogger.h"
#include "parsetreeloggerexception.h"

ParseTreeLogger::ParseTreeLogger(string sourceProgramFile){
    path p(sourceProgramFile);
    this->sourceProgramFile = p.filename().string();
    indent = 0;
    this->openFile();
    this->printHeader();
    this->printOpeningTag(this->sourceProgramFile);
}

ParseTreeLogger::~ParseTreeLogger(){
    this->dumpTagStack();
    this->closeFile();
}

void ParseTreeLogger::openFile(){
    char* logFileDir = getenv("PASCAL_COMPILER_PARSETREELOGGER_DIR");
    if(logFileDir == NULL){
        throw ParseTreeLoggerException(PARSE_TREE_LOG_DIR_ENV_VAR_ERROR);
    }
    string fileName = this->computeFileName();
    this->logFileName = string(logFileDir) + "/" + fileName;
    this->logFile.open(this->logFileName.c_str());
}

void ParseTreeLogger::closeFile(){
    this->logFile.close();
}

string ParseTreeLogger::computeFileName(){
    time_t t = time(0);
    struct tm* now = localtime(&t);
    return this->sourceProgramFile + "Run" + this->currentDateTime();
}

string ParseTreeLogger::currentDateTime(){
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%F@%Hh%Mm%Ss", &tstruct);
    return string(buf);
}

void ParseTreeLogger::printHeader(){
    this->logFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
}

void ParseTreeLogger::printOpeningTag(string tagName){
    this->printIndent();
    this->logFile << "<" << tagName << ">\n";
    this->openTagsStack.push_back(tagName);
    this->incrementIndent();
}

void ParseTreeLogger::printClosingTag(string tagName){
    this->decrementIndent();
    this->printIndent();
    if(this->matchTagStack(tagName)){
        this->openTagsStack.pop_back();
        this->logFile << "</" << tagName << ">\n";
    } else {
        ParseTreeLoggerException exception(CLOSE_ON_UNOPENED_TAG_ERROR, tagName);
        this->printErrorTag(exception.what());
        this->dumpTagStack();
    }
}

void ParseTreeLogger::dumpTagStack(){
    size_t size = this->openTagsStack.size();
    while(this->openTagsStack.size()){
        this->printClosingTag(this->openTagsStack.back());
    }
}

void ParseTreeLogger::printIndent(){
    for(int i = 0; i < this->indent; ++i)
        this->logFile << "  ";
}

void ParseTreeLogger::incrementIndent(){
    ++indent;
}

void ParseTreeLogger::decrementIndent(){
    --indent;
}

bool ParseTreeLogger::matchTagStack(string tagName){
    return this->openTagsStack.back() == tagName;
}

void ParseTreeLogger::printErrorTag(string message){
    this->logFile << "<error>" << message << "</error>\n";
}

void ParseTreeLogger::logEntry(string functionName){
    this->printOpeningTag(functionName);
}

void ParseTreeLogger::logExit(string functionName){
    this->printClosingTag(functionName);
}

#endif
