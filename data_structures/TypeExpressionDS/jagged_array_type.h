#include "../linked_list.h"

typedef struct ____RECT_ARRAY_RANGE____ rect_array_range;

struct ____RECT_ARRAY_RANGE____{
    int lower_bound;
    int higher_bound;
};

typedef struct ____RECT_ARRAY_TYPE____ rect_array_type;

struct ____RECT_ARRAY_TYPE____{
    int dimensions; // to keep or not? We can keep this in array_ranges.num_nodes
    linked_list array_ranges;
};

//to write function prototypes