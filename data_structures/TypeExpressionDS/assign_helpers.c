/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#include "assign_helpers.h"

// <fact> -> <var> | LPAREN <arithmeticexpr> RPAREN
type_expression *get_type_of_fact(type_exp_table *txp_table, Parse_tree_node* p){
    if(p->child->tok->lexeme.s == var){
        return get_type_of_var(txp_table, p->child);
    }
    else if(p->last_child->tok->lexeme.s == RPAREN){
        return get_type_of_arithm_expr(txp_table, getNodeFromIndex(p->child, 1));
    }
    else{
        return NULL;
    }
}

// <arithmeticexpr>-><term> PLUS <arithmeticexpr> | <term> MINUS <arithmeticexpr> | <term> OR <arithmeticexpr> | <term>
type_expression *get_type_of_arithm_expr(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression* txp = get_type_of_term(txp_table, p->child);
    if(p->last_child->tok->lexeme.s == term){
        return txp;
    }
    else if(p->last_child->tok->lexeme.s == arithmeticexpr){
        type_expression* txp_1 = get_type_of_arithm_expr(txp_table, p->last_child);
        char* t1 = str_type(txp);
        char* t2 = str_type(txp_1);
        char* lexeme1 = "term";
        char* lexeme2 = "arithmeticexpr";
        if (!(txp && txp_1))
            return NULL;
        switch(getNodeFromIndex(p->child, 1)->tok->lexeme.s){
            case (OR):
            {
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == PRIMITIVE_TYPE && txp->variable_type == PRIMITIVE_TYPE,
                "OR with Non-Boolean Operands", p, t1, t2, "OR", lexeme1, lexeme2);
                if(flag){
                    flag &= assert_debug(txp_1->union_to_be_named.primitive_data == t_BOOLEAN &&
                    txp->union_to_be_named.primitive_data == t_BOOLEAN,"OR with Non-Boolean Operands",
                    p, t1, t2, "OR", lexeme1, lexeme2);
                }
                return get_bool_type();
                break;
            }
            default:
            {
                char *operator= toStringSymbol(getNodeFromIndex(p->child, 1)->tok->lexeme);
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == txp->variable_type,
                                    "Different Left & Right operand",
                                    p, t1, t2, operator, lexeme1, lexeme2);
                if (!flag)
                    return NULL;
                switch(txp_1->variable_type){
                    case(PRIMITIVE_TYPE):
                    {
                        flag &= assert_debug(txp_1->union_to_be_named.primitive_data ==
                        txp->union_to_be_named.primitive_data,"Different Left & Right Operand",
                        p, t1, t2, operator, lexeme1, lexeme2);
                        flag &= assert_debug(txp_1->union_to_be_named.primitive_data!=t_BOOLEAN,
                                            "ADD or SUB with Bool Operand",
                                            p, t1, t2, operator, lexeme1, lexeme2);

                        if(flag && txp_1->union_to_be_named.primitive_data==t_INTEGER){
                            return get_integer_type();
                        }
                        else if(flag && txp_1->union_to_be_named.primitive_data==t_REAL){
                            return get_real_type();
                        }
                        else{
                            return txp; // TODO Default type is of LHS
                        }
                        break;
                    }
                    case(RECT_ARRAY):
                    {
                        bool flag = check_rect_dimensions(txp->union_to_be_named.rect_array_data,
                            txp_1->union_to_be_named.rect_array_data, p, t1, t2, operator,
                            lexeme1, lexeme2);

                        return txp; // TODO Default type if of LHS
                        break;
                    }
                    case(JAGGED_ARRAY):
                    {
                        bool flag = check_jagged_dimensions(txp->union_to_be_named.jagged_array_data,
                            txp_1->union_to_be_named.jagged_array_data, p, t1, t2, operator,
                            lexeme1, lexeme2);

                        return txp;  // TODO Default type if of LHS
                        break;
                    }
                }
            }
        }

    }
    else{
        return NULL;
    }
}


// TODO Return txp as done above (get_type_of_arithexp)
type_expression* get_type_of_term(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression *txp = get_type_of_fact(txp_table, p->child);
    if (p->last_child->tok->lexeme.s == fact)
    {
        return txp;
    }
    else if (p->last_child->tok->lexeme.s == term)
    {
        type_expression *txp_1 = get_type_of_term(txp_table, p->last_child);
        char *t1 = str_type(txp);
        char *t2 = str_type(txp_1);
        char *lexeme1 = "fact";
        char *lexeme2 = "term";
        if(!(txp && txp_1))
            return NULL;
        switch (getNodeFromIndex(p->child, 1)->tok->lexeme.s)
        {
            case (AND):
            {
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == PRIMITIVE_TYPE && txp->variable_type == PRIMITIVE_TYPE,
                                     "AND with Non-Bool Operand",
                                     p, t1, t2, "AND", lexeme1, lexeme2);
                if(flag){
                    flag &= assert_debug(txp_1->union_to_be_named.primitive_data == t_BOOLEAN &&
                                             txp->union_to_be_named.primitive_data == t_BOOLEAN,
                                         "AND with Non-Bool Operand",
                                         p, t1, t2, "AND", lexeme1, lexeme2);
                }
                return get_bool_type();
                break;
            }
            case (MULT):
            {
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == txp->variable_type,
                                    "Different Left & Right Operand", p,
                                    t1, t2, "MULT", lexeme1, lexeme2);
                if(!flag) return NULL;
                switch (txp_1->variable_type)
                {
                    case (PRIMITIVE_TYPE):
                    {
                        flag &= assert_debug(txp_1->union_to_be_named.primitive_data ==
                                                 txp->union_to_be_named.primitive_data,
                                             "Different Left & Right Operand",
                                             p, t1, t2, "MULT", lexeme1, lexeme2);
                        flag &= assert_debug(txp_1->union_to_be_named.primitive_data != t_BOOLEAN,
                                            "MULT with Bool Operand",
                                            p, t1, t2, "MULT", lexeme1, lexeme2);
                        if (flag && txp_1->union_to_be_named.primitive_data == t_INTEGER){
                            return get_integer_type();
                        }
                        else if (flag && txp_1->union_to_be_named.primitive_data == t_REAL){
                            return get_real_type();
                        }
                        else{
                            return txp; // TODO Default type is of LHS
                        }
                        break;
                    }
                    case (RECT_ARRAY):
                    {
                        bool flag = check_rect_dimensions(txp->union_to_be_named.rect_array_data, 
                                            txp_1->union_to_be_named.rect_array_data, p,
                                            t1, t2, "MULT", lexeme1, lexeme2); 
                        return txp; // TODO Default type is of LHS
                        break;
                    }
                    case (JAGGED_ARRAY):
                    {
                        bool flag = check_jagged_dimensions(txp->union_to_be_named.jagged_array_data,
                                            txp_1->union_to_be_named.jagged_array_data, p,
                                            t1, t2, "MULT", lexeme1, lexeme2);
                        return txp; // TODO Default type is of LHS
                        break;
                    }
                }
            }
            case (DIV):
            {
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == txp->variable_type,
                                     "Different Left & Right Operand",
                                     p, t1, t2, "DIV", lexeme1, lexeme2);
                if (!flag)
                    return NULL;
                switch (txp_1->variable_type)
                {
                    case (PRIMITIVE_TYPE):
                    {
                        flag &= assert_debug(txp_1->union_to_be_named.primitive_data ==
                                            txp->union_to_be_named.primitive_data,
                                             "Different Left & Right Operand",
                                             p, t1, t2, "DIV", lexeme1, lexeme2);
                        flag &= assert_debug(txp_1->union_to_be_named.primitive_data != t_BOOLEAN,
                                            "DIV of Bool Operands",
                                            p, t1, t2, "DIV", lexeme1, lexeme2);
                        if (flag && (txp_1->union_to_be_named.primitive_data == t_INTEGER ||
                            txp_1->union_to_be_named.primitive_data == t_REAL))
                            return get_real_type();
                        else
                            return txp; // TODO Default type is of LHS
                        break;
                    }
                    case (RECT_ARRAY):
                    {
                        bool flag = check_rect_dimensions(txp->union_to_be_named.rect_array_data,
                                            txp_1->union_to_be_named.rect_array_data, p,
                                            t1, t2, "DIV", lexeme1, lexeme2);
                        return txp; // TODO Default type is of LHS
                        break;
                    }
                    case (JAGGED_ARRAY):
                    {
                        bool flag = check_jagged_dimensions(txp->union_to_be_named.jagged_array_data,
                                            txp_1->union_to_be_named.jagged_array_data, p,
                                            t1, t2, "DIV", lexeme1, lexeme2);
                        return txp; // TODO Default type is of LHS
                        break;
                    }
                }
            }
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

type_expression* get_type_exp_of_expr(type_exp_table* txp_table, Parse_tree_node* p){
    return get_type_of_arithm_expr(txp_table, p->child);
}

type_expression* get_type_of_var_lhs(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression *txp = (type_expression*) calloc(1, sizeof(type_expression));

    if (p->last_child->tok->lexeme.s == SQBC)
    {
        type_expression *txp = get_type_of_var(txp_table, getNodeFromIndex(p->child, 2)->child);
        if(!assert_debug(txp!=NULL, "Var used before Declaration", p, "***", "***", "***", "***", "***"))
            return NULL;
        linked_list *bounds = get_type_of_index_list(txp_table, getNodeFromIndex(p->child, 2));
        bool flag = do_bound_checking(txp_table, p->child, bounds);
        
        return get_integer_type();
    }

    else if (p->last_child->tok->lexeme.s == ID)
    {
        txp = get_type_expression(txp_table, p->last_child->tok->token_name);
        bool flag = assert_debug(txp != NULL, "Var used before Declaration", p, "***", "***", "***", "***", "***");
        return txp;
    }
    return NULL;
}

bool check_rect_dimensions(rect_array_type r1, rect_array_type r2, Parse_tree_node* p,
                        char *t1, char *t2, char *operator, char *lexeme1, char *lexeme2)
{
    bool flag = true;
    flag &= assert_debug(r1.dimensions == r2.dimensions, "RectArray Dimensions Mismatch",
                        p, t1, t2, operator, lexeme1, lexeme2);
    if(!flag) 
        return flag;
    else{
        ll_node* temp_1 = r2.array_ranges->head;
        for (ll_node *temp = r1.array_ranges->head;temp;temp=temp->next){
            rect_array_range range1 = *(rect_array_range*)(temp->data);
            rect_array_range range2 = *(rect_array_range*)(temp_1->data);
            flag &= assert_debug(range1.upper_bound - range1.lower_bound ==
                                range2.upper_bound - range2.lower_bound,
                                "RectArray Dimensions Mismatch",
                                p, t1, t2, operator, lexeme1, lexeme2);
            temp_1 = temp_1->next;
            if(!flag)
                break;
        }
    }
    return flag;
}

bool check_jagged_dimensions(jagged_array_type j1, jagged_array_type j2, Parse_tree_node* p,
                            char* t1, char* t2, char* operator, char* lexeme1, char* lexeme2){
    bool flag = true;
    flag &= assert_debug(j1.dimensions == j2.dimensions,
                        "JgdArray Dimensions Mismatch",
                        p, t1, t2, operator, lexeme1, lexeme2);
    if(!flag){
        return flag;
    }
    switch(j1.dimensions)
    {
        case 2:
        {
            jagged_2d temp = j1.array_type.j2d;
            jagged_2d temp_1 = j2.array_type.j2d;
            flag &= assert_debug(temp.upper_bound - temp.lower_bound ==
                                temp_1.upper_bound - temp_1.lower_bound,
                                "JgdArray Dimensions Mismatch",
                                p, t1, t2, operator, lexeme1, lexeme2);
            if (!flag)
            {
                return flag;
            }
            ll_node* j2_sizes = temp.row_sizes.sizes->head;
            for (ll_node *j1_sizes = temp.row_sizes.sizes->head; j1_sizes; j1_sizes = j1_sizes->next){
                flag &= assert_debug(*((int *)(j1_sizes->data)) == *((int *)(j2_sizes->data)),
                                    "JgdArray Dimensions Mismatch",
                                    p, t1, t2, operator, lexeme1, lexeme2);
                j2_sizes = j2_sizes->next;
                if(!flag)
                    break;
            }
            return flag;
            break;
        }
        case 3:
        {
            jagged_3d temp = j1.array_type.j3d;
            jagged_3d temp_1 = j2.array_type.j3d;
            flag &= assert_debug(temp.upper_bound - temp.lower_bound ==
                                temp_1.upper_bound - temp_1.lower_bound,
                                "JgdArray Dimensions Mismatch",
                                p, t1, t2, operator, lexeme1, lexeme2);
            if (!flag)
            {
                return flag;
            }

            ll_node *j1_sizes = temp.row_sizes->head;
            for (ll_node *j2_sizes = temp.row_sizes->head; j2_sizes; j2_sizes = j2_sizes->next)
            {
                ll_node* ll_t1 = ((linked_list*)j2_sizes->data)->head;
                for (ll_node *ll_t2 = ((linked_list *)j2_sizes->data)->head; ll_t2; ll_t2=ll_t2->next)
                {
                    flag &= assert_debug(*((int *)(ll_t1->data)) == *((int *)(ll_t2->data)),
                                        "JgdArray Dimensions Mismatch",
                                        p, t1, t2, operator, lexeme1, lexeme2);
                    if (!flag)
                        break;
                    ll_t1 = ll_t1->next;
                }
                if(!flag)
                    break;
                j1_sizes = j1_sizes->next;
            }
            return flag;
            break;
        }
    }
}
