
#include "gen_utils.h"
#include "grammar_structs.h"
#include "parse_tree.h"
#include "type_errors.h"
#include <stdlib.h>

void assert(bool condition, char *error_string) {
    if (!condition) {
        printf("ERROR: Assertion failed - %s\n", error_string);
        exit(1);
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

bool assert_debug(bool condition, char *error_string, Parse_tree_node *p,
                  char *t1, char *t2, char *operator, char * lex1,
                  char * lex2) {

    ErrorNode *er = (ErrorNode *)malloc(sizeof(ErrorNode));
    er->depth = p->depth;
    er->message = error_string;
    er->stmt_type = getStmtType(p);
    er->type1 = t1;
    er->type2 = t2;
    er->lex1 = lex1;
    er->lex2 = lex2;
    er->op = operator;
    while(!p->tok->lexeme.is_terminal){
        p = p->child;
    }
    er->line_num = p->tok->line_no;
    /* if (!condition) */
    /* { */
    /*     printf("ERROR: Assertion failed - %s\n", error_string); */
    /*     return false; */
    /* } */
    return condition;
}
