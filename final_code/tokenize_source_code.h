#ifndef __TOKENIZE_SOURCE_CODE_H_
#define __TOKENIZE_SOURCE_CODE_H_

#include "tokenizer_structs.h"
#include "read_grammar.h"
#include "util/output_file_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_char(char *str, char find, char replace) ;
void tokenizeSourceCode(char *filename, TokenStream *s);

#endif // __TOKENIZE_SOURCE_CODE_H_
