/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#include "type_exp_table.h"

#define DEFAULT_TXP_TABLE_SIZE 60

type_exp_table* create_type_expression_table(){
    type_exp_table* txp_table = calloc(1, sizeof(type_exp_table));
    txp_table->root = create_linked_list();
    txp_table->symbol_table = create_hash_map(DEFAULT_TXP_TABLE_SIZE);

    return txp_table;
}

/* If key not found: this returns NULL
    So, while traversing parse tree we will raise error in this case.
    To get, string representation of this type_expression(say txp), we can call
    get_string_representation(txp); */
type_expression* get_type_expression(type_exp_table* txp_table, char* variable_name){
    hash_map* symbol_table = txp_table->symbol_table;
    type_expression* txp = (type_expression*)fetch_from_hash_map(symbol_table, variable_name);
    return txp;
}

/*
    Add entry to symbol_table <-> symbol_table[variable_name] = txp;
*/
void add_to_symbol_table(hash_map* symbol_table, char* variable_name, type_expression* txp){
    add_to_hash_map(symbol_table, variable_name, txp);
}

/*
    On encountering a decl statement in parse tree,
    var_type would be decided based on lexeme(category of token)
    decl_type would be decided based on var_type
    we would call construct_type_expression(*args) to get type_expression of variable.
    finally call this function with all the above fields.
*/
void add_entry_to_table(type_exp_table *txp_table, char *variable_name,
                        VariableType var_type, DeclarationType decl_type, type_expression* txp)
{

    txp_table_node* ttn = calloc(1, sizeof(txp_table_node));
    ttn->variable_name = variable_name;
    ttn->variable_type = var_type;
    ttn->declaration_type = decl_type;
    ll_append(txp_table->root, ttn);
    add_to_symbol_table(txp_table->symbol_table, variable_name, txp);
}

// Below functions wont be used.
/* delete txp_table_node corresponding to a variable_name
    Should We raise an error if the var_name's node not present
*/
// void ll_delete_txp_node(linked_list* root, char* variable_name){
//     int idx = ll_get_index_by_var(root, variable_name);
//     ll_remove_at(root, idx);
// }

// /*
//     To remove a variable's entry from Type Expression Table,
//     we need to remove it from both linked_list of txp_table_node(s)
//     as well as symbol_table
//     To raise error if not found or no?
// */
// void remove_entry_from_table(type_exp_table* txp_table, char* variable_name){
//     remove_from_hash_map(txp_table->symbol_table, variable_name);
//     // remove txp_table_node corresponding to variable_name
//     ll_delete_txp_node(txp_table->root, variable_name);

// }
