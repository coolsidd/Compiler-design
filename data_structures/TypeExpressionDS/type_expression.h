

#include "primitive_type.h"
#include "rect_array_type.h"
#include "jagged_array_type.h"
#include "../../data_structures/hash_map.h"

#ifndef TYPE_EXP_H
#define TYPE_EXP_H
// typedef enum {PRIMITIVE_TYPE, RECT_ARRAY, JAGGED_ARRAY} VariableType;
typedef enum {PRIMITIVE_TYPE, RECT_ARRAY, JAGGED_ARRAY} VariableType;

typedef union ____UNION_TO_BE_NAMED____ union_to_be_named;

union ____UNION_TO_BE_NAMED____{
    t_primitive_type primitive_data;
    rect_array_type rect_array_data;
    jagged_array_type jagged_array_data;
};

typedef struct ____TYPE_EXPRESSION____ type_expression;

struct ____TYPE_EXPRESSION____{
    bool is_declared;
    VariableType variable_type; // to keep or not? I thought of keeping it as a Tag/Discriminator for Union
    union_to_be_named union_to_be_named;
};

/* Function Prototypes */

// construct type_expression given the values for reqd fields
// called only through declarative statements of a variable
// how would we pass the fields?
type_expression *construct_type_expression(VariableType variable_type, union_to_be_named union_ds);

// get the desired String Representation of TypeExpression
char* get_string_representation(type_expression* tp);

// set is_declared to true on encountering decl_stmt
void set_declare_flag(type_expression* tp);

#endif