#include <stdlib.h>
#include "../../util/gen_utils.h"

#include "rect_array_type.h"

typedef enum {false, true} bool;

typedef enum {PRIMITIVE_TYPE, RECT_ARRAY, JAGGED_ARRAY} VariableType;

typedef enum {BOOLEAN, INTEGER, REAL} PrimitiveDataType;

typedef union ____UNION_TO_BE_NAMED____ union_to_be_named;

union ____UNION_TO_BE_NAMED____{
    PrimitiveDataType primitive_datatype;
    rect_array_type rect_array_data;
    jagged_array_type jagged_array_data;
};

typedef struct ____TYPE_EXPRESSION____ type_expression;

struct ____TYPE_EXPRESSION____{
    bool is_declared;
    VariableType variable_type; // to keep or not? I thought of keeping it as a Tag/Discriminator for Union
    UNION_TO_BE_NAMED union_to_be_named;
};

/* Function Prototypes */

// construct type_expression given the values for reqd fields
// called only through declarative statements of a variable
// how would we pass the fields?
type_expression construct_type_expression(VariableType variable_type);

// get the desired String Representation of TypeExpression
char* get_string_representation(type_expression tp);

// set is_declared to true on encountering decl_stmt
void set_declare_flag(type_expression t);





