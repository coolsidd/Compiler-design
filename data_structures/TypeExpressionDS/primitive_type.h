#include "../../final_code/parse_tree.h"
#ifndef PRIMITITVE_TYPE_H
#define PRIMITITVE_TYPE_H
typedef enum {t_BOOLEAN, t_INTEGER, t_REAL} t_primitive_type;

// to get primitive_type object from parse tree node
t_primitive_type* get_primitive_type(Parse_tree_node* p);

#endif