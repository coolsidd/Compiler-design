#include "type_expression.h"

// char* get_str_variable_type(enum variable_type){
//     char* res;
//     if(variable_type == PRIMITIVE_TYPE){
//         res = "";
//     }
//     elif(variable_type == RECT_ARRAY){
//         res = "rectangularArray";
//     }
//     else{
//         res = "jaggedArray";
//     }

//     return res;
// }

char* get_str_primitive_type(enum primitive_type){
    char* res;
    if(primitive_type == BOOLEAN){
        res = "Boolean";
    }
    elif(primitive_type == INTEGER){
        res = "integer";
    }
    else{
        res = "real";
    }

    return res;
}

// get the desired String Representation of TypeExpression
char* get_string_representation(type_expression tp){

    union_to_be_named union_ds = calloc(1,sizeof(union_to_be_named)); 
    union_ds = tp->union_to_be_named->root;
    char* result;

    if(tp->variable_type == PRIMITIVE_TYPE)
    {
        result = strcat("type = ", get_str_primitive_type(tp->primitive_type));
        return result;
    }
    else if(tp->variable_type == RECT_ARRAY){
        /*
            <type=rectangularArray, dimensions=2, range_R1= (2, 5), range_R2 = (3, 6), basicElementType = integer>
        */
        result = strcat(strcat("type = rectangularArray, ", "dimensions = "), atoi(union_ds->num_nodes));
        result = strcat(result, ", ");

        for(int i=1;i<=num_nodes;i++){
            result = strcat(result, strcat("range_R", atoi(i)));
            result = strcat(result, "= (");
            rect_array_range* r = (rect_array_range*)ll_get(union_ds, i);
            result = strcat(result,strcat(atoi(r->lower_bound), atoi(r->upper_bound)));
            result = strcat(result, "), ");
        }
        result = strcat(result, "basicElementType = integer");
        return result;
    }
    else{
        result="type = jaggedArray"
    }
}

// set is_declared to true on encountering decl_stmt
void set_declare_flag(type_expression t){
    t->is_declared = true;
}

/*
    construct_type_expression:=
        tp = allocate memory for tp
        set_declare_flag(tp)
        variable_type 
            primitive: assign enum value based on lexeme value
            rect_array: ll_append(rect_array_node[Lb,Up])
*/