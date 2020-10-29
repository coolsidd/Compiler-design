/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#include "tokenizer_structs.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void freeTokenStream(TokenStream *s){
    Token * temp = s->head;
    while(s->head){
        s->head = s->head->next;
        free(temp);
        temp= s->head;
    }
    free(s);
}

TokenStream *insertIntoStream(TokenStream *s, int line_num, char *token_str) {
    // printf("inserting \"%s\"\n", token_str);
    Token *newToken = (Token *)malloc(sizeof(Token));
    newToken->line_no = line_num;
    newToken->token_name = token_str;
    newToken->lexeme = toSymbol(token_str);
    if (newToken->lexeme.s == UNKNOWN) {
        char *temp = token_str;
        bool flag = false;
        while (*temp) {
            //printf("flag : %d\n", flag);
            if (isdigit(*temp)) {
                temp++;
                continue;
            } else {
                flag = true;
                break;
            }
        }
        if (flag) {
            char *temp = token_str;
            bool flag = false;
            if (isalpha((char)*temp) && strlen(temp) <= 20) {
                newToken->lexeme.s = ID;
                newToken->lexeme.is_terminal = true;
            } else {
                printf("ERROR parsed an invalid token \"%s\"\n", token_str);
            }
        } else {
            newToken->lexeme.s = CONST;
            newToken->lexeme.is_terminal = true;
        }
    }
    // printf("inserted \"%s\"",toStringSymbol(newToken->lexeme));
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

void deleteHead(TokenStream *s) {
    if (!s->head) {
        printf("ERROR DELETING HEAD OF SIZE 0");
        return;
    }
    Token *temp = s->head->next;
    free(s->head);
    s->head = temp;
    s->length--;
}

void deleteTail(TokenStream *s) {
    if (!s->head) {
        printf("ERROR DELETING TAIL OF SIZE 0");
        return;
    }
    s->length--;
    Token *temp = s->head;
    if (!temp->next) {
        free(temp);
        s->head = NULL;
        s->tail = NULL;
        return;
    }
    while (temp->next->next) {
        temp = temp->next;
    }
    s->tail = temp;
    free(temp->next);
    s->tail->next = NULL;
}
