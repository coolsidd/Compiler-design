
#include "gen_utils.h"
#include "parse_tree.h"
#include "type_errors.h"
#include <stdlib.h>

void assert(bool condition, char *error_string)
{
    if (!condition)
    {
        printf("ERROR: Assertion failed - %s\n", error_string);
        exit(1);
    }
}

bool assert_debug(bool condition, char* error_string, Parse_tree_node * p, char* t1, char* t2, char* operator)
{

    ErrorNode *er = (ErrorNode*) malloc(sizeof(ErrorNode));
    er->depth = p->depth;
    er->stmt_type = getStmtType(p);
    er->type1 = t1;
    er->type2 = t2;
    er->line_num = p->tok->
    /* if (!condition) */
    /* { */
    /*     printf("ERROR: Assertion failed - %s\n", error_string); */
    /*     return false; */
    /* } */
    return true;
}
