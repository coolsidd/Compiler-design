/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <stdio.h>
#include "parse_tree.h"
/* #include "./type_errors.h" */
#include "grammar_structs.h"
#include "linked_list.h"
#include <stdlib.h>
#include <math.h>

extern linked_list * all_errors;

typedef struct en
{
    int line_num, depth;
    char *stmt_type, *op, *message;
    char *lex1, *lex2, *type1, *type2;
} ErrorNode;

void printErrorsHeader();
void printErrorEntries(ErrorNode *err);
void init_errors();
void print_all_errors();
void assert(bool condition, char *error_string);
bool assert_debug(bool condition, char* error_string, Parse_tree_node * p, char* t1, char* t2, char* operator, char* lex1, char* lex2);
#endif
