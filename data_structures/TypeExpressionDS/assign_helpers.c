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

type_expression* get_integer_type(){
    type_expression* txp = (type_expression *)calloc(1, sizeof(type_expression));
    set_declare_flag(txp);
    txp->variable_type = PRIMITIVE_TYPE;
    txp->union_to_be_named.primitive_data = INTEGER;
    return txp;
}

type_expression *get_real_type()
{
    type_expression *txp = (type_expression *)calloc(1, sizeof(type_expression));
    set_declare_flag(txp);
    txp->variable_type = PRIMITIVE_TYPE;
    txp->union_to_be_named.primitive_data = REAL;
    return txp;
}

type_expression *get_bool_type()
{
    type_expression *txp = (type_expression *)calloc(1, sizeof(type_expression));
    set_declare_flag(txp);
    txp->variable_type = PRIMITIVE_TYPE;
    txp->union_to_be_named.primitive_data = BOOLEAN;
    return txp;
}

// <arithmeticexpr>-><term> PLUS<arithmeticexpr> | <term> MINUS<arithmeticexpr> | <term> OR<arithmeticexpr> | <term>
type_expression *get_type_of_arithm_expr(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression* txp = get_type_of_term(txp_table, p->child);
    if(p->last_child->tok->lexeme.s == term){
        return txp;
    }
    else if(p->last_child->tok->lexeme.s == arithmeticexpr){
        type_expression* txp_1 = get_type_of_arithm_expr(txp_table, p->last_child);
        switch(getNodeFromIndex(p->child, 1)->tok->lexeme.s){
            case (OR):
            {
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == PRIMITIVE_TYPE && txp->variable_type == PRIMITIVE_TYPE, "OR can only be applied to boolean terms");
                if(flag)
                {
                    flag &= assert_debug(txp_1->union_to_be_named.primitive_data == BOOLEAN &&
                    txp->union_to_be_named.primitive_data == BOOLEAN, 
                    "OR can only be applied to boolean terms");
                    if(flag)
                        return get_bool_type();
                }
                break;
            }
            default:
            { 
                /*
                    done: Both should be of same variable type
                    Array_Types-> check dimensions
                    done: Boolean-> type-error
                    done: primitive-> integer, integer or real,real 
                */
               bool flag = true;
                flag &= assert_debug(txp_1->variable_type == txp->variable_type,
                    "Type of left and right operand should be same");
                switch(txp_1->variable_type){
                    case(PRIMITIVE_TYPE):
                    {
                        assert_debug(txp_1->union_to_be_named.primitive_data ==
                            txp->union_to_be_named.primitive_data,
                            "Left and Right Operand should be of same Primitive Type");
                        assert_debug(txp_1->union_to_be_named.primitive_data==BOOLEAN,
                        "PLUS and MINUS are not for boolean types.");
                        if(txp_1->union_to_be_named.primitive_data==INTEGER){
                            return get_integer_type();
                        }
                        else if(txp_1->union_to_be_named.primitive_data==REAL){
                            return get_real_type();
                        }
                        else{
                            return NULL;
                        }
                        break;
                    }
                    case(RECT_ARRAY):
                    {
                        bool flag = check_rect_dimensions(txp->union_to_be_named.rect_array_data,
                            txp_1->union_to_be_named.rect_array_data);
                        // TODO: Check flag or not
                        return get_integer_type();
                        break;
                    }
                    case(JAGGED_ARRAY):
                    {
                        bool flag = check_jagged_dimensions(txp->union_to_be_named.jagged_array_data,
                            txp_1->union_to_be_named.jagged_array_data);
                        // TODO: Check flag or not
                        return get_integer_type();
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

type_expression* get_type_of_term(type_exp_table* txp_table, Parse_tree_node* p){
    type_expression *txp = get_type_of_fact(txp_table, p->child);
    if (p->last_child->tok->lexeme.s == fact)
    {
        return txp;
    }
    else if (p->last_child->tok->lexeme.s == term)
    {
        type_expression *txp_1 = get_type_of_term(txp_table, p->last_child);
        switch (getNodeFromIndex(p->child, 1)->tok->lexeme.s)
        {
            case (AND):
            {
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == PRIMITIVE_TYPE && txp->variable_type == PRIMITIVE_TYPE, "AND can only be applied to boolean terms");
                if (flag)
                {
                    flag &= assert_debug(txp_1->union_to_be_named.primitive_data == BOOLEAN &&
                                            txp->union_to_be_named.primitive_data == BOOLEAN,
                                        "AND can only be applied to boolean terms");
                    if (flag)
                        return get_bool_type();
                }
                break;
            }
            case (MULT):
            {
                /*
                    done: Both should be of same variable type
                    Array_Types-> check dimensions
                    done: Boolean-> type-error
                    done: primitive-> integer, integer or real,real 
                */
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == txp->variable_type,
                                     "Type of left and right operand should be same");
                switch (txp_1->variable_type)
                {
                    case (PRIMITIVE_TYPE):
                    {
                        assert_debug(txp_1->union_to_be_named.primitive_data ==
                                        txp->union_to_be_named.primitive_data,
                                    "Left and Right Operand should be of same Primitive Type");
                        assert_debug(txp_1->union_to_be_named.primitive_data == BOOLEAN,
                                    "PLUS and MINUS are not for boolean types.");
                        if (txp_1->union_to_be_named.primitive_data == INTEGER)
                            return get_integer_type();
                        else if (txp_1->union_to_be_named.primitive_data == REAL)
                            return get_real_type();
                        else
                            return NULL;
                        break;
                    }
                    case (RECT_ARRAY):
                    {
                        bool flag = check_rect_dimensions(txp->union_to_be_named.rect_array_data,
                                                        txp_1->union_to_be_named.rect_array_data);
                        // TODO: Check flag or not
                        return get_integer_type();
                        break;
                    }
                    case (JAGGED_ARRAY):
                    {
                        bool flag = check_jagged_dimensions(txp->union_to_be_named.jagged_array_data,
                                                            txp_1->union_to_be_named.jagged_array_data);
                        // TODO: Check flag or not
                        return get_integer_type();
                        break;
                    }
                }
            }
            case (DIV):
            {
                /*
                    done: Both should be of same variable type
                    Array_Types-> check dimensions
                    done: Boolean-> type-error
                    done: primitive-> integer, integer or real,real 
                */
                bool flag = true;
                flag &= assert_debug(txp_1->variable_type == txp->variable_type,
                                     "Type of left and right operand should be same");
                switch (txp_1->variable_type)
                {
                    case (PRIMITIVE_TYPE):
                    {
                        assert_debug(txp_1->union_to_be_named.primitive_data ==
                                        txp->union_to_be_named.primitive_data,
                                    "Left and Right Operand should be of same Primitive Type");
                        assert_debug(txp_1->union_to_be_named.primitive_data == BOOLEAN,
                                    "PLUS and MINUS are not for boolean types.");
                        if (txp_1->union_to_be_named.primitive_data == INTEGER ||
                            txp_1->union_to_be_named.primitive_data == REAL)
                            return get_integer_type();
                        else
                            return NULL;
                        break;
                    }
                    case (RECT_ARRAY):
                    {
                        bool flag = check_rect_dimensions(txp->union_to_be_named.rect_array_data,
                                                        txp_1->union_to_be_named.rect_array_data);
                        // TODO: Check flag or not
                        return get_real_type();
                        break;
                    }
                    case (JAGGED_ARRAY):
                    {
                        bool flag = check_jagged_dimensions(txp->union_to_be_named.jagged_array_data,
                                                            txp_1->union_to_be_named.jagged_array_data);
                        // TODO: Check flag or not
                        return get_integer_type();
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
}

bool check_rect_dimensions(rect_array_type r1, rect_array_type r2){
    bool flag = true;
    flag &= assert_debug(r1.dimensions == r2.dimensions, "Rect Array Dimensions Mismatch");
    if(!flag){
        return flag;
    }
    else{
        ll_node* temp_1 = r2.array_ranges->head;
        for (ll_node *temp = r1.array_ranges->head;temp;temp=temp->next){
            rect_array_range* r1 = (rect_array_range*) temp->data;
            rect_array_range* r2 = (rect_array_range*) temp_1->data;
            flag &= assert_debug(r1->upper_bound - r1->lower_bound == 
                                r2->upper_bound - r2->lower_bound,
                                "Rect Array Dimensions Mismatch");
            if(!flag)
                break;
            temp_1 = temp_1->next;
        }
    }
    return flag;
}

bool check_jagged_dimensions(jagged_array_type j1, jagged_array_type j2){
    bool flag = true;
    flag &= assert_debug(j1.dimensions == j2.dimensions,
                        "Jagged Array Dimensions Mismatch");
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
                                "Jagged Array Dimensions Mismatch");
            if (!flag)
            {
                return flag;
            }
            ll_node* j2_sizes = temp.row_sizes.sizes->head;
            for (ll_node *j1_sizes = temp.row_sizes.sizes->head; j1_sizes; j1_sizes = j1_sizes->next){
                flag&=assert_debug( *((int*)(j1_sizes->data)) == *((int*)(j2_sizes->data)),
                                    "Jagged Array Dimensions Mismatch"); 
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
                                 "Jagged Array Dimensions Mismatch");
            if (!flag)
            {
                return flag;
            }

            ll_node *j1_sizes = temp.row_sizes->head;
            for (ll_node *j2_sizes = temp.row_sizes->head; j2_sizes; j2_sizes = j2_sizes->next)
            {
                ll_node* t1 = ((linked_list*)j2_sizes->data)->head;
                for (ll_node *t2 = ((linked_list *)j2_sizes->data)->head; t2; t2=t2->next)
                {
                    flag &= assert_debug(*((int*)(t1->data)) == *((int *)(t2->data)),
                                         "Jagged Array Dimensions Mismatch");
                    if (!flag)
                        break;
                    t1 = t1->next;
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