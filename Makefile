SRCS = src/main.cpp src/parserDriver.cpp src/system.cpp src/symbolTable.cpp parser.cpp lexer.cpp
CC = g++

test: all
	./asembler

all: $(SRCS) inc/parserDriver.h
	$(CC) $(SRCS) -o asembler

# pravi lexer.c i lexer.h fajlove
lexer.cpp: src/lexer.lex inc/parserDriver.h
	flex src/lexer.lex

# pravi bison.c i bison.h fajlove
parser.cpp: src/parser.y src/lexer.lex inc/parserDriver.h
	bison -d src/parser.y

clean:
	rm -rf *.o lexer.cpp lexer.h parser.cpp parser.h asembler
