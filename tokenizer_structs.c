#include "tokenizer_structs.h"
#include <stdlib.h>
#include <string.h>

TokenStream *insertIntoStream(TokenStream *s, int line_num, char *token_str) {
    Token *newToken = (Token *)malloc(sizeof(Token));
    newToken->line_no = line_num;
    newToken->token_name = token_str;
    newToken->lexeme = toSymbol(token_str);
    newToken->next = NULL;
    if (s->tail) {
        s->tail->next = newToken;
        s->tail = s->tail->next;
        s->length++;
        return s;
    }
    s->head = newToken;
    s->tail = newToken;
    s->length++;
    return s;
}

TokenStream *newTokenStream() {
    TokenStream *s = (TokenStream *)malloc(sizeof(TokenStream));
    s->head = NULL;
    s->tail = NULL;
    s->length = 0;
    return s;
}
void freeTokenStream(TokenStream *s){
    while(s->head){
        Token *temp = s->head->next;
        free(s->head);
        s->head = temp;
    }

}
void deleteHead(TokenStream *s){
    if(!s->head){
        printf("ERROR DELETING HEAD OF SIZE 0");
        return;
    }
    Token *temp = s->head->next;
    free(s->head);
    s->head = temp;
    s->length--;
}

void deleteTail(TokenStream *s){
    if(!s->head){
        printf("ERROR DELETING TAIL OF SIZE 0");
        return;
    }
    s->length--;
    Token *temp = s->head;
    if(!temp->next){
        free(temp);
        s->head = NULL;
        s->tail = NULL;
        return;
    }
    while(temp->next->next){
        temp = temp->next;
    }
    s->tail = temp;
    free(temp->next);
    s->tail->next = NULL;

}
