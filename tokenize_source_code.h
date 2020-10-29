/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef __TOKENIZE_SOURCE_CODE_H_
#define __TOKENIZE_SOURCE_CODE_H_

#include "tokenizer_structs.h"
#include "read_grammar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_char(char *str, char find, char replace) ;
void tokenizeSourceCode(char *filename, TokenStream *s);

#endif // __TOKENIZE_SOURCE_CODE_H_
