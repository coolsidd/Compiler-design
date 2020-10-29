/*
    Given parse_tree_node* p;
    check p->tok->lexeme

    stmt:
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