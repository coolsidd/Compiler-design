/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef __TOKENIZER_STRUCT_H_
#define __TOKENIZER_STRUCT_H_

#include "grammar_structs.h"

typedef struct token{
    int line_no;
    char *token_name;
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
int tokenizeSourceCode(char *filename, TokenStream *s);

char *replace_char(char *str, char find, char replace);
int tokenizeSourceCode(char *filename, TokenStream *s);

#endif // __TOKENIZER_STRUCT_H_
