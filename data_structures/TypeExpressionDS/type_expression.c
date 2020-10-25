#include "type_expression.h"
#define MAX_BUFFER_SIZE 200

char* get_str_primitive_type(enum primitive_data){
    switch(primitive_data){
        case(BOOLEAN):
            return "Boolean";
            break;
        case(INTEGER):
            return "integer";
            break;
        case(REAL):
            return "real";
            break;
    }
}

// get the desired String Representation of TypeExpression
char* get_string_representation(type_expression* tp){

    union_to_be_named union_ds = tp->union_to_be_named;
    char result_buffer[MAX_BUFFER_SIZE];
    char* result = result_buffer;
    // snprintf(prefix, 100, "%s: %s: %s", argv[0], cmd_argv[0], cmd_argv[1]);

    switch(tp->variable_type){
        case(PRIMITIVE_TYPE):
        {
            result = snprintf(result, MAX_BUFFER_SIZE, "type = %s", get_str_primitive_type(union_ds->primitive_data));
            return result;
            break;
        }

        case(RECT_ARRAY):
        {
            /*
                <type=rectangularArray, dimensions=2, range_R1= (2, 5), range_R2 = (3, 6), basicElementType = integer>
            */
            linked_list* ll = union_ds->array_ranges;
            result = snprintf(result, MAX_BUFFER_SIZE, "type = rectangularArray, dimensions = %d, ", 
                                union_ds->num_nodes);
            for(int i=1;i<=num_nodes;i++){
                rect_array_range* r = (rect_array_range*)ll_get(ll, i);
                result = snprintf(result, MAX_BUFFER_SIZE, "range_R%d= (%d,%d), basicElementType = integer", 
                                    i,r->lower_bound, r->upper_bound);
            }
            return result;
            break;
        }
        
        case(JAGGED_ARRAY):
        {
            result = snprintf(result, MAX_BUFFER_SIZE, "type = jaggedArray");
            return result;
            break;
        }
    }
}

// set is_declared to true on encountering decl_stmt
void set_declare_flag(type_expression* tp){
    tp->is_declared = true;
}

type_expression construct_type_expression(VariableType variable_type, union_to_be_named* union_ds){

    type_expression* tp = (type_expression*)calloc(1, sizeof(type_expression));
    set_declare_flag(tp);
    tp->union_to_be_named = union_ds;
    return tp;
}

/*
    construct_type_expression:=
        tp = allocate memory for tp
        set_declare_flag(tp)
        variable_type 
            primitive: assign enum value based on lexeme value
            rect_array: ll_append(rect_array_node[Lb,Up])

    variable_type->
        create PrimitiveType
    primitive:
        lexeme: int, real, bool
    rect:
        create_rect_
        RectArrayType

    jagged:

    variableType:

    
    type_expression* tp = construct_type_expression(variable_name, u);
    add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);

*/
union_to_be_named* populate_union(VariableType variable_type, parse_tree_node* p):
        union_to_be_named* u = (union_to_be_named*)calloc(1,sizeof(union_to_be_named));
        switch(variableType){
            case(PRIMITIVE_TYPE):
            {
                u = get_primitive_type(parse_tree_node* p);   
                break;
            }
            case(RECT_ARRAY):
            {
                u = create_rect_array_type(parse_tree_node* p);
                break;
            }
            case(JAGGED_ARRAY):
            {
                u = create_jagged_array_type(parse_tree_node* p);
                break;
            }
        }