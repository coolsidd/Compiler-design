#include "primitive_type.h"

t_primitive_type* get_primitive_type(Parse_tree_node* p){
    t_primitive_type* tp;
    char* ch = toStringSymbol(p->child->tok->lexeme);

    if(ch == "BOOLEAN"){
        *tp = t_BOOLEAN;
    }
    else if(ch == "INTEGER"){
        *tp = t_INTEGER;
    }
    else{
        *tp = t_REAL;
    }
    return tp;
}