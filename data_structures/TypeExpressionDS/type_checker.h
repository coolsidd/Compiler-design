/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef __TYPE_CHECKER_H_
#define __TYPE_CHECKER_H_

#include "./type_exp_table.h"

bool jagged_init_checker(type_exp_table *txp_table, Parse_tree_node *p, int idx);
bool jagged_list_checker(type_exp_table *txp_table, Parse_tree_node *p);

#endif // __TYPE_CHECKER_H_
