/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef PRINT_H
#define PRINT_H

#include "type_exp_table.h"
#include<string.h>

void print_type_exp_table(type_exp_table *t);
char *get_str_decl_type(DeclarationType decl_type);
char *get_str_variable_type(VariableType variable_type);
#endif
