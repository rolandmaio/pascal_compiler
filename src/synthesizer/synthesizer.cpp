#ifndef SYNTHESIZER_IMPL
#define SYNTHESIZER_IMPL

#include<iostream>
using std::cout;
using std::endl;
#include<cstring>
using std::strlen;
using std::memcpy;
#include<fstream>
using std::ofstream;
#include<cstdlib>
using std::malloc;
#include "synthesizer.h"

#define ADDR_SIZE sizeof(size_t)

Synthesizer::Synthesizer(string outFileName) : outFileName(outFileName){
    headerBuffer = malloc(INITIAL_BUFFER_SIZE);
    headerPtr = headerBuffer;
    headerSize = ADDR_SIZE;
    instructionBuffer = malloc(INITIAL_BUFFER_SIZE);
    instructionPtr = instructionBuffer;
    instructionSize = 0;
}

void Synthesizer::writeFile(){

    cout << "headerSize: " << headerSize << endl;
    genOpCode(TERMINATE_PROGRAM);
    ofstream outFile(outFileName.c_str(), std::ofstream::out | std::ofstream::binary);
    outFile.write((const char*) &headerSize, ADDR_SIZE);
    outFile.write((const char*) headerBuffer, headerSize - ADDR_SIZE);
    outFile.write((const char*) instructionBuffer, instructionSize);
    free(headerBuffer);
    free(instructionBuffer);

}

size_t Synthesizer::writeStringLiteralToHeader(StringToken strtok){
    size_t addr = headerSize,
           size = strlen(strtok.getValue().c_str());
    cout << "strtok.getValue().c_str(): " << strtok.getValue().c_str() << endl;
    strcpy((char*)headerPtr, strtok.getValue().c_str());
    headerPtr = headerPtr + size + 1;
    headerSize += size + 1;
    return addr;
}

size_t Synthesizer::writeUnsignedIntegerLiteralToHeader(Token tok){
    size_t addr = headerSize;
    unsigned int value = tok.getValue();
    cout << "value: " << value << endl;
    memcpy(headerPtr, (void*) &value, sizeof(int));
    headerPtr = headerPtr + sizeof(int);
    headerSize += sizeof(int);
    return addr;
}

void Synthesizer::genAddress(size_t addr){
    memcpy(instructionPtr, (void*)&addr, ADDR_SIZE);
    instructionPtr = instructionPtr + ADDR_SIZE;
    instructionSize = instructionSize + ADDR_SIZE;
}

void Synthesizer::genOpCode(Opcode opcode){
    unsigned char chr = opcode;
    memcpy(instructionPtr, (void*)&chr, 1);
    instructionPtr = instructionPtr + 1;
    ++instructionSize;
}

void Synthesizer::genPrintCode(Type t){
    switch(t.getKind()){
        case INTEGER_K:
            genOpCode(WRITE_INT);
            break;
        case REAL_K:
            genOpCode(WRITE_REAL);
            break;
        case BOOLEAN_K:
            genOpCode(WRITE_BOOLEAN);
            break;
        case STRING_K:
            genOpCode(WRITE_STRING);
            break;
    }
}

void Synthesizer::genPrintLn(){
    genOpCode(WRITE_LINE);
}

Type Synthesizer::genAdditionCode(Type t1, Type t2){
    if(t1.getKind() == INTEGER_K && t2.getKind() == INTEGER_K){
        genOpCode(INTEGER_ADDITION);
        return Type(INTEGER_K);
    }
    throw 1;
}

#endif
