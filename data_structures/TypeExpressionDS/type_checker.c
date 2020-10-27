/*
    Given parse_tree_node* p;
    check p->tok->lexeme

    stmts:

        INDEXES SHOULD BE INTEGER and within bounds

        decl_stmt:
            call add_entry_to_type_exp_table
                non_jagged:
                    2nd child: list_of_identifiers:
                        f(){
                            check 1st child:
                                if ID:
                                    call add_entry_to_type_exp_table
                                if last_child is id_list:
                                    recurse on the last child(call f())
                        }

                jagged:
                    to check for typedef errors
                    rows = count on number of rows
                        for each row:
                           2d: 
                            checker(jagged2init, index)
                            jagged_2init: 3rd child(var: index/RowNumber) should be in bounds
                            7th child: size
                            no of j2list instances should be equal to size
                            j2list:
                                value_list:
                                    last_child shouldnot be value_list
                            number of jagged_2init instances should be equal to rows


*/

/*
    Conventions:
        jagged2_list: stores LB-UBs
        (UB-LB+1) * jagged2_init: initialisation of a row
        j2_list: columns of jagged2_init(numbers separated by semicolons)

checker(jagged2init, index)
    3rd child should be equal to index
    if not:
        throw error

*/

#include "type_exp_table.h"
#include "print.h"
#include "type_expression.h"
#include "assign_helpers.h"
#include <math.h>

void traverse_and_populate(type_exp_table* txp_table, Parse_tree_node *p)
{
    printf("At node %s\n", toStringSymbol(p->tok->lexeme));
    p = p->child;
    p = getNodeFromIndex(p, 4);
    Parse_tree_node *assign_stmts_node = p->last_child;
    p = p->child;
    Parse_tree_node* decl_stmts_node = p;
    do{
        type_check_decl_stmt(txp_table, decl_stmts_node->child);
        print_type_exp_table(txp_table);
        decl_stmts_node = decl_stmts_node->last_child;
    }while(decl_stmts_node->tok->lexeme.s == decl_stmts);

    do{
        type_check_assign_stmt(txp_table, assign_stmts_node->child);
        assign_stmts_node = assign_stmts_node->last_child;
    }while(assign_stmts_node->tok->lexeme.s == assign_stmts);
}

void type_check_decl_stmt(type_exp_table* txp_table,Parse_tree_node* p) {
    printf("At node %s\n", toStringSymbol(p->tok->lexeme));
    char* variable_name;
    VariableType variable_type;
    DeclarationType decl_type;
    union_to_be_named u;
    // p -> <decl_stmt>
    p = p->child; // p -> <decl_non_jagged> | <decl_jagged>
    printf("creating ll %s\n", toStringSymbol(p->tok->lexeme));
    // storing list of identifiers p->child -> DECLARE <list_of_identifier> ...
    linked_list* variables = create_linked_list();
    Parse_tree_node* list_of_id_node = getNodeFromIndex(p->child,1);
    list_of_id_node = list_of_id_node->child;
    if(list_of_id_node->tok->lexeme.s == LIST){

        list_of_id_node = getNodeFromIndex(list_of_id_node, 3);
        do{
        list_of_id_node = list_of_id_node->child;
        ll_append(variables, list_of_id_node->tok->token_name);
        list_of_id_node = list_of_id_node->next;
        }while(list_of_id_node->tok->lexeme.s==id_list);

        ll_append(variables, list_of_id_node->tok->token_name);
    }
    else{
        ll_append(variables, list_of_id_node->tok->token_name);
    }
    printf("got ll %s\n", toStringSymbol(p->tok->lexeme));
    p = p->child; // p -> DECLARE <list_of_identifier> COLON (<decOLlation_type> | <jagged_array>)
    p = getNodeFromIndex(p, 3);
    printf("At node %s\n", toStringSymbol(p->tok->lexeme));
    if(p->tok->lexeme.s==declaration_type){
        p = p->child;
    }
    
    switch (p->tok->lexeme.s)
    {
        case primitive_type:
        {
            printf("primitive %s\n", toStringSymbol(p->tok->lexeme));
            variable_type = PRIMITIVE_TYPE;
            decl_type = NOT_APPLICABLE;
            for(int i=0;i<variables->num_nodes;i++)
            {
                variable_name = (char*)ll_get(variables, i);
                u = *populate_union(variable_type, p);
                type_expression *tp = construct_type_expression(variable_type, u);
                add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);
            }
            break;
        }
        case rect_array:
        {
            // proceed only if type checks success
            decl_type = STATIC;
            Parse_tree_node* pt = (Parse_tree_node*)calloc(1, sizeof(Parse_tree_node));
            pt = p;
            bool flag = rect_decl_checks(txp_table, pt, &decl_type);
            if(flag){
                variable_type = RECT_ARRAY;
                for (int i = 0; i < variables->num_nodes; i++)
                {
                    variable_name = (char *)ll_get(variables, i);
                    u = *populate_union(variable_type, p);
                    type_expression *tp = construct_type_expression(variable_type, u);
                    add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);
                }
                break;
            }
        }
        
        case jagged_array:
        {
            printf("jagged %s\n", toStringSymbol(p->tok->lexeme));
            // proceed only if type checks success
            Parse_tree_node *pt = (Parse_tree_node *)calloc(1, sizeof(Parse_tree_node));
            pt = p;
            bool flag = jagged_decl_checks(pt);
            if (flag)
            {
                variable_type = JAGGED_ARRAY;
                decl_type = NOT_APPLICABLE;
                for (int i = 0; i < variables->num_nodes; i++)
                {
                    variable_name = (char *)ll_get(variables, i);
                    u = *populate_union(variable_type, p);
                    type_expression *tp = construct_type_expression(variable_type, u);
                    add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);
                }
                break;
            }
        }
    }
}

void type_check_assign_stmt(type_exp_table* txp_table, Parse_tree_node* p){
    printf("At node %s\n", toStringSymbol(p->tok->lexeme));
    type_expression* lhs = get_type_of_var_lhs(txp_table, p->child);
    type_expression* rhs = get_type_exp_of_expr(txp_table, p->last_child);
    bool flag = are_types_equal(lhs, rhs, txp_table, p);
}

bool are_types_equal(type_expression* t1, type_expression* t2, type_exp_table* txp_table,
            Parse_tree_node* p){
    char* s1 = str_type(t1);
    char* s2 = str_type(t2);
    char* operator = "EQUALS";
    char* lexeme1 = "var_lhs";
    char* lexeme2 = "expr";
    bool flag = assert_debug(t1 && t2 && t1->is_declared && t2->is_declared, 
        "Variable used before Declaration",p, s1, s2, operator, lexeme1, lexeme2);
    flag &= assert_debug(t1->variable_type == t2->variable_type,
                            "Variable used before Declaration", p,
                            s1, s2, operator, lexeme1, lexeme2);
    if(!flag) 
        return false;
    switch(t1->variable_type){
        case(PRIMITIVE_TYPE):{
            flag&=assert_debug(t1->union_to_be_named.primitive_data == t2->union_to_be_named.primitive_data,
            "Different Primitive types",p, s1, s2, operator, lexeme1, lexeme2);
            return flag;
            break;
        }
        case(RECT_ARRAY):{
            flag &= check_rect_dimensions(t1->union_to_be_named.rect_array_data,
                        t2->union_to_be_named.rect_array_data, p, s1, s2, operator,
                        lexeme1, lexeme2);
            return flag;
            break;
        }
        case(JAGGED_ARRAY):{
            flag &= check_jagged_dimensions(t1->union_to_be_named.jagged_array_data,
                        t2->union_to_be_named.jagged_array_data, p, s1, s2, operator,
                        lexeme1, lexeme2);
            return flag;
            break;
        }
    }
    
}

bool rect_decl_checks(type_exp_table* txp_table, Parse_tree_node* p, DeclarationType* decl_type){
    int i = 0;
    bool flag = true;
    p = p->child;
    Parse_tree_node* range_list_node = getNodeFromIndex(p,1);
    Parse_tree_node* primitive_type_node = getNodeFromIndex(p, 3);
    flag &= assert_debug(primitive_type_node->child->tok->lexeme.s == INTEGER, "RectArrayType has to be int", p, "***", "***", "***", "***", "***");
    do{
        Parse_tree_node* lower_bound = getNodeFromIndex(range_list_node->child, 1);
        Parse_tree_node* upper_bound = getNodeFromIndex(range_list_node->child, 3);
        if(lower_bound->child->tok->lexeme.s != CONST || upper_bound->child->tok->lexeme.s != CONST){
            *decl_type = DYNAMIC;
        }
        type_expression* lower_type = get_type_of_var(txp_table, lower_bound);
        type_expression* upper_type = get_type_of_var(txp_table, upper_bound);
        flag &= assert_debug(lower_type->variable_type==PRIMITIVE_TYPE, "Rect Array decl indices cannot be arrays", p, "***", "***", "***", "***", "***");
        flag &= assert_debug(upper_type->variable_type==PRIMITIVE_TYPE, "Rect Array decl indices cannot be arrays", p, "***", "***", "***", "***", "***");
        range_list_node = range_list_node->last_child;
    }while(range_list_node->tok->lexeme.s==range_list);
    return flag;
}

bool jagged_decl_checks(Parse_tree_node* p){
    bool flag = true;
    /*
        - Index out of bounds for jaggedXinit. X=2,3
        - No of instances of jaggedXinit should be = UB-LB+1
        - For each row, size should be equal to be number of semicolon 
            separated values.
        - For 2d, value_list cannot have last child as value_list
    */
    p = p->child;
    Parse_tree_node* dimen = getNodeFromIndex(p, 2);
    Parse_tree_node* bounds = dimen->child->child;
    Parse_tree_node* lower_bound = getNodeFromIndex(bounds, 1);
    Parse_tree_node* upper_bound = getNodeFromIndex(bounds, 3);
    flag = assert_debug(lower_bound->tok->lexeme.s == INTEGER ||
                        lower_bound->tok->lexeme.s == CONST, 
                        "JaggedArray Lower Bound has to be Integer", p, "***", "***", "***", "***", "***");
    flag = assert_debug(upper_bound->tok->lexeme.s == INTEGER, "JaggedArray Upper Bound has to be Integer",p, "***", "***", "***", "***", "***");
    int n_rows = atoi(upper_bound->tok->token_name)-atoi(lower_bound->tok->token_name);
    if(dimen->tok->lexeme.s == jagged2list){

    }
    else{

    }

    return flag;
}


type_expression* get_type_of_var(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression* txp;

    if(p->child->tok->lexeme.s == CONST){
        return get_integer_type();
    }
    else if(p->last_child->tok->lexeme.s == SQBC){

        linked_list* bounds = get_type_of_index_list(txp_table, getNodeFromIndex(p->child,2));
        if(bounds)
        {
            bool flag = do_bound_checking(txp_table, p, bounds);
        }
        return get_integer_type();
    }

    else if(p->last_child->tok->lexeme.s == ID){
        txp = get_type_expression(txp_table, p->last_child->tok->token_name);
        bool flag = assert_debug(txp!=NULL, "Variable used before declaration",p, "***", "***", "***", "***", "***");
        return txp;
    }

}

linked_list* get_type_of_index_list(type_exp_table* txp_table, Parse_tree_node* p){
    
    linked_list* ll = create_linked_list();

    type_expression* txp = get_type_of_var(txp_table ,p->child);

    if(txp->union_to_be_named.primitive_data == t_INTEGER){
        if(p->child->tok->lexeme.s == CONST){
            void* temp = (void*)calloc(1, sizeof(int));
            *(int*)temp = atoi(p->child->tok->token_name);
            ll_append(ll, temp);
        }
        else if(p->last_child->tok->lexeme.s == SQBC){
            linked_list* temp = get_type_of_index_list(txp_table, getNodeFromIndex(p->child, 2));
            if(!temp){
                return NULL;
            }
            else{
                ll->tail->next = temp->head;
                ll->num_nodes += temp->num_nodes;
                return ll;
            }
        }
        else if(p->child->tok->lexeme.s == ID){
            return NULL;
        }
    }
    else{
        bool flag = assert_debug(false, "Type of Index should be Integer or Constant.",p, "***", "***", "***", "***", "***");
        return NULL;
    }
}

bool do_bound_checking(type_exp_table* txp_table, Parse_tree_node* p, linked_list* ll){
    type_expression* txp = get_type_expression(txp_table, p->tok->token_name);
    switch(txp->variable_type){
        case(PRIMITIVE_TYPE):
        {
            return false;
            break;
        }
        case(RECT_ARRAY):
        {
            linked_list* rect_bounds = txp->union_to_be_named.rect_array_data.array_ranges;
            int n_nodes = ll->num_nodes;
            bool flag = true;
            assert_debug(n_nodes==rect_bounds->num_nodes, "Dimension Number Mismatch", p, "***", "***", "***", "***", "***");
            ll_node *temp1 = ll->head;
            for(ll_node *temp = rect_bounds->head; temp && temp1; temp = temp->next)
            {
                int* b = (int*)temp1->data;
                rect_array_range* r = (rect_array_range*)temp->data;
                flag &= assert_debug(*b >= r->lower_bound && *b <= r->upper_bound, "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");
                temp1 = temp1->next;
            }
            return flag;
            break;
        }
        case(JAGGED_ARRAY):
        {
            bool flag = true;
            switch(txp->union_to_be_named.jagged_array_data.dimensions){
                case 2:{
                    jagged_2d jagged_bounds = txp->union_to_be_named.jagged_array_data.array_type.j2d;
                    flag &= assert_debug(ll->num_nodes==2, "Dimension Number Mismatch",p, "***", "***", "***", "***", "***");
                    int first = *((int*)ll->head->data);
                    flag &= assert_debug(jagged_bounds.lower_bound<= first && jagged_bounds.upper_bound>=first
                                 , "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");
                    int second = *((int*)ll->head->next->data);
                    flag &= assert_debug(second<=*((int*)ll_get(jagged_bounds.row_sizes.sizes, first - jagged_bounds.lower_bound)), "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");
                    return flag;
                    break;
                }
                case 3:{
                    // TODO Crosscheck
                    jagged_3d jagged_bounds = txp->union_to_be_named.jagged_array_data.array_type.j3d;
                    flag &= assert_debug(ll->num_nodes==3, "Dimension Number Mismatch",p, "***", "***", "***", "***", "***");
                    if(flag){
                        int first = *((int *)ll->head->data);
                        flag &= assert_debug(jagged_bounds.lower_bound <= first && jagged_bounds.upper_bound>= first, "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");
                        int second = *((int *)ll->head->next->data);
                        int third = *((int *)ll->head->next->next->data);
                        linked_list * ll_temp = jagged_bounds.row_sizes;
                        flag &= assert_debug(second <= ((linked_list*)ll_get(ll_temp,first-jagged_bounds.lower_bound))->num_nodes, "IndexOutOfBounds",p, "***", "***", "***", "***", "***");
                        linked_list * third_dim = ((linked_list*)ll_get(ll_temp,first-jagged_bounds.lower_bound));
                        flag &= assert_debug(*((int*)ll_get(third_dim,second))<=third, "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");
                        return flag;
                    }else{
                        return flag;
                    }
                    break;
                }
            }
        }
    }
}
