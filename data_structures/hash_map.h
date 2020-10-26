#include <stdlib.h>
#include <string.h>
#include "../util/gen_utils.h"

#ifndef HASH_MAP_H
#define HASH_MAP_H

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

typedef struct ____HASH_MAP____ hash_map;

hash_map *create_hash_map(int num_buckets);

void add_to_hash_map(hash_map *hm, char *string, void *data);

void *fetch_from_hash_map(hash_map *hm, char *string);

void *remove_from_hash_map(hash_map *hm, char *string);

void destroy_hash_map(hash_map *hm);

hm_node *get_all_hm_nodes (hash_map *map);

#endif
