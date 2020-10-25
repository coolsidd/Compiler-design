#include "jagged_array_type.h"

jagged_array_type *create_jagged_array_type(Parse_tree_node *p)
{
    jagged_array_type *r = (jagged_array_type *)calloc(1, sizeof(jagged_array_type));
    return r;
}

