#include "../linked_list.h"

typedef struct ____RECT_ARRAY_RANGE____ rect_array_range;

struct ____RECT_ARRAY_RANGE____{
    int lower_bound;
    int higher_bound;
};

typedef struct ____RECT_ARRAY_TYPE____ rect_array_type;

struct ____RECT_ARRAY_TYPE____{
    int dimensions; // to keep or not? We can keep this in array_ranges.num_nodes
    linked_list* array_ranges;
};

/* Function Prototypes */

// initialise rect_array_type
rect_array_type* create_rect_array_type();

// get number of dimensions of rect array
int get_dimension(rect_array_range* r_type);

// add range at index 'idx' of rect array
void add_range_at(rect_array_type *r_type, void *data, int idx);

// append range of rect array
void append_range(rect_array_type* r_type, rect_array_range* r);

// remove range of rect array
void remove_range_at(rect_array_type* r_type, rect_array_range* r, int idx);

// get range at an index
rect_array_range* get_range_by_index(rect_array_range* r, int idx);