%{
#include<iostream>
#include "parser.h"
#include "inc/system.h"
#include "inc/parserDriver.h"
   int val;
   char *ident;
   
%}

%x COMMENT
%x ENDSTATE
%option yylineno
%option outfile="lexer.cpp" header-file="lexer.h"
%option noyywrap

%%

" "	{ }
"\b"	{ }
"\t"	{ }
"\r"	{ return NEWLINE; }
"\n"	{ return NEWLINE; }
"\f"	{ }


".global"	{ return GLOBAL; } 
".extern"	{ return EXTERN; } 
".section"	{ return SECTION;}
".word"	{ return WORD; }
".skip"	{ return SKIP; }
".equ"		{ return EQU; }
".end"		{ BEGIN(ENDSTATE); return END; }

"halt" 	{ return HALT; }
"int" 		{ return INT; }
"iret"		{ return IRET; }
"call"		{ return CALL; }
"ret"		{ return RET; }
"jmp" 		{ return JMP; }
"jeq"		{ return JEQ; }
"jne"		{ return JNE; }
"jgt"		{ return JGT; }
"push"		{ return PUSH; }
"pop"		{ return POP; }
"xchg"		{ return XCHG; }
"add"		{ return ADD; }
"sub"		{ return SUB; }
"mul"		{ return MUL; }
"div"		{ return DIV; }
"cmp"		{ return CMP; }
"not"		{ return NOT; }
"and"		{ return AND; }
"or"		{ return OR; }
"xor" 		{ return XOR; }
"test"		{ return TEST; }
"shl"		{ return SHL; }
"shr"		{ return SHR; }
"ldr"		{ return LDR; }
"str"		{ return STR; }

"r0" 		{ return R0; }
"r1" 		{ return R1; }
"r2" 		{ return R2; }
"r3" 		{ return R3; }
"r4" 		{ return R4; }
"r5" 		{ return R5; }
"r6" 		{ return R6; }
"r7" 		{ return R7; }
"sp"		{ return SP; }
"pc"		{ return PC; }
"psw"		{ return PSW; }


":"		{ return COLON; }
"," 		{ return COMMA; }
"$" 		{ return DOLLAR; }
"%"		{ return PERCENT; }
"*"		{ return STAR; }
"["		{ return LBRACKET; }
"]"		{ return RBRACKET; }
"+"		{ return PLUS; }


"#" 	    	{ BEGIN(COMMENT); }
<COMMENT>. 	{ BEGIN(COMMENT); }
<COMMENT>"\n" { BEGIN(INITIAL); return NEWLINE; }

<ENDSTATE>.	{ BEGIN(ENDSTATE); }

[1-9][0-9]*			{ val = atoi(yytext); yylval.val = val; return NUMBER; }
0[xX][0-9a-fA-F]+		{ yylval.str = strdup(yytext); return HEX; }
0[0-7]*			{ yylval.str = strdup(yytext); return OCTAL; }
([a-z]|[A-Z]|_)[a-zA-Z0-9_]*	{ ident = strdup(yytext); yylval.str = ident; return IDENT; }

. { std::cout << "Leksicka greska " << yytext << " u liniji " << yylineno << std::endl; System::setParserError(); return ERROR; }


%%

int
yyerror(const char* msg)
{
    fprintf(stderr, "Sintaksna greska na liniji %d ,info: %s\n", yylineno, msg);
    System::setParserError();
    return 0;
}
