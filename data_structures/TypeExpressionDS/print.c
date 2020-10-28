#include "print.h"

char *get_str_decl_type(DeclarationType decl_type)
{
    switch (decl_type)
    {
    case (NOT_APPLICABLE):
    {
        return "Not Applicable";
        break;
    }
    case (STATIC):
    {
        return "Static";
        break;
    }
    case (DYNAMIC):
    {
        return "Dynamic";
        break;
    }
    }
}

char *get_str_variable_type(VariableType variable_type)
{
    switch (variable_type)
    {
    case (PRIMITIVE_TYPE):
    {
        return "Primitive Type";
        break;
    }
    case (RECT_ARRAY):
    {
        return "Rectangular Arr";
        break;
    }
    case (JAGGED_ARRAY):
    {
        return "Jagged Arr";
        break;
    }
    }
}

void print_type_exp_table(type_exp_table *t)
{
    printf("\n%45s","|Type Expression Table|\n\n");
    printf("\n%-15s| %-17s| %-15s| %-40s|\n",
           "Variable Name", "Variable Type", "Static/Dynamic", "Type Expression");
    printf("%-15s| %-17s| %-15s| %-40s\n",
          "=============", "=============", "==============", "===============");

    linked_list *ll = t->root;
    hash_map *hm = t->symbol_table;
    VariableType v_temp;
    DeclarationType d_temp;
    type_expression *txp;
    char var_name_buffer[30];
    char *var_name = var_name_buffer;
    char var_type_buffer[20];
    char *var_type = var_type_buffer;
    char decl_type_buffer[20];
    char *decl_name = decl_type_buffer;
    char txp_buffer[200];
    char *txp_str = txp_buffer;
    for (int i = 0; i < ll->num_nodes; i++)
    {
        txp_table_node *txp_node = (txp_table_node *)ll_get(ll, i);

        var_name = txp_node->variable_name;

        v_temp = txp_node->variable_type;
        strcpy(var_type, get_str_variable_type(v_temp));

        d_temp = txp_node->declaration_type;
        strcpy(decl_name, get_str_decl_type(d_temp));

        txp = get_type_expression(t, var_name);
        strcpy(txp_str, get_string_representation(txp));

        printf("%-15s| %-17s| %-15s| %-40s\n",
               var_name,
               var_type,
               decl_name,
               txp_str);
    }
}
