#include "../../data_structures/linked_list.h"
#include "../../final_code/parse_tree.h"

#ifndef JAGGED_ARRAY_TYPE_H
#define JAGGED_ARRAY_TYPE_H

typedef struct ____JAGGED_ARRAY_RANGE____ jagged_array_range;

struct ____JAGGED_ARRAY_RANGE____{
    int lower_bound;
    int higher_bound;
};

typedef struct ____JAGGED_ARRAY_TYPE____ jagged_array_type;

struct ____JAGGED_ARRAY_TYPE____{
    int dimensions; // to keep or not? We can keep this in array_ranges.num_nodes
    linked_list* array_ranges;
};

//to write function prototypes
jagged_array_type* create_jagged_array_type(Parse_tree_node* p);

#endif

/*
R2_Dimension:
    linkedlist* sizes
    (sizes is a ll with data as integers)

Jagged_2d:
    UpperBound, Lower Bound;
    R2_Dimension c1;

Jagged_3d:
    UpperBound, Lower Bound
    linked_list* c;
    (linked_list of R2_Dimension(s))

// Functionalities
R2_Dimension* create_R2_Dimension();
void append_size(linked_list* ll, int size);
// to change get_type_expression
// print exp_table
*/