#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_grammar.h"

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

void printGrammar(Grammar* g) {
    printf("Rules(%d): \n", g->num_rules);
    printf("-------------\n");
    for (int i=0;i<g->num_rules;i++) {
        printf("%s -> ", toStringSymbol((g->rules)[i].lhs));
        RuleNode* rnptr = (g->rules)[i].rhs;
        while (rnptr != NULL) {
            if ( (rnptr->s).is_terminal ) {
                printf("T<%s> ", toStringSymbol(rnptr->s));
            } else {
                printf("NT<%s> ", toStringSymbol(rnptr->s));
            }
            rnptr = rnptr->next;
        }
        printf("\n");
    }
}

void readGrammar(char *filename, Grammar* g){
    char* sep = " ";
	FILE* file = fopen(filename, "r");

    if (!file) {
        printf("File error!"); return;
    }

    Rule *rptr = NULL;

    char line[MAXLINELEN];
	while (fgets(line, MAXLINELEN, file)) {

        bool first = true;
        Rule rule_new;
        RuleNode *rn_head = NULL, *rn_ptr = NULL;

        char* tmp_line = strdup(line); // strtok destroys a string
        tmp_line = replace_char(tmp_line, '\n', '\0');
        tmp_line = replace_char(tmp_line, '\r', '\0');

        char* tok = strtok(tmp_line, sep); // read first token from the line
        while (tok) {
            if (first) {
                rule_new.lhs = toSymbol(tok);
                first = false;
            }
            else {
                RuleNode *rn_new = (RuleNode*)malloc(sizeof(RuleNode));
                rn_new->next = NULL;
                rn_new->s = toSymbol(tok);

                if (rn_ptr == NULL) {
                    rn_head = rn_new;
                    rn_ptr = rn_head;
                } else {
                    rn_ptr->next = rn_new;
                    rn_ptr = rn_ptr->next;
                }
            }
            printf("%s|", tok);
            tok = strtok(NULL, sep);
        } printf("\n");

        rule_new.rhs = rn_head;
        (g->rules)[(g->num_rules)++] = rule_new;

        free(tmp_line);
    }
}

/* int main() { */
/*     Grammar* g = (Grammar*)malloc(sizeof(Grammar)); */
/*     g->num_rules = 0; */
/*     g->start_symb = toSymbol("program"); */
/*     g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule)); */
/*     readGrammar("machine_grammar.txt", g); */
/*     printGrammar(g); */
/* } */
