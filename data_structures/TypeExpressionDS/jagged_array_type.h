/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#ifndef JAGGED_ARRAY_TYPE_H
#define JAGGED_ARRAY_TYPE_H

#include "../../data_structures/linked_list.h"
#include "../../final_code/parse_tree.h"

typedef struct ____R2_DIMENSION____ r2_dimension;

struct ____R2_DIMENSION____{
    linked_list* sizes;
};

typedef struct ____JAGGED_2D____ jagged_2d;

struct ____JAGGED_2D____
{
    int lower_bound;
    int upper_bound;
    r2_dimension row_sizes;
};

typedef struct ____JAGGED_3D____ jagged_3d;

struct ____JAGGED_3D____
{
    int lower_bound;
    int upper_bound;
    linked_list* row_sizes;
};

typedef struct ____JAGGED_ARRAY_TYPE____ jagged_array_type;

struct ____JAGGED_ARRAY_TYPE____{
    int dimensions;
    union array_type{
        jagged_2d j2d;
        jagged_3d j3d;
    }array_type;
};

jagged_2d* create_jagged_2d();
jagged_3d* create_jagged_3d();
r2_dimension* create_r2_dimension();
void append_size(linked_list *ll, int size);
jagged_array_type* create_jagged_array_type(Parse_tree_node *p);

#endif
