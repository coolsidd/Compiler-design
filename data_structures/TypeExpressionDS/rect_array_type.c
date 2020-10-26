#include "rect_array_type.h"

rect_array_range* create_rect_array_node(int lower_bound, int upper_bound){
    rect_array_range* r_node = (rect_array_range*)calloc(1,sizeof(rect_array_range));
    r_node->lower_bound = lower_bound;
    r_node->upper_bound = upper_bound;
    return r_node;
}
void get_type_from_rangelist(Parse_tree_node *p, linked_list *ll)
{
    /*
        low: 2nd child
        high: 4th child
        iterate on basis of last child:
            (if range_list)
    */
    Parse_tree_node *low = p->child->next;
    Parse_tree_node *high = low->next->next;

    rect_array_range *r_node = create_rect_array_node(atoi(low->tok->token_name),
                                                      atoi(high->tok->token_name));
    ll_append(ll, r_node);
    Parse_tree_node *temp = high->next->next;
    if (temp && temp->tok->lexeme.s == range_list)
    {
        get_type_from_rangelist(temp, ll);
    }
}

rect_array_type* create_rect_array_type(Parse_tree_node* p){
    rect_array_type* r = (rect_array_type*)calloc(1,sizeof(rect_array_type));
    linked_list* ll = create_linked_list();
    r->array_ranges = ll;
    get_type_from_rangelist(p,r->array_ranges);
    r->dimensions = r->array_ranges->num_nodes;
    return r;
}

int get_dimension(rect_array_type* r_type){
    return r_type->dimensions;
}

