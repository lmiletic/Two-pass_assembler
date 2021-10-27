#include "../inc/parserDriver.h"
#include "../inc/system.h"
#include "../inc/symbolTable.h"
#include <iostream>


using namespace std;


void psHalt(){
    //std::cout << "Halt" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(1);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x00);
        System::addToLocationCounter(1);
    }
}

void psInt(){
    //std::cout << "Int" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x10);
        //dodati u registar 1111 -> neki patch uradi
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x0F, System::lowBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::addToLocationCounter(2);
    }
}

void psIret(){
    //std::cout << "Iret" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(1);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x20);
        System::addToLocationCounter(1);
    }
}

void psCall(){
    //std::cout << "Call" << std::endl;
    if(System::isFirstPass()){
        //cout << "LC:" << System::getLocationConter() << endl;
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        //cout << "LC:" << System::getLocationConter() << endl;
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x30);
        //patch registara
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x0F, System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psRet(){
    //std::cout << "Ret" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(1);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x40);
        System::addToLocationCounter(1);
    }
}

void psJmp(){
    //std::cout << "Jmp" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x50);
        //patch reg
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x0F, System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psJeq(){
    //std::cout << "Jeq" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x51);
        //patch reg
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x0F, System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psJne(){
    //std::cout << "Jne" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x52);
        //patch reg
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x0F, System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psJgt(){
    //std::cout << "Jgt" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x53);
        //patch reg
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x0F, System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psPush(){
    //std::cout << "Push" << std::endl;
    if(System::isFirstPass()){
        //cout << "LC:" << System::getLocationConter() << endl;
        System::addToLocationCounter(3);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        //cout << "LC:" << System::getLocationConter() << endl;
        System::writeMemory(System::getLocationConter() + InstrDescr, 0xB0);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x06, System::lowBits);
        System::writeMemory(System::getLocationConter() + AddrMode, 0x12);
        System::addToLocationCounter(3);
    }
}

void psPop(){
    //std::cout << "Pop " << std::endl;
    if(System::isFirstPass()){
        //cout << "LC:" << System::getLocationConter() << endl;
        System::addToLocationCounter(3);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        //cout << "LC:" << System::getLocationConter() << endl;
        System::writeMemory(System::getLocationConter() + InstrDescr, 0xA0);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x06, System::lowBits);
        System::writeMemory(System::getLocationConter() + AddrMode, 0x42);
        System::addToLocationCounter(3);
    }
}

void psXchg(){
    //std::cout << "Xchg" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x60);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psAdd(){
    //std::cout << "Add" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x70);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psSub(){
    //std::cout << "Sub" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x71);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psMul(){
    //std::cout << "Mul" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x72);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psDiv(){
    //std::cout << "Div" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x73);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psCmp(){
    //std::cout << "Cmp" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x74);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psNot(){
    //std::cout << "Not" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x80);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::addToLocationCounter(2);
    }
}

void psAnd(){
    //std::cout << "And" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x81);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psOr(){
    //std::cout << "Or" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x82);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psXor(){
    //std::cout << "Xor" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x83);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psTest(){
    //std::cout << "Test" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x84);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psShl(){
    //std::cout << "Shl" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x90);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psShr(){
    //std::cout << "Shr" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0x91);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::lowBits);
        System::addToLocationCounter(2);
    }
}

void psLdr(){
    //std::cout << "Ldr" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0xA0);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psStr(){
    //std::cout << "Str" << std::endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
        if(!SymbolTable::validSection()){
            cout << "Greska, instrukcija se ne nalazi u sekciji" << endl;
            System::setParserError();
        }
    }else{
        System::writeMemory(System::getLocationConter() + InstrDescr, 0xB0);
        System::patchMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister(), System::highBits);
        System::addToLocationCounter(3);
        System::addToLocationCounter(System::getMoreBytes());
        System::additionalBytes(0);
    }
}

void psLabelName(string labelName){
    if(System::isFirstPass()){
        if(!SymbolTable::validSection()){
            System::setParserError();
            cout << "Greska, labela se ne nalazi u sekciji" << endl;
        }else{
            SymbolTable::addSymbol(labelName);
            SymbolTable::addLabelValue(labelName);
        }
    }
}

void readSymbol(string symb){
    if(System::isFirstPass()){
        SymbolTable::incSymbolList();
    	SymbolTable::addSymbol(symb);
    }
}

void psEnd(){
    //cout << "End" << endl;
    if(System::isFirstPass()){
        SymbolTable::addSectionSize();
        SymbolTable::joinTable();
    }else{
        System::resetLocationCounter();
    }
}

void beginSection(std::string section){
    if(System::isFirstPass()){
        SymbolTable::addSectionSize();
        SymbolTable::addSection(section);
    }else{
        System::resetLocationCounter();
        System::switchSection();
    }
}

void psGlobal(){
    if(System::isFirstPass()){
        SymbolTable::markSymbolGlobal();
    }
}

void psExtern(){
    if(System::isFirstPass()){
        SymbolTable::markSymbolExtern();
    }
}

void psLiteralNUM(int num){
    SymbolTable::addLastLiteral(num);
    SymbolTable::setLastLiteral(num); //samo za skip
}

void psLiteralHEX(std::string num){
    int number = 0;
    number = stoi(num, nullptr, 16);
    SymbolTable::addLastLiteral(number);
    SymbolTable::setLastLiteral(number); //samo za skip
    
}

void psLiteralOCTAL(std::string num){
    int number = 0;
    number = stoi(num, nullptr, 8);
    SymbolTable::addLastLiteral(number);
    SymbolTable::setLastLiteral(number); //samo za skip
}

void psEQU(std::string equ){
    if(System::isFirstPass()){
        SymbolTable::addEQU(equ);
    }   
}

void psWord(){
    //cout << "LC:" << System::getLocationConter() << endl;
    //cout << "Words: " << SymbolTable::countSymbolLiterals() << endl;
    if(System::isFirstPass()){
        System::addToLocationCounter(2*SymbolTable::countSymbolLiterals());
        if(!SymbolTable::validSection()){
            System::setParserError();
            cout << "Greska, direktiva .word se ne nalazi u sekciji. " << endl;
        }
    }else{
        int listCount = SymbolTable::countSymbolLiterals();
        for(int i = 0; i < listCount; i++){
            if(SymbolTable::whoWasLast()){
                string sym = SymbolTable::getLastSymbolFromList();
                Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
                if(findSymbol == nullptr){
                    cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
                    System::setParserError();
                }else{
                    //cout << "Symbol : " << findSymbol->value << endl;
                    if(findSymbol->section != SymbolTable::ABS){
                        int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                        System::makeRelocation(System::getLocationConter(), System::R_386_16, value);
                    }
                    unsigned char higher = 0x00;
                    unsigned char lower = 0x00;
                    if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                        higher = (findSymbol->value & 0x0000FF00) >> 8;
                        lower = (findSymbol->value & 0x000000FF);
                    }
                    System::writeMemory(System::getLocationConter(), lower);
                    System::writeMemory(System::getLocationConter() + 1, higher);
                }
            }else{
                int lit = SymbolTable::getLastLiteralFromList();
                //cout << "Literal : " << lit << endl;
                unsigned char higher = (lit & 0x0000FF00) >> 8;
                unsigned char lower = (lit & 0x000000FF);
                System::writeMemory(System::getLocationConter(), lower);
                System::writeMemory(System::getLocationConter() + 1, higher);
            }
            System::addToLocationCounter(2);
        }
    }
    SymbolTable::clearSymbolLiterals();   
}

void psSkip(){
    System::addToLocationCounter(SymbolTable::getLastLiteral());
    //cout << "LC:" << System::getLocationConter() << endl;
    if(System::isFirstPass()){
        if(!SymbolTable::validSection()){
            System::setParserError();
            cout << "Greska, direktiva .skip se ne nalazi u sekciji. " << endl;
        }
    }
    SymbolTable::clearSymbolLiterals();   
}

void addRegister(int reg){
    SymbolTable::addLastRegister(reg);
}

void directiveDone(){
    SymbolTable::clearSymbolLiterals();
    SymbolTable::clearLastRegistersList();
}

void statementDone(){
    SymbolTable::clearSymbolLiterals();
    SymbolTable::clearLastRegistersList();
}

void processSymbol(std::string sym){
    SymbolTable::addLastSymbol(sym);
}

//Jump operands

void jmpLiteral(){
    //neposredna vrednost Literal
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x00);
        unsigned char higher = (SymbolTable::getLastLiteral() & 0x0000FF00) >> 8;
        unsigned char lower = (SymbolTable::getLastLiteral() & 0x000000FF);
        System::writeMemory(System::getLocationConter() + DataHigh, higher);
        System::writeMemory(System::getLocationConter() + DataLow, lower);
    }
}
void jmpIdent(std::string sym){
    //apsolutno adresiranje Simbol
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x00);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_16, value);
            }
            unsigned char higher = 0x00;
            unsigned char lower = 0x00;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                higher = (findSymbol->value & 0x0000FF00) >> 8;
                lower = (findSymbol->value & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}
void jmpPercIdent(std::string sym){
    //PC relativno adresiranje Simbol
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x05);
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x07, System::lowBits);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_PC16, value);
            }
            unsigned char higher = 0xff;
            unsigned char lower = 0xfe;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                int val = (findSymbol->value) - 2;
                higher = (val & 0x0000FF00) >> 8;
                lower = (val & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
} 
void jmpStarLiteral(){
    //mem[Literal]
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x04);
        unsigned char higher = (SymbolTable::getLastLiteral() & 0x0000FF00) >> 8;
        unsigned char lower = (SymbolTable::getLastLiteral() & 0x000000FF);
        System::writeMemory(System::getLocationConter() + DataHigh, higher);
        System::writeMemory(System::getLocationConter() + DataLow, lower);
    }
}
void jmpStarIdent(std::string sym){
    //mem[Simbol]
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x04);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_16, value);
            }
            unsigned char higher = 0x00;
            unsigned char lower = 0x00;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                higher = (findSymbol->value & 0x0000FF00) >> 8;
                lower = (findSymbol->value & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}
void jmpStarReg(){
    //registarsko direktno
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x01);
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
    }
}
void jmpBracReg(){
    //registarsko indirektno
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x02);
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
    }
}
void jmpBracRegPlusLiteral(){
    //registarsko indirektno sa 16b pomerajem(Literal)
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x03);
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
        unsigned char higher = (SymbolTable::getLastLiteral() & 0x0000FF00) >> 8;
        unsigned char lower = (SymbolTable::getLastLiteral() & 0x000000FF);
        System::writeMemory(System::getLocationConter() + DataHigh, higher);
        System::writeMemory(System::getLocationConter() + DataLow, lower);
    }
}

void jmpBracRegPlusIdent(std::string sym){
    //registarsko indirektno sa 16b pomerajem(Simbol)
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x03);
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_16, value);
            }
            unsigned char higher = 0x00;
            unsigned char lower = 0x00;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                higher = (findSymbol->value & 0x0000FF00) >> 8;
                lower = (findSymbol->value & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}

//Data operands

void dataDolLiteral(){
    //vrednost Literal
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x00);
        unsigned char higher = (SymbolTable::getLastLiteral() & 0x0000FF00) >> 8;
        unsigned char lower = (SymbolTable::getLastLiteral() & 0x000000FF);
        System::writeMemory(System::getLocationConter() + DataHigh, higher);
        System::writeMemory(System::getLocationConter() + DataLow, lower);
    }
}
void dataDolIdent(std::string sym){
    //vrednost Simbol
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x00);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_16, value);
            }
            unsigned char higher = 0x00;
            unsigned char lower = 0x00;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                higher = (findSymbol->value & 0x0000FF00) >> 8;
                lower = (findSymbol->value & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}
void dataLiteral(){
    //mem[Literal]
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x04);
        unsigned char higher = (SymbolTable::getLastLiteral() & 0x0000FF00) >> 8;
        unsigned char lower = (SymbolTable::getLastLiteral() & 0x000000FF);
        System::writeMemory(System::getLocationConter() + DataHigh, higher);
        System::writeMemory(System::getLocationConter() + DataLow, lower);
    }
}
void dataIdent(std::string sym){
    //mem[Simbol] apsolutno adresiranje
    System::additionalBytes(2);
     if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x04);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_16, value);
            }
            unsigned char higher = 0x00;
            unsigned char lower = 0x00;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                higher = (findSymbol->value & 0x0000FF00) >> 8;
                lower = (findSymbol->value & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}
void dataPercIdent(std::string sym){
    //mem[Simbol] Pc relativno adresiranje
    System::additionalBytes(2);
     if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x03);
        System::patchMemory(System::getLocationConter() + RegsDescr, 0x07, System::lowBits);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_PC16, value);
            }
            unsigned char higher = 0xff;
            unsigned char lower = 0xfe;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                int val = (findSymbol->value) - 2;
                higher = (val & 0x0000FF00) >> 8;
                lower = (val & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}
void dataReg(){
    //registrasko direktno
     if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x01);
        unsigned char firstReg = SymbolTable::getRegister();
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
        SymbolTable::addLastRegister(firstReg);
    }
}
void dataBracReg(){
    //registarsko indirektno
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x02);
        unsigned char firstReg = SymbolTable::getRegister();
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
        SymbolTable::addLastRegister(firstReg);
    }
}
void dataBracRegPlusLiteral(){
    //registarsko indirektno sa 16b pomerajem(Literal)
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x03);
        unsigned char firstReg = SymbolTable::getRegister();
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
        SymbolTable::addLastRegister(firstReg);
        unsigned char higher = (SymbolTable::getLastLiteral() & 0x0000FF00) >> 8;
        unsigned char lower = (SymbolTable::getLastLiteral() & 0x000000FF);
        System::writeMemory(System::getLocationConter() + DataHigh, higher);
        System::writeMemory(System::getLocationConter() + DataLow, lower);
    }
}
void dataBracRegPlusIdent(std::string sym){
    //registarsko indirektno sa 16b pomerajem(Simbol)
    System::additionalBytes(2);
    if(!System::isFirstPass()){
        System::writeMemory(System::getLocationConter() + AddrMode, 0x03);
        unsigned char firstReg = SymbolTable::getRegister();
        System::writeMemory(System::getLocationConter() + RegsDescr, SymbolTable::getRegister());
        SymbolTable::addLastRegister(firstReg);
        Elem* findSymbol = SymbolTable::findSymbolInTable(sym);
        if(findSymbol == nullptr){
            cout << "Greska, koristi se simbol " << sym << " koji nije definisan" << endl;
            System::setParserError();
        }else{
            //cout << "Symbol : " << findSymbol->value << endl;
            if(findSymbol->section != SymbolTable::ABS){
                int value = (findSymbol->scope == 1 ? findSymbol->index : findSymbol->section);
                System::makeRelocation(System::getLocationConter() + DataHigh, System::R_386_16, value);
            }
            unsigned char higher = 0x00;
            unsigned char lower = 0x00;
            if(findSymbol->scope == 0 || findSymbol->section == SymbolTable::ABS){
                higher = (findSymbol->value & 0x0000FF00) >> 8;
                lower = (findSymbol->value & 0x000000FF);
            }
            System::writeMemory(System::getLocationConter() + DataHigh, higher);
            System::writeMemory(System::getLocationConter() + DataLow, lower);
        }
    }
}
