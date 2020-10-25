#include "primitive_type.h"

t_primitive_type* get_primitive_type(Parse_tree_node* p){
    t_primitive_type* p;
    char* ch = toStringSymbol(p->child->tok->lexeme);

    if(ch == "BOOLEAN"){
        p = t_BOOLEAN;
    }
    else if(ch == "INTEGER"){
        p = t_INTEGER;
    }
    else{
        p = t_REAL;
    }
    return p;
}