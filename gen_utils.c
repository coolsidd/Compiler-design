/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#include "linked_list.h"
#include <stdio.h>


#include "gen_utils.h"
#include "grammar_structs.h"
#include "parse_tree.h"
#include <stdlib.h>

linked_list * all_errors = NULL;

void assert(bool condition, char *error_string) {
    if (!condition) {
        printf("ERROR: Assertion failed - %s\n", error_string);
        exit(1);
    }
}

void printErrorsHeader()
{
    printf("\n%45s","|Error Statements Table|");
    printf("\n|%5s|%10s|%10s|%10s|%10s|%20s|%10s|%5s|%40s|\n",
           "num", "stmt type", "operator", "lexeme 1", "type 1",
           "lexeme 2", "type 2", "depth", "error message");
}

void printErrorEntries(ErrorNode* err){

    if (err != NULL)
    {
        printf("|"KCYN"%5d"RESET"|%10s|%10s|%10s|"KRED"%10s"RESET"|%20s|"KRED"%10s"RESET"|%5d|"KRED"%40s"RESET"|\n",
               err->line_num, err->stmt_type, err->op, err->lex1, err->type1,
               err->lex2, err->type2, err->depth, err->message);
    }
}

char *getStmtType(Parse_tree_node *p) {
    while (p || p->depth >1) {
        switch (p->tok->lexeme.s) {
            case decl_stmts: {
                return "decl stmt";
                break;
            }
            case assign_stmts: {
                return "assgn stmt";
                break;
            }
            case main_program : {
                return "UNKNOWN";
                break;
            }
        }
        p = p->parent;
    }
    return "UNKNOWN";
}

void init_errors(){
    if(all_errors){
        ll_node* head = all_errors->head;
        while(head){
            all_errors->head = all_errors->head->next;
            free(head);
            head = all_errors->head;
        }
        free(all_errors);
    }
    all_errors = create_linked_list();
}

bool assert_debug(bool condition, char *error_string, Parse_tree_node *p,
                  char *t1, char *t2, char *operator, char *lex1,
                  char *lex2) {

    if(!condition){
        ErrorNode *er = (ErrorNode *)malloc(sizeof(ErrorNode));
    er->depth = p->depth;
    er->message = error_string;
    er->stmt_type = getStmtType(p);
    er->type1 = t1;
    er->type2 = t2;
    er->lex1 = lex1;
    er->lex2 = lex2;
    er->op = operator;
    Parse_tree_node *temp1 = (Parse_tree_node *)calloc(1, sizeof(Parse_tree_node));
    temp1 = p;
    while (!temp1->tok->lexeme.is_terminal)
    {
        temp1 = temp1->child;
    }
    er->line_num = temp1->tok->line_no;
    //printErrorEntries(er);
    if(!all_errors)
        init_errors();
    ll_append(all_errors, er);
    return false;
    }
    return true;
}

void print_all_errors(){
    if(!all_errors)
        return;
    printErrorsHeader();
    for(ll_node *head = all_errors->head; head; head=head->next){
        printErrorEntries((ErrorNode *)head->data);
    }
}
