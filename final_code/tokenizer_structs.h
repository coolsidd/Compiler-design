#ifndef __TOKENIZER_STRUCT_H_
#define __TOKENIZER_STRUCT_H_

#include "grammar_structs.h"

typedef struct token{
    int line_no;
    char * token_name;
    Symbol lexeme;
    struct token *next;
} Token;

typedef struct tokenStream{
    Token *head;
    Token *tail;
    int length;
} TokenStream;

TokenStream* insertIntoStream(TokenStream *s, int line_num, char *token_str);
TokenStream* newTokenStream();
void freeTokenStream(TokenStream* s);
void tokenizeSourceCode(char *filename, TokenStream *s);

char *replace_char(char *str, char find, char replace);
void tokenizeSourceCode(char *filename, TokenStream *s);

#endif // __TOKENIZER_STRUCT_H_
