#include "../inc/system.h"
#include "../inc/symbolTable.h"
#include <iostream>
#include <iomanip>

bool System::firstPass = false;
bool System::parserError = false;
int System::locationCounter = 0;
int System::moreBytes = 0;
list<SectionElem*> System::memory = list<SectionElem*>();
list<SectionElem*>::iterator System::memorySection = memory.begin();

bool System::switchSectionFirstCall = true;

bool System::isFirstPass(){
	return firstPass;
}

void System::setParserError(){
	parserError = true;
}

bool System::getParserError(){
	return parserError;
}

void System::setFirstPass(){
	SymbolTable::initTable();
	firstPass = true;
	//std::cout << "First pass" << std::endl;
}

void System::setSecondPass(){
	firstPass = false;
	//std::cout << "Second pass" << std::endl;
}

void System::addToLocationCounter(int add){
	locationCounter += add;
}

int System::getLocationConter(){
	return locationCounter;
}

void System::resetLocationCounter(){
	locationCounter = 0;
}

void System::additionalBytes(int add){
	moreBytes = add;
}

int System::getMoreBytes(){
	return moreBytes;
}

void System::initMemory(list<Elem*> ls){
	bool sectionsExists = false;
	list<Elem*>::iterator it = ls.begin();
	if(ls.size() > 2){
			sectionsExists = true;
			it++;
			it++;
	}else{
			cout << "Ne postoje sekcije u kodu." << endl;
	}
	if(sectionsExists){
		while(it != ls.end()){
			memory.push_back(new SectionElem((*it)->index, (*it)->name, (*it)->size));
			it++;
		}
	}
	memorySection = memory.begin(); //postavlja se prva sekcija
}

void System::switchSection(){
	if(switchSectionFirstCall){
		switchSectionFirstCall = false;
	}else{
		memorySection++;
	}
}

void System::writeMemory(int lc, unsigned char data){
	//cout << "Pozvan writeMemory" << endl;
	((*memorySection)->bytes)[lc] = data;
	//System::printSectionMemory();
}

void System::patchMemory(int lc, unsigned char data, unsigned int highLowBits){
	//cout << "Pozvan patchMemory" << endl;
	//cout << "Section: " << (*memorySection)->index << ", " << (*memorySection)->name << endl;
	((*memorySection)->bytes)[lc] = ((*memorySection)->bytes)[lc] | (0x0F << highLowBits);
	((*memorySection)->bytes)[lc] = ((*memorySection)->bytes)[lc] & ((data << highLowBits) | (0xF0 >> highLowBits));
	//cout << hex << setfill('0') << setw(2) << (int)((*memorySection)->bytes)[lc] << endl;
	//cout << dec;
}

void System::printSectionMemory(){
	cout << "Section: " << (*memorySection)->index << ", " << (*memorySection)->name << endl;
	for(int i = 0; i < ((*memorySection)->bytes).size(); i++){
		if(i%8 == 0 && i != 0) cout << endl;
		cout << hex << setfill('0') << setw(2) << (int)(((*memorySection)->bytes)[i]) << " ";
	}
	cout << endl;
	cout << dec;
}

void System::printAllSectionsMemory(){
	for(list<SectionElem*>::iterator it = memory.begin(); it != memory.end(); it++){
		cout << "Section: " << (*it)->index << ", " << (*it)->name << endl;
		for(int i = 0; i < ((*it)->bytes).size(); i++){
			if(i%8 == 0 && i != 0) cout << endl;
			cout << hex << setfill('0') << setw(2) << (int)(((*it)->bytes)[i]) << " ";
		}
		cout << endl;
		cout << endl;
		cout << dec;
	}
}

void System::printRelocation(){
	for(list<SectionElem*>::iterator it = memory.begin(); it != memory.end(); it++){
		cout << "Relocation: " << (*it)->name << endl;
		cout << "offset  |" << "type      |" << "value" << endl;  
		for(list<RelocElem*>::iterator ik = ((*it)->relocTable).begin(); ik != ((*it)->relocTable).end(); ik++){
			cout << (*ik)->offset << "       |" << "R_386_" << ((*ik)->type == R_386_PC16 ? "PC" : "") << "16  |" << (*ik)->value << endl; 
		}
		cout << endl;
	}
}

void System::makeRelocation(int offset, int type, int value){
	((*memorySection)->relocTable).push_back(new RelocElem(offset, type, value));
}

void System::printFile(){
	SymbolTable::printSymbolTable();
	System::printRelocation();
	System::printAllSectionsMemory();
}




