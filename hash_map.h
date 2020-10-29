/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>
#include <string.h>
#include "gen_utils.h"

typedef struct hmnode {
    char *string;
    void *data;
    struct hmnode *next;
} hm_node;

typedef struct hmb
{
    hm_node *first;
    int num_nodes;
} hm_bucket;


typedef struct hm {
    hm_bucket **buckets;
    int num_buckets;
} hash_map;

hash_map *create_hash_map(int num_buckets);

void add_to_hash_map(hash_map *hm, char *string, void *data);

void *fetch_from_hash_map(hash_map *hm, char *string);

void destroy_hash_map(hash_map *hm);

void free_hash_map(hash_map *new_hm );

#endif
