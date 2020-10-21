#ifndef __TOKENIZER_STRUCT_H_
#define __TOKENIZER_STRUCT_H_

#include "./output_file_structs.h"

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


#endif // __TOKENIZER_STRUCT_H_
