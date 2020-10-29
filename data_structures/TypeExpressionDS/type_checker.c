/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#include "type_exp_table.h"
#include "type_checker.h"
#include "print.h"
#include "type_expression.h"
#include "assign_helpers.h"
#include <math.h>

void traverse_and_populate(type_exp_table* txp_table, Parse_tree_node *p)
{
    p = p->child;
    p = getNodeFromIndex(p, 4);
    Parse_tree_node *assign_stmts_node = p->last_child;
    p = p->child;
    Parse_tree_node* decl_stmts_node = p;
    printErrorsHeader();
    do{
        type_expression * temp =type_check_decl_stmt(txp_table, decl_stmts_node->child);
        decl_stmts_node->child->txp = temp;
        decl_stmts_node = decl_stmts_node->last_child;
    }while(decl_stmts_node->tok->lexeme.s == decl_stmts);

    do{
        type_expression * temp = type_check_assign_stmt(txp_table, assign_stmts_node->child);
        assign_stmts_node->child->txp = temp;
        assign_stmts_node = assign_stmts_node->last_child;
    }while(assign_stmts_node->tok->lexeme.s == assign_stmts);
}

type_expression* type_check_decl_stmt(type_exp_table* txp_table,Parse_tree_node* p) {
    char* variable_name;
    VariableType variable_type;
    DeclarationType decl_type;
    union_to_be_named u;
    // p -> <decl_stmt>
    p = p->child; // p -> <decl_non_jagged> | <decl_jagged>
    // printf("creating ll %s\n", toStringSymbol(p->tok->lexeme));
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
    p = p->child; // p -> DECLARE <list_of_identifier> COLON (<decOLlation_type> | <jagged_array>)
    p = getNodeFromIndex(p, 3);
    if(p->tok->lexeme.s==declaration_type){
        p = p->child;
    }

    type_expression* tp;

    switch (p->tok->lexeme.s)
    {
        case primitive_type:
        {
            variable_type = PRIMITIVE_TYPE;
            decl_type = NOT_APPLICABLE;
            for(int i=0;i<variables->num_nodes;i++)
            {
                variable_name = (char*)ll_get(variables, i);
                u = *populate_union(variable_type, p);
                tp = construct_type_expression(variable_type, u);
                add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);
            }
            return tp;
            break;
        }
        case rect_array:
        {
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
                    tp = construct_type_expression(variable_type, u);
                    add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);
                }
            }
            return tp;
            break;
        }

        case jagged_array:
        {
            // proceed only if type checks success
            Parse_tree_node *pt = (Parse_tree_node *)calloc(1, sizeof(Parse_tree_node));
            pt = p;
            decl_type = NOT_APPLICABLE;
            bool flag = jagged_decl_checks(txp_table,  pt);
            // printf("FLAG: %d", flag);
            if (flag)
            {
                variable_type = JAGGED_ARRAY;
                for (int i = 0; i < variables->num_nodes; i++)
                {
                    variable_name = (char *)ll_get(variables, i);
                    u = *populate_union(variable_type, p);
                    tp = construct_type_expression(variable_type, u);
                    add_entry_to_table(txp_table, variable_name, variable_type, decl_type, tp);
                }
            }
            return tp;
            break;
        }
    }
}

type_expression* type_check_assign_stmt(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression* lhs = get_type_of_var_lhs(txp_table, p->child);
    type_expression* rhs = get_type_exp_of_expr(txp_table, p->last_child);
    if(rhs)
        are_types_equal(lhs, rhs, txp_table, p);
    return lhs;
}

bool are_types_equal(type_expression* t1, type_expression* t2, type_exp_table* txp_table,
            Parse_tree_node* p){
    char* s1 = str_type(t1);
    char* s2 = str_type(t2);
    char* operator = "EQUALS";
    char* lexeme1 = "var_lhs";
    char* lexeme2 = "expr";
    bool flag = assert_debug(t1 && t2 && t1->is_declared && t2->is_declared,
        "Var Declaration",p, s1, s2, operator, lexeme1, lexeme2);
    flag &= assert_debug(t1->variable_type == t2->variable_type,
                            "Var used before Declaration", p,
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
    flag &= assert_debug(primitive_type_node->child->tok->lexeme.s == INTEGER, "RectArray of Non-Int Type", p, "***", "***", "***", "***", "***");
    if(!flag) return flag;
    do{
        Parse_tree_node* lower_bound = getNodeFromIndex(range_list_node->child, 1);
        Parse_tree_node* upper_bound = getNodeFromIndex(range_list_node->child, 3);
        if(lower_bound->child->tok->lexeme.s != CONST || upper_bound->child->tok->lexeme.s != CONST){
            type_expression * type_lower = get_type_of_var(txp_table, lower_bound);
            type_expression * type_upper = get_type_of_var(txp_table, upper_bound);
            flag &= assert_debug(type_lower && type_upper,"RectArray undeclared bounds", range_list_node, "***", "***", "***", "***", "***");
            if(flag){
                assert_debug(type_lower->variable_type==PRIMITIVE_TYPE && type_lower->union_to_be_named.primitive_data == t_INTEGER && type_upper->variable_type==PRIMITIVE_TYPE && type_upper->union_to_be_named.primitive_data == t_INTEGER,"RectArray with non int bounds", range_list_node, str_type(type_lower), str_type(type_upper), "***", "***", "***");
                *decl_type = DYNAMIC;
            }else{
                return flag;
            }

        }
        type_expression* lower_type = get_type_of_var(txp_table, lower_bound);
        type_expression* upper_type = get_type_of_var(txp_table, upper_bound);
        flag &= assert_debug(lower_type->variable_type == PRIMITIVE_TYPE, "RectArray index of array type", p, "***", "***", "***", "***", "***");
        flag &= assert_debug(upper_type->variable_type == PRIMITIVE_TYPE, "RectArray index of array type", p, "***", "***", "***", "***", "***");
        range_list_node = range_list_node->last_child;
    }while(range_list_node->tok->lexeme.s==range_list);
    return flag;
}

bool jagged_decl_checks(type_exp_table* txp_table, Parse_tree_node* p){
    bool flag = true;
    Parse_tree_node* temp = p->child;
    Parse_tree_node* primitive_type_node = getNodeFromIndex(temp, 4);
    flag &= assert_debug(primitive_type_node->child->tok->lexeme.s == INTEGER, "JaggedArrayType has to be int", p, "***", "***", "***", "***", "***");
    Parse_tree_node *dimen = getNodeFromIndex(temp, 2);
    Parse_tree_node* bounds = dimen->child->child;
    Parse_tree_node* lower_bound = getNodeFromIndex(bounds, 1);
    Parse_tree_node* upper_bound = getNodeFromIndex(bounds, 3);
    type_expression* lower_type = get_type_of_var(txp_table, lower_bound);
    type_expression* upper_type = get_type_of_var(txp_table, upper_bound);

    if (lower_type && upper_type) {
        lower_bound = lower_bound->last_child;
        upper_bound = upper_bound->last_child;
        flag &= assert_debug(lower_bound->tok->lexeme.s == CONST,
                            "JgdArr Lower Bound variable", p, "***",
                            "***", "***", "***", "***");
        flag &= assert_debug(upper_bound->tok->lexeme.s == CONST,
                            "JgdArr Upper Bound variable", p, "***",
                            "***", "***", "***", "***");
        int upper_int = atoi(upper_bound->tok->token_name);
        int lower_int = atoi(lower_bound->tok->token_name);
        int n_rows = upper_int - lower_int + 1;
        flag &= assert_debug(n_rows > 0, "JaggedArray bounds <=0", p, "***", "***",
                            "***", "***", "***");
        if(!flag)
            return false;
        // here p is jagged array
        BaseSymbol b = p->last_child->tok->lexeme.s;
        if(b!=jagged2init && b!=jagged3init)
            return false;
        p = p->last_child;
        for(int i = lower_int; i<=upper_int; i++){
            // TODO Call function
            // printf("\n ****** DRIVER: Got %d", i);
            flag &= jagged_init_checker(txp_table, p, i);
            if (i < upper_int )
            { flag &= assert_debug(p->last_child->tok->lexeme.s == b, "Less initalisations than rowNo", p, "***", "***", "***", "***", "***");
                if (!flag)
                    return false;
                p = p->last_child;
            }
            // printf("\n ******* DRIVER:  %d: %d", i, flag);
        }
        flag &= assert_debug(p->last_child->tok->lexeme.s != b, "More initials than rowNo", p, "***", "***", "***", "***", "***");
        return flag;
    }
    else{
        return false;
    }

}

bool jagged_init_checker(type_exp_table * txp_table, Parse_tree_node* p, int idx){
    char *lex = toStringSymbol(p->tok->lexeme);
    Parse_tree_node *r1_idx = getNodeFromIndex(p->child, 2);
    bool flag = assert_debug(r1_idx->child->tok->lexeme.s == CONST, "R1[variable] not allowed", p, "***", "***", "***", lex, "***");
    if(!flag) return false;
    
    int r1_idx_int = atoi(r1_idx->child->tok->token_name);
    flag &= assert_debug(r1_idx_int == idx, "R1[idx] not ascending", p, "***", "***", "***", lex, "***");
    Parse_tree_node* row_size_node = getNodeFromIndex(r1_idx, 4);
    type_expression *rsize_type = get_type_of_var(txp_table, row_size_node);
    if(!rsize_type) return false;

    flag &= assert_debug(row_size_node->child->tok->lexeme.s == CONST,
                            "JgdArr Row Size variable", p, "***",
                            "***", "***", "***", "***");
    int row_size = atoi(row_size_node->child->tok->token_name);
    char *errStr = (char *)malloc(sizeof("JaggedArray row size <=0")+5);
    sprintf(errStr, "JaggedArray row %d size <=0", idx);
    flag &= assert_debug(row_size > 0, errStr, p, "***", "***",
                                "***", "***", "***");
    if(!flag) return false;
    flag &= jagged_list_checker(txp_table, getNodeFromIndex(row_size_node,4), row_size);
    // printf(" INIT_C %d %d", idx, flag);
    return flag;
}

bool jagged_list_checker(type_exp_table * txp_table, Parse_tree_node* p, int row_size){
    // 2 semicolons together
    if(p->child->tok->lexeme.s == SEMICOLON) 
        return false;
    if(p->tok->lexeme.s == j2list){
        Parse_tree_node* val_list_node;
        type_expression* txp;
        bool flag = true;
        for(int i=0;i<row_size;i++){
            val_list_node = p->child; // value_list
            txp = get_type_of_var(txp_table, val_list_node->child);
            if(txp){
                flag &= assert_debug(txp->variable_type == PRIMITIVE_TYPE, "Values in row not integer", p, "***", "***", "***", "***", "***");
                if(!flag)
                    return false;
                flag &= assert_debug(txp->union_to_be_named.primitive_data == t_INTEGER, "Values in row not integer", p, "***", "***", "***", "***", "***");
                if (!flag)
                    return false;
            }
            else{
                // undeclared variable as entry in row
                return false;
            }
            if(val_list_node->last_child->tok->lexeme.s == value_list){
                return false;
            }
            if(i<row_size-1){
                flag &= assert_debug(p->last_child->tok->lexeme.s == j2list, "Fewer values than row size.", p, "***", "***", "***", "***", "***");
                if(!flag)
                    return false;
            }
            p = p->last_child;
        }
        flag&=assert_debug(p->tok->lexeme.s != j2list, "More values than row size", p, "***", "***", "***", "***", "***");
        // printf("\n LIST_CHECKER: %d %d", row_size, flag);
        return flag;
    }
    else if(p->tok->lexeme.s == j3list){
        Parse_tree_node *val_list_node;
        type_expression *txp;
        bool flag = true;
        for (int i = 0; i < row_size; i++)
        {
            val_list_node = p->child; // value_list
            do{
                txp = get_type_of_var(txp_table, val_list_node->child);
                if (txp)
                {
                    flag &= assert_debug(txp->variable_type == PRIMITIVE_TYPE, "Values in row not integer", p, "***", "***", "***", "***", "***");
                    if (!flag)
                        return false;
                    flag &= assert_debug(txp->union_to_be_named.primitive_data == t_INTEGER, "Values in row not integer", p, "***", "***", "***", "***", "***");
                    if (!flag)
                        return false;
                }
                else
                {
                    // undeclared variable as entry in row
                    return false;
                }
                if (i < row_size - 1)
                {
                    flag &= assert_debug(p->last_child->tok->lexeme.s == j3list, "Fewer values than row size.", p, "***", "***", "***", "***", "***");
                    if (!flag)
                        return false;
                }
                p = p->last_child;
            }while(p->tok->lexeme.s == value_list);
        }
        flag &= assert_debug(p->tok->lexeme.s != j3list, "More values than row size", p, "***", "***", "***", "***", "***");
        return flag;
    }
}

type_expression* get_type_of_var(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression* txp = (type_expression*) calloc(1, sizeof(type_expression));


    if(p->last_child->tok->lexeme.s == CONST){
        return get_integer_type();
    }
    else if(p->last_child->tok->lexeme.s == SQBC){
        type_expression *txp = get_type_of_var(txp_table, getNodeFromIndex(p->child,2)->child);
        if (!assert_debug(txp!=NULL, "Var used before Declaration", p, "***", "***", "***", "***", "***"))
            return NULL;

        linked_list* bounds = get_type_of_index_list(txp_table, getNodeFromIndex(p->child,2));
        bool flag = do_bound_checking(txp_table, p->child, bounds);
        return get_integer_type();
    }

    else if(p->last_child->tok->lexeme.s == ID){
        txp = get_type_expression(txp_table, p->last_child->tok->token_name);
        bool flag = assert_debug(txp!=NULL, "Var used before Declaration",p, "***", "***", "***", "***", "***");
        return txp;
    }
    return NULL;
}

linked_list* get_type_of_index_list(type_exp_table* txp_table, Parse_tree_node* p){
    linked_list* ll = create_linked_list();
    p = p->child;
    type_expression* txp = get_type_of_var(txp_table ,p);
    if(txp){
        bool flag = assert_debug(txp->variable_type==PRIMITIVE_TYPE && txp->union_to_be_named.primitive_data==t_INTEGER, "Type of Index should be Integer or Constant.",p, "***", "***", "***", "***", "***");
        if(p->child->tok->lexeme.s == CONST){
            int* temp = (int*)calloc(1, sizeof(int));
            *temp = atoi(p->child->tok->token_name);
            ll_append(ll, temp);
        }
        else if(p->last_child->tok->lexeme.s == SQBC){
            ll_append(ll, NULL);
        }
        else if(p->child->tok->lexeme.s == ID){
            ll_append(ll, NULL);
        }
    }
    else{
        bool flag = assert_debug(false, "Invalid Indexing",p, "***", "***", "***", "***", "***");
        return NULL;
    }
    if(p->next && p->next->tok->lexeme.s == index_list){
        linked_list* temp = get_type_of_index_list(txp_table, p->next);
        ll->tail->next = temp->head;
        ll->tail = temp->tail;
        ll->num_nodes+= temp->num_nodes;
    }

    return ll;
}

bool do_bound_checking(type_exp_table* txp_table, Parse_tree_node* p, linked_list* ll){
    type_expression* txp = get_type_expression(txp_table, p->tok->token_name);
    if(!txp) return false;
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
            assert_debug(n_nodes==rect_bounds->num_nodes, "Dimensions Mismatch", p, "***", "***", "***", "***", "***");
            char *err_str = (char *)malloc(strlen("Dimension Mismatch %d vs %d")+10);
            sprintf(err_str,"Dimension Mismatch %d vs %d", n_nodes, rect_bounds->num_nodes);
            assert_debug(n_nodes==rect_bounds->num_nodes, err_str , p, "***", "***", "***", "***", "***");
            ll_node *temp1 = ll->head;
            for(ll_node *temp = rect_bounds->head; temp && temp1; temp = temp->next)
            {
                if(!temp1->data){
                    continue;
                }
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
                    flag &= assert_debug(ll->num_nodes==2, "Dimensions Mismatch",p, "***", "***", "***", "***", "***");
                    if(!ll->head->data || !flag){
                        return flag;
                    }
                    int first = *((int*)ll->head->data);
                    flag &= assert_debug(jagged_bounds.lower_bound<= first && jagged_bounds.upper_bound>=first
                                         , "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");

                    if(!ll->head->next->data || !flag){
                        return flag;
                    }
                    int second = *((int*)ll->head->next->data);
                    flag &= assert_debug(second<=*((int*)ll_get(jagged_bounds.row_sizes.sizes, first - jagged_bounds.lower_bound)), "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");
                    return flag;
                    break;
                }
                case 3:{
                    jagged_3d jagged_bounds = txp->union_to_be_named.jagged_array_data.array_type.j3d;
                    flag &= assert_debug(ll->num_nodes==3, "Dimensions Mismatch",p, "***", "***", "***", "***", "***");
                    if(flag){
                        if(!ll->head->data || !flag){
                            return flag;
                        }
                        int first = *((int *)ll->head->data);
                        flag &= assert_debug(jagged_bounds.lower_bound <= first && jagged_bounds.upper_bound>= first, "IndexOutOfBoundsError",p, "***", "***", "***", "***", "***");

                        if(!ll->head->next->data || !flag){
                            return flag;
                        }
                        int second = *((int *)ll->head->next->data);
                        linked_list * ll_temp = jagged_bounds.row_sizes;
                        flag &= assert_debug(second <= ((linked_list*)ll_get(ll_temp,first-jagged_bounds.lower_bound))->num_nodes, "IndexOutOfBounds",p, "***", "***", "***", "***", "***");
                        if(!ll->head->next->next->data || !flag){
                            return flag;
                        }
                        int third = *((int *)ll->head->next->next->data);
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
