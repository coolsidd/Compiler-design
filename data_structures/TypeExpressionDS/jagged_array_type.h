#include "../linked_list.h"
#include "../../final_code/parse_tree.h"
typedef struct ____RECT_ARRAY_RANGE____ jagged_array_range;

struct ____RECT_ARRAY_RANGE____{
    int lower_bound;
    int higher_bound;
};

typedef struct ____RECT_ARRAY_TYPE____ jagged_array_type;

struct ____RECT_ARRAY_TYPE____{
    int dimensions; // to keep or not? We can keep this in array_ranges.num_nodes
    linked_list array_ranges;
};

//to write function prototypes
jagged_array_type* create_jagged_array_type(Parse_tree_node* p);