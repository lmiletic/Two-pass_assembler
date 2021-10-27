#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "../lexer.h"
#include "../parser.h"
#include "../inc/system.h"
#include "../inc/parserDriver.h"
#include "../inc/symbolTable.h"

//#define YYDEBUG 1

using namespace std;


int main(int argc,char* argv[]){

  FILE *fileInput;
  FILE *fileOutput;
  string outputName = "output_file.txt";

  if(argc == 4 || argc == 2){
    if(argc == 2){
      fileInput = fopen(argv[1],"r");
    }else{
      if(strcmp(argv[1],"-o")==0){
        outputName = argv[2];
        fileInput = fopen(argv[3],"r");
      }else{
        cout << "Pogresni argumenti za pokretanje" << endl;
        return -1;
      }
    }
    if (!fileInput) {
        cout << "Nije moguce otvoriti ulazni fajl!" << endl;
        return -1;
    }else{
        
        yyin = fileInput;
  
        //yydebug = 1; 
        System::setFirstPass();
        yyparse();
        yylex_destroy();
  
        if(!System::getParserError()){
          System::setSecondPass();
          rewind(fileInput);
          yyin = fileInput;
          yyparse();
          yylex_destroy();
          if(!System::getParserError()){
            cout << "Program Done" << endl;
            fileOutput = freopen(outputName.c_str(), "w", stdout);
            System::printFile();
            fclose(fileOutput);
          }else{
            cout << "Doslo je do greske prilikom parsiranja" << endl;
          }
        }else{
          cout << "Doslo je do greske prilikom parsiranja" << endl;
        }
        fclose(fileInput);
    }
  }else{
    cout << "Pogresni argumenti za pokretanje" << endl;
  }
  return 0;
}
