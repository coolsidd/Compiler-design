#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"
#define MAXLINELEN 2048
#define MAXTOKLEN 50

typedef struct node {
    int size;
    struct node* next;
} Node;

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

void readGrammar(char *filename, Grammar* g){
    char* sep = " ";
	FILE* file = fopen(filename, "r");

    if (!file) {
        printf("File error!"); return;
    }

    char line[MAXLINELEN];
	while (fgets(line, MAXLINELEN, file)) {
        char* tmp_line = strdup(line); // strtok destroys a string
        tmp_line = replace_char(tmp_line, '\n', '\0');
        tmp_line = replace_char(tmp_line, '\r', '\0');

        char* tok = strtok(tmp_line, sep); // read first token from the line
        while (tok) {
            printf("%s | ", tok);
            tok = strtok(NULL, sep);
        } printf("\n");
        free(tmp_line);
    }
}

int main() {
    Grammar* g = (Grammar*)malloc(sizeof(Grammar));
    g->num_rules = 0;
    g->start_symb = program;
    readGrammar("test.txt", g);
}
