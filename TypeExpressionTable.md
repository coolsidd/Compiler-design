## Requirement
According to the assignment PDF, The Type Expression Table is expected to store the following:
 + Field 1: The name of variable extracted from the declaration statement and to be used in the
assignment statement.
 + Field 2: The information about whether it is an array or not, if yes, then whether it is rectangular
array or a jagged array.  
Use numbers enumerated values of 0, 1 and 2 for primitive data type, rectangular array and jagged array respectively.  
The value 0 corresponds to integer, real and Boolean types. However, these primitive type details are filled in the fourth field  
explicitly defining the integer, real or Boolean specifications appropriately.
 + Field 3: If the type is a rectangular array, then whether it is static or dynamic based on the typeof range parameters used in  
defining the array type. If it is not a rectangular array this value is stored as “not_applicable”.
 + Field 4: type expression, which is implemented using the union data type.

## Design Overview
My design is as follows:

## type_exp_table.h
 + We will have a `TYPE_EXPRESSION_TABLE` data structure which would store the `root` node [of a `linked_list` of   
 `TYPE_EXPRESSION_TABLE_NODE`(s)] and the `SYMBOL_TABLE`.
 + A `TYPE_EXPRESSION_TABLE_NODE` would store the Fields(1,2,3) of a variable.
 + `SYMBOL_TABLE` would be implemented as a `HASH_MAP` with the key as `variable_name` and value as  
 `TYPE_EXPRESSION` of the variable.
 + `TYPE_EXPRESSION_TABLE_NODE` would store the first 3 fields as per requirement -:  
     * `variable_name`: `char*`
     * `variable_type`: `VariableType` which is an enum field of `{PRIMITIVE_TYPE, RECT_ARRAY, JAGGED_ARRAY}`
     * `declaration_type`: `DeclarationType` which is an enum field of `{NOT_APPLICABLE, STATIC, DYNAMIC}`

 #### Function Prototypes
 * Initialise the type expression table
     + `type_exp_table* create_type_expression_table();`
 * Get type expression of a variable
     + `type_expression get_type_expression(type_exp_table* t, char* variable);`
 * Add entry
     + `void add_entry_to_table(type_exp_table* t, char* variable_name, VariableType var_type,`  
    `                    declaration_type decl_type, type_expression t);`
 * Remove entry
     + `void remove_entry_from_table(type_exp_table* t, char* variable_name);`

## type_expression.h
 + The `TYPE_EXPRESSION` data structure would store the type expression(Field 4) of a variable  
  (with a unique `variable_name`).
 + The necessary fields of `TYPE_EXPRESSION` are(fields with ** are tentative and under review):
     * `is_declared`: which is set to `true` when a valid `decl_stmt` corresponding to its `variable_name` is encountered.
     * `variable_type`**: could be used as a `tag` for allocating union value.
     * `to_be_named`: The union data structure which would store amongst:  
         + `PrimitiveDataType`
         + `RECT_ARRAY_TYPE`
         + `JAGGED_ARRAY_TYPE`
 ### Function Prototypes
 * Get the desired String Representation of TypeExpression
     + `char* get_string_representation(type_expression tp)`;
 * Set is_declared to true on encountering decl_stmt
     + `void set_declare_flag(type_expression t);`

### [WIP: Docs Incomplete]