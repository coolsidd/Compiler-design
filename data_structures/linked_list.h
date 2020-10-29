#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include "../final_code/gen_utils.h"
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} ll_node;

typedef struct ll {
    ll_node *head;
    ll_node *tail;
    int num_nodes;
} linked_list;

linked_list *create_linked_list();

void ll_add_at(linked_list *ll, void *data, int idx);

void ll_append(linked_list *ll, void *data);

void ll_prepend(linked_list *ll, void *data);

void *ll_remove_at(linked_list *ll, int idx);

void *ll_get(linked_list *ll, int idx);

int ll_num_nodes(linked_list *ll);

#endif
