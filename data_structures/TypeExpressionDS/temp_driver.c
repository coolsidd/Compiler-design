#include<stdlib.h>
#include "type_exp_table.h"
// gcc *.c ../linked_list.c ../hash_map.c ../../final_code/grammar_structs.c ../../final_code/parse_tree.c ../../util/gen_utils.c -o exe

int main(){
    rect_array_type* r = (rect_array_type*)calloc(1, sizeof(rect_array_type));
    r->dimensions = 2;
    r->array_ranges = create_linked_list();
    rect_array_range* r_node = create_rect_array_node(2, 5);
    ll_append(r->array_ranges, r_node);
    rect_array_range *r_node1 = create_rect_array_node(4, 7);
    ll_append(r->array_ranges, r_node1);
    printf("dimension of the array = %d, %d", r->dimensions, get_dimension(r));

    type_exp_table* t = create_type_expression_table();
    VariableType variable_type = RECT_ARRAY;
    union_to_be_named *u = (union_to_be_named *)calloc(1, sizeof(union_to_be_named));
    u->rect_array_data = *r;
    type_expression* txp = construct_type_expression(variable_type, *u);
    printf("%s",get_string_representation(txp));
    DeclarationType decl_type = STATIC;
    char* variable_name = "r";
    add_entry_to_table(t, variable_name, variable_type,
                       decl_type, txp);
    type_expression* txp2 = get_type_expression(t, variable_name);
    printf("%s",get_string_representation(txp2));
    
}