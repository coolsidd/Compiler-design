#include "primitive_type.h"

t_primitive_type* get_primitive_type(Parse_tree_node* p){
    t_primitive_type* tp = (t_primitive_type*)  malloc(sizeof(t_primitive_type));
    switch(p->child->tok->lexeme.s){
        case BOOLEAN:
        {
            *tp = t_BOOLEAN;
            break;
        }
        case INTEGER:
        {
            *tp = t_INTEGER;
            break;
        }
        case REAL:
        {
            *tp = t_REAL;
            break;
        }
    }
    return tp;
}
