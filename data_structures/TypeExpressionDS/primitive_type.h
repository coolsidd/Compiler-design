#include "../../final_code/grammar_structs.h"
#include "../../final_code/parse_tree.h"
typedef enum {BOOLEAN, INTEGER, REAL} primitive_type;

// to get primitive_type object from parse tree node
primitive_type* get_primitive_type(Parse_tree_node* p);