#include "rect_array_type.h"
#include "../../final_code/parse_tree.h"

rect_array_type* create_rect_array_type(parse_tree_node* p){
    // rect_array_type* r =
    /*
        traversing p:
            if p->child[5]->tok.lexeme.s==range_list:
    */
}

linked_list* get_type_from_rangelist(parse_tree_node* p){
    parse_tree_node* low = p->child->next;

    if(p->last_child->tok->lexeme->s==range_list){
        get_type_from_rangelist
    }
}