/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

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
