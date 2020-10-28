/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer_structs.h"
#define MAXLINELEN 2048

char *trim(char *s) {
    while(isspace(*s)) s++;

    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return strdup(s);
}

int tokenizeSourceCode(char *filename, TokenStream *s) {
    char *sep = " ";
    FILE *file = fopen(filename, "r");
    int line_num = 0;

    if (!file) {
        printf("Tokenizer: File error!\n");
        return 0;
    }

    char line[MAXLINELEN];
    while (fgets(line, MAXLINELEN, file)) {
        line_num++;
        char *tmp_line = strdup(line); // strtok destroys a string
        tmp_line = replace_char(tmp_line, '\n', '\0');
        tmp_line = replace_char(tmp_line, '\r', '\0');

        //printf("%d: ", line_num);
        char *tok = strtok(tmp_line, sep); // read first token from the line
        while (tok) {
            char* new_tok = strdup(tok);
            //printf("`%s` | ", trim(new_tok));
            char * next_tok = trim(new_tok);
            if (*next_tok) insertIntoStream(s, line_num, strdup(next_tok));
            free(new_tok);
            free(next_tok);
            tok = strtok(NULL, sep); // read next token
        } //printf("\n");
    }

    return 1;
}
