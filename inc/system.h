#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include <list>
#include <vector>
#include "symbolTable.h"
using namespace std;

struct RelocElem {
	int offset;
	int type; // 0 - R_386_16 , 1 - R_386_PC16
	int value;
	RelocElem(int offset, int type, int value):offset(offset), type(type), value(value){}
};

struct SectionElem {
  int index;
  string name;
  vector<unsigned char> bytes;
  list<RelocElem*> relocTable;
  SectionElem(int index, string name, int size):index(index),name(name){
	  bytes = vector<unsigned char>(size, 0);
	  relocTable = list<RelocElem*> ();
  }
};

class System {

private:

	static bool firstPass;
	static bool parserError;
	static int locationCounter;
	static int moreBytes;
	static list<SectionElem*> memory;
	static list<SectionElem*>::iterator memorySection;

	static bool switchSectionFirstCall;

public:
	static const unsigned int highBits = 4;
	static const unsigned int lowBits = 0; 

	static const int R_386_16 = 0;
	static const int R_386_PC16 = 1;

	static bool isFirstPass();
	static void setParserError();
	static bool getParserError();
	static void setFirstPass();
	static void setSecondPass();

	static int getMoreBytes();
	static void addToLocationCounter(int add);
	static int getLocationConter();
	static void resetLocationCounter();
	static void additionalBytes(int add);

	static void initMemory(list<Elem*> ls);
	static void switchSection();
	static void writeMemory(int lc, unsigned char data);
	static void patchMemory(int lc, unsigned char data, unsigned int highLowBits);

	static void printSectionMemory();
	static void makeRelocation(int offset, int type, int value);
	static void printRelocation();

	static void printFile();
	static void printAllSectionsMemory();



};



#endif
