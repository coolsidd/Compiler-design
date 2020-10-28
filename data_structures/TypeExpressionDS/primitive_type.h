/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef PRIMITIVE_TYPE_H
#define PRIMITIVE_TYPE_H

#include "../../final_code/parse_tree.h"

typedef enum {t_BOOLEAN, t_INTEGER, t_REAL} t_primitive_type;

// to get primitive_type object from parse tree node
t_primitive_type* get_primitive_type(Parse_tree_node* p);

#endif
