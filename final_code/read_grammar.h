#ifndef __READ_GRAMMAR_H_
#define __READ_GRAMMAR_H_

#include "./grammar.h"
#define MAXLINELEN 2048
#define MAXTOKLEN 50
#define MAXRULES 100

char* replace_char(char* str, char find, char replace);
void printGrammar(Grammar* g);
void readGrammar(char *filename, Grammar* g);

#endif // __READ_GRAMMAR_H_
