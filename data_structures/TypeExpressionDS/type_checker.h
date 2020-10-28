#ifndef __TYPE_CHECKER_H_
#define __TYPE_CHECKER_H_

#include "./type_exp_table.h"

bool jagged_init_checker(type_exp_table *txp_table, Parse_tree_node *p, int idx);
bool jagged_list_checker(type_exp_table *txp_table, Parse_tree_node *p);

#endif // __TYPE_CHECKER_H_
