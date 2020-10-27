// #include <stdbool.h>


#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <stdio.h>
#include "parse_tree.h"
#include "./type_errors.h"
#include "grammar_structs.h"
#include <stdlib.h>
#include <math.h>

void assert(bool condition, char *error_string);
bool assert_debug(bool condition, char* error_string, Parse_tree_node * p, char* t1, char* t2, char* operator, char* lex1, char* lex2);
#endif
