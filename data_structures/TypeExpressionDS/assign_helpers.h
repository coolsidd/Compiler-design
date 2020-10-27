#ifndef RECT_ARRAY_TYPE_H
#define RECT_ARRAY_TYPE_H

#include "type_exp_table.h"
#include "../../final_code/parse_tree.h"

type_expression *get_type_of_fact(type_exp_table *txp_table, Parse_tree_node *p);
type_expression *get_integer_type();
type_expression *get_real_type();
type_expression *get_bool_type();
type_expression *get_type_of_arithm_expr(type_exp_table *txp_table, Parse_tree_node *p);
type_expression *get_type_of_term(type_exp_table *txp_table, Parse_tree_node *p);
bool check_rect_dimensions(rect_array_type r1, rect_array_type r2);
bool check_jagged_dimensions(jagged_array_type j1, jagged_array_type j2);

#endif