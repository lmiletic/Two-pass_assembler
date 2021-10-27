
%{
	#include "inc/parserDriver.h"
	#include <iostream>
	#define YYDEBUG 1
	int yylex(void);
	void yyerror(const char*);
%}

%debug

%output "parser.cpp"
%defines "parser.h"

%union { 
  int val;
  char* str;
}

%token GLOBAL
%token EXTERN
%token SECTION
%token WORD
%token SKIP
%token EQU
%token END
%token ERROR

%token COLON
%token NEWLINE
%token COMMA

%token<str> OCTAL
%token<str> HEX
%token<val> NUMBER
%token<str> IDENT

%token DOLLAR
%token PERCENT
%token STAR
%token LBRACKET
%token RBRACKET
%token PLUS

%token HALT
%token INT
%token IRET
%token CALL
%token RET
%token JMP
%token JEQ
%token JNE
%token JGT
%token PUSH
%token POP
%token XCHG
%token ADD
%token SUB
%token MUL
%token DIV
%token CMP
%token NOT
%token AND
%token OR
%token XOR
%token TEST
%token SHL
%token SHR
%token LDR
%token STR

%token R0
%token R1
%token R2
%token R3
%token R4
%token R5
%token R6
%token R7
%token SP
%token PC
%token PSW

%%
 
Program : LineList END
	{ psEnd(); };
 
LineList : LineList Line
	 | /*epsilon*/;
	 
Line : NEWLINE
     | Directive NEWLINE
     	{ directiveDone(); }	
     | Statement NEWLINE
     	{ statementDone(); }
     | Label NEWLINE;
		      
Label : LabelName Statement
      | LabelName Directive
      | LabelName;

LabelName : IDENT COLON
	    { psLabelName($1); };

Directive : GLOBAL SymbolList
		{ psGlobal(); }
	  | EXTERN SymbolList
	  	{ psExtern(); }
	  | SECTION IDENT
	  	{ beginSection($2); }
	  | WORD WordList
	  	{ psWord(); }
	  | SKIP Literal
	  	{ psSkip(); }
	  | EQU IDENT COMMA Literal
	  	{ psEQU($2); };

SymbolList : SymbolList COMMA IDENT
		{ readSymbol($3); }
	    | IDENT
	    	{ readSymbol($1); };
	    
WordList : WordList COMMA SymbolLiteral
	 | SymbolLiteral;
	 
SymbolLiteral : IDENT
		{ processSymbol($1); }
	       | Literal;
	    
Literal : NUMBER
	  { psLiteralNUM($1); }
	| HEX
	  { psLiteralHEX($1); }
	| OCTAL
	  { psLiteralOCTAL($1); };
	
Statement : HALT
		{ psHalt(); }
	  | INT RegX
	  	{ psInt(); }
	  | IRET
	  	{ psIret(); }
	  | CALL OperandJump
	  	{ psCall(); }
	  | RET
	  	{ psRet(); }
	  | JMP OperandJump
	  	{ psJmp(); }
	  | JEQ OperandJump
	  	{ psJeq(); }
	  | JNE OperandJump
	  	{ psJne(); }
	  | JGT OperandJump
	  	{ psJgt(); }
	  | PUSH RegX
	  	{ psPush(); }
	  | POP RegX
	  	{ psPop(); }
	  | XCHG RegX COMMA RegX
	  	{ psXchg(); }
	  | ADD RegX COMMA RegX
	  	{ psAdd(); }
	  | SUB RegX COMMA RegX
	  	{ psSub();}
	  | MUL RegX COMMA RegX
	  	{ psMul(); }
	  | DIV RegX COMMA RegX
	   	{ psDiv(); }
	  | CMP RegX COMMA RegX
	  	{ psCmp(); }
	  | NOT RegX 
	  	{ psNot(); }
	  | AND RegX COMMA RegX
	  	{ psAnd(); }
	  | OR RegX COMMA RegX
	  	{ psOr(); }
	  | XOR RegX COMMA RegX
	  	{ psXor(); }
	  | TEST RegX COMMA RegX
	  	{ psTest(); }
	  | SHL RegX COMMA RegX
	  	{ psShl(); }
	  | SHR RegX COMMA RegX
	  	{ psShr(); }
	  | LDR RegX COMMA OperandState
	  	{ psLdr(); }
	  | STR RegX COMMA OperandState
	  	{ psStr(); };
	  
OperandState : DOLLAR Literal
		{ dataDolLiteral(); }
	     | DOLLAR IDENT
	     	{ dataDolIdent($2); }
	     | Literal
	     	{ dataLiteral(); }
	     | IDENT
	     	{ dataIdent($1); }
	     | PERCENT IDENT
	     	{ dataPercIdent($2); }
	     | RegX 
	     	{ dataReg(); }
	     | LBRACKET RegX RBRACKET
	     	{ dataBracReg(); }
	     | LBRACKET RegX PLUS Literal RBRACKET
	     	{ dataBracRegPlusLiteral(); }
	     | LBRACKET RegX PLUS IDENT RBRACKET
	     	{ dataBracRegPlusIdent($4); };
	     
	
OperandJump :  Literal
		{ jmpLiteral(); }
	     | IDENT
	     	{ jmpIdent($1); }
	     | PERCENT IDENT
	     	{ jmpPercIdent($2); }
	     | STAR Literal
	     	{ jmpStarLiteral(); }
	     | STAR IDENT
	     	{ jmpStarIdent($2); }
	     | STAR RegX 
	     	{ jmpStarReg(); }
	     | STAR LBRACKET RegX RBRACKET
	     	{ jmpBracReg(); }
	     | STAR LBRACKET RegX PLUS Literal RBRACKET
	     	{ jmpBracRegPlusLiteral(); }
	     | STAR LBRACKET RegX PLUS IDENT RBRACKET
	     	{ jmpBracRegPlusIdent($5); };

RegX : R0
	{ addRegister(0); }
     | R1
     	{ addRegister(1); }
     | R2
     	{ addRegister(2); }
     | R3
     	{ addRegister(3); }
     | R4
     	{ addRegister(4); }
     | R5
     	{ addRegister(5); }
     | R6
     	{ addRegister(6); }
     | R7
     	{ addRegister(7); }
     | PC
     	{ addRegister(7); }
     | SP
     	{ addRegister(6); }
     | PSW
     	{ addRegister(8); };
	 
%%
