/* Header guard */

/***************/

#include <stdlib.h>
#include "../../util/gen_utils.h"
#include "type_expression.h"

#ifndef TYPE_EXP_TABLE_H
#define TYPE_EXP_TABLE_H

typedef struct ____TYPE_EXPRESSION_TABLE_NODE____ txp_table_node;

typedef enum {NOT_APPLICABLE, STATIC, DYNAMIC} DeclarationType;

struct ____TYPE_EXPRESSION_TABLE_NODE____{
    char* variable_name;
    VariableType variable_type;
    DeclarationType declaration_type;
};

typedef struct ____TYPE_EXPRESSION_TABLE____ type_exp_table;

struct ____TYPE_EXPRESSION_TABLE____{
    linked_list* root; // should be a linked_list of txp_table_node(s)? But does it need to be ordered?
    hash_map* symbol_table;
};

/* Function Prototypes */

// initialise the type expression table
type_exp_table* create_type_expression_table();

// get type expression of a variable
type_expression* get_type_expression(type_exp_table* txp_table, char* variable);

// add entry to symbol table
void add_to_symbol_table(hash_map* symbol_table, char* variable_name, type_expression* txp);

// add entry to type expression table
void add_entry_to_table(type_exp_table *txp_table, char *variable_name, VariableType var_type,
                        DeclarationType decl_type, type_expression* t);

// // remove entry
// void remove_entry_from_table(type_exp_table* txp_table, char* variable_name);

// // delete txp_table_node corresponding to a variable_name
// void ll_delete_txp_node(linked_list* root, char* variable_name);

// // get index of a txp_node in linked_list* root corresponding to a variable name
// int ll_get_index_by_var(linked_list* root, char* variable_name);

#endif