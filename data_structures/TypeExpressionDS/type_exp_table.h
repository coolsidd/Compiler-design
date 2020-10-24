/* Header guard */
#ifndef TYPE_EXP_TABLE_H
#define TYPE_EXP_TABLE_H
/***************/

#include <stdlib.h>
#include "../../util/gen_utils.h"
#include "../hash_map.h"
#include "type_expression.h"

typedef struct ____TYPE_EXPRESSION_TABLE_NODE____ txp_node;

typedef enum {PRIMITIVE_TYPE, RECT_ARRAY, JAGGED_ARRAY} VariableType;

typedef enum {NOT_APPLICABLE, STATIC, DYNAMIC} DeclarationType;

struct ____TYPE_EXPRESSION_TABLE_NODE____{
    char* variable_name;
    VariableType variable_type;
    DeclarationType declaration_type;
};

typedef struct ____TYPE_EXPRESSION_TABLE____ type_exp_table;

struct ____TYPE_EXPRESSION_TABLE____{
    txp_node* root; // should be a linked_list of txp_node(s)? But does it need to be ordered?
    hash_map symbol_table;
};

/* Function Prototypes */

// initialise the type expression table
type_exp_table* create_type_expression_table();
// get type expression of a variable
type_expression get_type_expression(type_exp_table* t, char* variable);
// add entry
void add_entry_to_table(type_exp_table* t, char* variable_name, VariableType var_type,
                        declaration_type decl_type, type_expression t);
// remove entry
void remove_entry_from_table(type_exp_table* t, char* variable_name);

#endif