/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#include "jagged_array_type.h"

jagged_2d* create_jagged_2d(){
    jagged_2d *j2d = (jagged_2d*)calloc(1, sizeof(jagged_2d));
    j2d->row_sizes = *create_r2_dimension();
    return j2d;
}

jagged_3d* create_jagged_3d(){
    jagged_3d *j3d = (jagged_3d*)calloc(1, sizeof(jagged_3d));
    j3d->row_sizes = create_linked_list();
    return j3d;
}

r2_dimension* create_r2_dimension(){
    r2_dimension* r2 = (r2_dimension*)calloc(1, sizeof(r2_dimension));
    r2->sizes = create_linked_list();
    return r2;
}

void append_size(linked_list *ll, int size){
    int *data = (int*)calloc(1, sizeof(int));
    *data = size;
    ll_append(ll, data);
}

void populate_row_sizes_2d(linked_list* ll, Parse_tree_node* p){
    Parse_tree_node *row_size_node = getNodeFromIndex(p, 6);
    int row_size = atoi(row_size_node->tok->token_name);
    // Parse_tree_node *row = row_size_node->next->next->next->next;
    // for(int i=0;i<row_size;i++){
    //     int value = atoi(row->child->child->tok->token_name);
    //     append_size(jat->array_type.j2d.row_sizes.sizes, value);
    // }
    append_size(ll, row_size);
    Parse_tree_node *last_child_1 = getNodeFromIndex(row_size_node, 6);
    if (last_child_1 && last_child_1->tok->lexeme.s == jagged2init)
    {
        populate_row_sizes_2d(ll, last_child_1);
    }
}

void populate_value_list(linked_list* ll, Parse_tree_node* p){
    // <value_list> -> <var> <value_list> | <var>
    int count = 1;
    Parse_tree_node* first_child = p->child;
    //Parse_tree_node* last_child = p->last_child;
    int num_child = p->num_children;
    while(num_child == 2){
        p = p->child->next;
        num_child = p->num_children;
        count++;
    }
    append_size(ll, count);
}

void populate_j3list(linked_list* ll, Parse_tree_node* p){

    // <j3list> -> <value_list> SEMICOLON <j3list> | <value_list>
    Parse_tree_node *first_child = p->child;
    // first_child = value_list
    populate_value_list(ll, first_child);

    if (first_child->next)
    {
        Parse_tree_node *last_child = getNodeFromIndex(first_child, 2);
        populate_j3list(ll, last_child);
    }
}

void populate_row_sizes_3d(linked_list *ll, Parse_tree_node *p)
{
    // p = jagged3init
    int size = atoi(getNodeFromIndex(p->child, 6)->child->tok->token_name);
    Parse_tree_node *row_node = getNodeFromIndex(p->child, 10);
    // row_node = j3list
    r2_dimension* r = create_r2_dimension();
    populate_j3list(r->sizes, row_node);
    ll_append(ll, r);

    Parse_tree_node *last_child_1 = getNodeFromIndex(row_node, 2);
    if (last_child_1 && last_child_1->tok->lexeme.s == jagged3init)
    {
        populate_row_sizes_3d(ll, last_child_1);
    }
}

jagged_array_type *create_jagged_array_type(Parse_tree_node *p){
    /*
        This function is called only if:
            there are no type errors(listed below) in the jagged_array
            - Index out of bounds for jaggedXinit. X=2,3
            - No of instances of jaggedXinit should be = UB-LB+1
            - For each row, size should be equal to be number of semicolon
                separated values.
            - For 2d, value_list cannot have last child as value_list
    */
    jagged_array_type* jat = (jagged_array_type*)calloc(1, sizeof(jagged_array_type));
    // p = jagged_array
    Parse_tree_node* third_child = getNodeFromIndex(p->child,2);
    // third_child = jagged2list or jagged3list
    Parse_tree_node *lower_bound = third_child->child->child->next;
    // lower_bound = var
    Parse_tree_node *upper_bound = getNodeFromIndex(lower_bound,2);
    // upper_bound = var
    Parse_tree_node* last_child = getNodeFromIndex(third_child,4);
    // last_child = jagged2init / jagged3init
    int l_bound = atoi(lower_bound->child->tok->token_name);
    int u_bound = atoi(upper_bound->child->tok->token_name);

    if(third_child->tok->lexeme.s == jagged2list){
        jat->dimensions = 2;
        jat->array_type.j2d = *create_jagged_2d();
        jat->array_type.j2d.lower_bound = l_bound;
        jat->array_type.j2d.upper_bound = u_bound;
        populate_row_sizes_2d(jat->array_type.j2d.row_sizes.sizes, last_child);
    }

    else{
        jat->dimensions = 3;
        jat->array_type.j3d = *create_jagged_3d();
        jat->array_type.j3d.lower_bound = l_bound;
        jat->array_type.j3d.upper_bound = u_bound;
        populate_row_sizes_3d(jat->array_type.j3d.row_sizes, last_child);
    }

    return jat;
}
