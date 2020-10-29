/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include "grammar_structs.h"

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

void assert(bool condition, char *error_string);

linked_list *create_linked_list();

void ll_add_at(linked_list *ll, void *data, int idx);

void ll_free(linked_list *ll);

void ll_append(linked_list *ll, void *data);

void *ll_get(linked_list *ll, int idx);

#endif
