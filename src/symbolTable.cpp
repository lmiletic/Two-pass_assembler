#include "../inc/symbolTable.h"
#include "../inc/system.h"
#include <list>
#include <iterator>
#include <iostream>
using namespace std;

list<Elem*> SymbolTable::table = list<Elem*>();
list<Elem*> SymbolTable::symbols = list<Elem*>();
int SymbolTable::numOfSymb = 0;
int SymbolTable::numOfSect = 0;
int SymbolTable::currentSection = 0;

int SymbolTable::symbolList = 0;
int SymbolTable::lastLiteral = 0;

list<int> SymbolTable::lastLiterals = list<int>();
list<string> SymbolTable::lastSymbols = list<string>();
list<bool> SymbolTable::lastAdded = list<bool>();

list<unsigned char> SymbolTable::lastRegisters = list<unsigned char>();

void SymbolTable::addLastRegister(unsigned char num){
	lastRegisters.push_back(num);
}

unsigned char SymbolTable::getRegister(){
	int reg = lastRegisters.front();
	lastRegisters.pop_front();
	return reg;
}

void SymbolTable::clearLastRegistersList(){
	lastRegisters.clear();
}

void SymbolTable::addLastLiteral(int num){
	lastLiterals.push_back(num);
	lastAdded.push_back(false);
}

void SymbolTable::addLastSymbol(string sym){
	lastSymbols.push_back(sym);
	lastAdded.push_back(true);
}

bool SymbolTable::whoWasLast(){
	bool last = lastAdded.front();
	lastAdded.pop_front();
	return last;
}

string SymbolTable::getLastSymbolFromList(){
	string last = lastSymbols.front();
	lastSymbols.pop_front();
	return last;
}

int SymbolTable::getLastLiteralFromList(){
	int last = lastLiterals.front();
	lastLiterals.pop_front();
	return last;
}

int SymbolTable::countSymbolLiterals(){
	return lastSymbols.size() + lastLiterals.size();
}

void SymbolTable::clearSymbolLiterals(){
	lastLiterals.clear();
	lastSymbols.clear();
	lastAdded.clear();
}

void SymbolTable::incSymbolList(){
	symbolList++;
}

void SymbolTable::markSymbolGlobal(){
	list<Elem*>::iterator it = symbols.begin();
	for(int i = 0; i < symbols.size() - symbolList; i++){
		it++;
	}
	for(int i = 0; i < symbolList; i++){
		(*it)->scope = 1;
		it++;
	}
	symbolList = 0;
}

void SymbolTable::markSymbolExtern(){
	list<Elem*>::iterator it = symbols.begin();
	for(int i = 0; i < symbols.size() - symbolList; i++){
		it++;
	}
	for(int i = 0; i < symbolList; i++){
		(*it)->scope = 1;
		(*it)->section = 0;
		it++;
	}
	symbolList = 0;
}

void SymbolTable::initTable(){
	table.push_back(new Elem(numOfSect, "UND", numOfSect, 0, 0, 0));
	numOfSect++;
	table.push_back(new Elem(numOfSect, "ABS", numOfSect, 0, 0, 0));
	numOfSect++;
}

Elem* SymbolTable::findSymbolInTable(string sym){
	Elem* found = nullptr;
	for(list<Elem*>::iterator it = table.begin(); it != table.end(); it++){
		if((*it)->name == sym && (*it)->index >= numOfSect){
			found = (*it);
			break;
		}
	}
	return found;
}

void SymbolTable::addSymbol(string symb){
	bool exists = false;
	for(list<Elem*>::iterator it = table.begin(); it != table.end(); it++) {
		if((*it)->name == symb){
			exists = true;
			cout << "Greska, sekcija " << symb << " vec postoji!" << endl;
			System::setParserError();
			break;
		}
	}
	for(list<Elem*>::iterator it = symbols.begin(); it != symbols.end(); it++){
		if((*it)->name == symb){
			exists = true;
			if((*it)->scope == 1 && (*it)->section == UND){
				(*it)->section = currentSection;
				(*it)->value = 0;
				break;
			}else{
				cout << "Greska, simbol " << symb << " vec postoji!" << endl;
				System::setParserError();
				break;
			}
		}
	}
	if(!exists){
		symbols.push_back(new Elem(numOfSymb++, symb, currentSection, 0, 0, 0)); //vidi resi Value
		//cout << "U listi: " << symbols.back()->name << endl;
	}
}

void SymbolTable::addSection(string sect){
	bool exists = false;
	for(list<Elem*>::iterator it = table.begin(); it != table.end(); it++) {
		if((*it)->name == sect){
			exists = true;
			cout << "Greska, sekcija " << sect << " vec postoji!" << endl;
			System::setParserError();
			break;
		}
	}
	for(list<Elem*>::iterator it = symbols.begin(); it != symbols.end(); it++) {
		if((*it)->name == sect){
			exists = true;
			cout << "Greska, simbol " << sect << " vec postoji!" << endl;
			System::setParserError();
			break;
		}
	}
	if(!exists){
		currentSection = numOfSect;
		table.push_back(new Elem(numOfSect, sect, numOfSect, 0, 0, 0));
		numOfSect++;
	}
}

void SymbolTable::joinTable(){
	Elem* e = nullptr;
	int index = numOfSect;
	System::initMemory(table);
	while((e = symbols.front()) != nullptr){
		symbols.pop_front();
		e->index = index++;
		table.push_back(e);
	}
}

void SymbolTable::printSymbolTable(){
	cout << "Index |" << "Name     |" << "Section |" << "Value |" << "Size |" << "Scope" << endl;

	for(list<Elem*>::iterator it = table.begin(); it != table.end(); it++){
		cout << (*it)->index << "     |" << (*it)->name << "  |" << (*it)->section << "        |" << (*it)->value 
		<< "     |" << (*it)->size << "     |" << ((*it)->scope == 0 ? "local" : "global") << endl;
	}
	cout << endl;
}

void SymbolTable::addEQU(string equ){
	bool exists = false;
	for(list<Elem*>::iterator it = table.begin(); it != table.end(); it++) {
		if((*it)->name == equ){
			exists = true;
			cout << "Greska, sekcija " << equ << " vec postoji!" << endl;
			System::setParserError();
			break;
		}
	}
	for(list<Elem*>::iterator it = symbols.begin(); it != symbols.end(); it++){
		if((*it)->name == equ){
			exists = true;
			if((*it)->scope == 1 && (*it)->section == UND){
				(*it)->section = ABS;
				(*it)->value = lastLiteral;
				break;
			}else{
				cout << "Greska, simbol " << equ << " vec postoji!" << endl;
				System::setParserError();
				break;
			}
		}
	}
	if(!exists){
		symbols.push_back(new Elem(numOfSymb++, equ, ABS, lastLiteral, 0, 0)); //vidi resi Value
		//cout << "U listi: " << symbols.back()->name << endl;
	}
}

void SymbolTable::setLastLiteral(int num){
	lastLiteral = num;
}

int SymbolTable::getLastLiteral(){
	return lastLiteral;
}

bool SymbolTable::validSection(){
	if(currentSection != UND && currentSection != ABS)return true;
	else return false;
}

void SymbolTable::addSectionSize(){
	if(currentSection != UND && currentSection != ABS){
		for(list<Elem*>::iterator it = table.begin(); it != table.end(); it++){
			if((*it)->index == currentSection){
				(*it)->size = System::getLocationConter();
				System::resetLocationCounter();
				break;
			}
		}
	}
}

void SymbolTable::addLabelValue(string label){
	if(currentSection != UND && currentSection != ABS){
		for(list<Elem*>::iterator it = symbols.begin(); it != symbols.end(); it++){
			if((*it)->name == label){
				(*it)->value = System::getLocationConter();
				break;
			}
		}
	}
}





