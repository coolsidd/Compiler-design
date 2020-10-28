/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#include "rect_array_type.h"

rect_array_range* create_rect_array_node(int lower_bound, int upper_bound){
    rect_array_range* r_node = (rect_array_range*)calloc(1,sizeof(rect_array_range));
    r_node->lower_bound = lower_bound;
    r_node->upper_bound = upper_bound;
    return r_node;
}
void get_type_from_rangelist(Parse_tree_node *p, linked_list *ll)
{
    do{
    Parse_tree_node *low = getNodeFromIndex(p->child, 1);
    Parse_tree_node *high = getNodeFromIndex(low, 2);
    rect_array_range *r_node = create_rect_array_node(atoi(low->child->tok->token_name),
                                                      atoi(high->child->tok->token_name));
    ll_append(ll, r_node);
    p = getNodeFromIndex(high, 2);
    }while(p && p->tok->lexeme.s == range_list);
}

rect_array_type* create_rect_array_type(Parse_tree_node* p){
    rect_array_type* r = (rect_array_type*)calloc(1,sizeof(rect_array_type));
    linked_list* ll = create_linked_list();
    r->array_ranges = ll;
    get_type_from_rangelist(p->child->next,r->array_ranges); // p->child->next is rangelist
    r->dimensions = r->array_ranges->num_nodes;
    return r;
}

int get_dimension(rect_array_type* r_type){
    return r_type->dimensions;
}
