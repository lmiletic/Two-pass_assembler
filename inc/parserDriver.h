#ifndef PARSERDRIVER_H
#define PARSERDRIVER_H
#include <string>
#define InstrDescr 0
#define RegsDescr 1
#define AddrMode 2
#define DataHigh 3
#define DataLow 4

void psHalt();
void psInt();
void psIret();
void psCall();
void psRet();
void psJmp();
void psJeq();
void psJne();
void psJgt();
void psPush();
void psPop();
void psXchg();
void psAdd();
void psSub();
void psMul();
void psDiv();
void psCmp();
void psNot();
void psAnd();
void psOr();
void psXor();
void psTest();
void psShl();
void psShr();
void psLdr();
void psStr();

void psLabelName(std::string labelName);
void readSymbol(std::string symb);
void beginSection(std::string section);
void psEnd();

void psGlobal();
void psExtern();

void psLiteralNUM(int num);
void psLiteralHEX(std::string num);
void psLiteralOCTAL(std::string num);
void psEQU(std::string equ);

void psWord();
void psSkip();

void directiveDone();
void statementDone();
void processSymbol(std::string sym);

void addRegister(int reg);

//Jump operands

void jmpLiteral();
void jmpIdent(std::string sym);
void jmpPercIdent(std::string sym); 
void jmpStarLiteral();
void jmpStarIdent(std::string sym);
void jmpStarReg();
void jmpBracReg();
void jmpBracRegPlusLiteral();
void jmpBracRegPlusIdent(std::string sym);

//Data operands

void dataDolLiteral();
void dataDolIdent(std::string sym);
void dataLiteral();
void dataIdent(std::string sym);
void dataPercIdent(std::string sym);
void dataReg();
void dataBracReg();
void dataBracRegPlusLiteral();
void dataBracRegPlusIdent(std::string sym);



#endif
