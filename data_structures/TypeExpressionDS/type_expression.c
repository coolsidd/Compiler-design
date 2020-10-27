#include "type_expression.h"
#define MAX_BUFFER_SIZE 200

char *get_str_primitive_type(t_primitive_type primitive_data)
{
    switch(primitive_data){
        case(t_BOOLEAN):
            return "Boolean";
            break;
        case(t_INTEGER):
            return "integer";
            break;
        case(t_REAL):
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
            snprintf(result, MAX_BUFFER_SIZE, "<type = %s>", get_str_primitive_type(union_ds.primitive_data));
            return result;
            break;
        }

        case(RECT_ARRAY):
        {
            /*
                <type=rectangularArray, dimensions=2, range_R1= (2, 5), range_R2 = (3, 6), basicElementType = integer>
            */
            linked_list* ll = union_ds.rect_array_data.array_ranges;
            snprintf(result, MAX_BUFFER_SIZE, "<type = rectangularArray, dimensions = %d, ",
                              union_ds.rect_array_data.dimensions);
            char temp[30];
            char* temp1 = temp;
            for(int i=1;i<=union_ds.rect_array_data.dimensions;i++){
                rect_array_range* r = (rect_array_range*)ll_get(ll, i-1);
                snprintf(temp1, 100, "range_R%d= (%d,%d), ", i,r->lower_bound, r->upper_bound);
                result = strcat(result, temp1);
            }
            result = strcat(result,"basicElementType = integer>");
            return result;
            break;
        }
        
        case(JAGGED_ARRAY):
        {
            //3d : <type = jaggedArray, dimensions = 3, range_R1 = (4, 7), range_R2 = (3 [5, 3, 5], 2 [3, 5], 3 [5, 4, 3], 4 [2, 5, 4, 4]), basicElementType = integer> 
            //2d : <type = jaggedArray, dimensions = 2, range_R1 = (3, 8), range_R2 = (3, 6, 2, 4, 1, 5), basicElementType = integer>
            int dimen = tp->union_to_be_named.jagged_array_data.dimensions;
            snprintf(result, MAX_BUFFER_SIZE, "<type = jaggedArray>, dimensions = %d,",
                                                dimen);
            if(dimen == 2){
                jagged_2d jagg_2d = tp->union_to_be_named.jagged_array_data.array_type.j2d;
                int l_bound = jagg_2d.lower_bound;
                int u_bound = jagg_2d.upper_bound;
                snprintf(result, MAX_BUFFER_SIZE, "%s range_R1 = (%d, %d), range_R2 = (", result, l_bound, u_bound);
                r2_dimension r2d = jagg_2d.row_sizes;
                int i, *data;
                for(i = 0; i < (u_bound-l_bound); i++){
                    data = (int *)ll_get(r2d.sizes, i);
                    snprintf(result, MAX_BUFFER_SIZE, "%s%d, ", result, *data);
                }
                data = (int *)ll_get(r2d.sizes, i);
                snprintf(result, MAX_BUFFER_SIZE, "%s%d)", result, *data);
            }

            else if(dimen == 3){
                jagged_3d jagg_3d = tp->union_to_be_named.jagged_array_data.array_type.j3d;
                int l_bound = jagg_3d.lower_bound;
                int u_bound = jagg_3d.upper_bound;
                snprintf(result, MAX_BUFFER_SIZE, "%s range_R1 = (%d, %d), range_R2 = (", result, l_bound, u_bound);
                linked_list* ll = jagg_3d.row_sizes;
                for(int i = 0; i < ll->num_nodes; i++){
                    r2_dimension* r = (r2_dimension*)ll_get(ll, i);
                    int s = r->sizes->num_nodes;
                    snprintf(result, MAX_BUFFER_SIZE, "%s%d [", result, s);
                    for(int j = 0; j < s; j++){
                        int* data = (int *)ll_get(r->sizes, j);
                        if (j < s-1)
                        {
                            snprintf(result, MAX_BUFFER_SIZE, "%s%d, ", result, *data);
                            continue;
                        }
                            snprintf(result, MAX_BUFFER_SIZE, "%s%d", result, *data);
                    }
                    if(i < ll->num_nodes-1){
                        snprintf(result, MAX_BUFFER_SIZE, "%s], ", result);
                        continue;
                    }

                    snprintf(result, MAX_BUFFER_SIZE, "%s]),", result);
                }
            }
            snprintf(result, MAX_BUFFER_SIZE, "%sbasicElementType = integer", result); 
            return result;
            break;
        }
    }
}

// set is_declared to true on encountering decl_stmt
void set_declare_flag(type_expression* tp){
    tp->is_declared = true;
}

type_expression* construct_type_expression(VariableType variable_type, union_to_be_named union_ds){

    type_expression* tp = (type_expression*)calloc(1, sizeof(type_expression));
    set_declare_flag(tp);
    tp->variable_type = variable_type;
    tp->union_to_be_named = union_ds;
    return tp;
}

union_to_be_named* populate_union(VariableType variable_type, Parse_tree_node* p){
        union_to_be_named* u = (union_to_be_named*)calloc(1,sizeof(union_to_be_named));
        switch(variable_type){
            case(PRIMITIVE_TYPE):
            {
                u->primitive_data = *get_primitive_type(p);   
                break;
            }
            case(RECT_ARRAY):
            {
                u->rect_array_data = *create_rect_array_type(p);
                break;
            }
            case(JAGGED_ARRAY):
            {
                u->jagged_array_data = *create_jagged_array_type(p);
                break;
            }
        }
        return u;
}