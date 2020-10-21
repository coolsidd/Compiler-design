#include "tokenizer_struct.h"
#include <stdlib.h>
#include <string.h>

Symbol toLex(char* lex_str){
    Symbol symb;
    symb.is_terminal=true;
    if(strcmp(lex_str, "{")){
        symb.s=CURLYOPEN;
        return symb;
    }
}

TokenStream *insertIntoStream(TokenStream *s, int line_num, char *token_str) {
    Token *newToken = (Token *)malloc(sizeof(Token));
    newToken->line_no = line_num;
    newToken->token_name = token_str;
    newToken->lexeme = toLex(char *token_str);
    s->tail->next = newToken;
    s->length++;
    return s;
}
TokenStream *newTokenStream();
void freeTokenStream(TokenStream *s);
