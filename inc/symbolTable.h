#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <list>
using namespace std;

struct Elem {
  int index;
  string name;
  int section;
  int value;
  int size;
  int scope; // 0 -> local(default) , 1 -> global
  Elem(int index, string name, int section, int value, int size, int scope) : index(index), name(name), section(section), value(value),
   size(size), scope(scope){
  }
};

class SymbolTable{

private:
  
  static int numOfSymb;
  static int numOfSect;
  static int currentSection;
  static list<Elem*> table;
  static list<Elem*> symbols;

  static int symbolList;
  static int lastLiteral;

  static list<int> lastLiterals;
  static list<string> lastSymbols;
  static list<bool> lastAdded;

  static list<unsigned char> lastRegisters;


  
public:

  static const int UND = 0;
  static const int ABS = 1;

  static void initTable();
  static void addSymbol(string symb);
  static void addSection(string sect);
  static void addEQU(string equ);
  static void setLastLiteral(int num);
  static int getLastLiteral();
  static void joinTable();
  static void printSymbolTable();
  static Elem* findSymbolInTable(string sym);

  static void incSymbolList();
  static void markSymbolGlobal();
  static void markSymbolExtern();
  static bool validSection();

  static void addSectionSize();
  static void addLabelValue(string label);

  static void addLastLiteral(int num);
  static void addLastSymbol(string sym);
  static bool whoWasLast();
  static string getLastSymbolFromList();
  static int getLastLiteralFromList();
  static int countSymbolLiterals();
  static void clearSymbolLiterals();

  static void addLastRegister(unsigned char num);
  static unsigned char getRegister();
  static void clearLastRegistersList();

};

#endif
