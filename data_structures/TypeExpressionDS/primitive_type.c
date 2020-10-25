#include "primitive_type.h"

primitive_type* get_primitive_type(parse_tree_node* p){
    primitive_type* p;
    char* ch = toStringSymbol(p->child->tok->lexeme->s);

    if(ch == "BOOLEAN"){
        p = BOOLEAN;
    }
    else if(ch == "INTEGER"){
        p = INTEGER;
    }
    else{
        p = REAL;
    }
    return p;
}