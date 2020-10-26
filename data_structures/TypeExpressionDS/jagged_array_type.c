#include "jagged_array_type.h"

r2_dimension *create_r2_dimension(){
    r2_dimension* r2 = (r2_dimension*) calloc(1, sizeof(r2_dimension));
    r2->sizes = create_linked_list();
    return r2;
}

void append_size(linked_list *ll, int size){
    ll_append(ll, size);
}
