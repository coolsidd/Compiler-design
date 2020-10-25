#include "../../final_code/grammar_structs.h"

typedef enum {BOOLEAN, INTEGER, REAL} primitive_type;

// to get primitive_type object from parse tree node
primitive_type* get_primitive_type(parse_tree_node* p);