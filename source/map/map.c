/**
  @file map.c
  @brief See header for details
*/
#include "map.h"

typedef struct {
    uint32_t hash;
    void* key;
    void* value;
} map_pair_t;

struct map_t {
    hashfn_t hash_func;
    rbt_t* tree;
};

static void map_pair_free(void* obj)
{
    mem_release(((map_pair_t*)obj)->key);
    mem_release(((map_pair_t*)obj)->value);
}

static map_pair_t* map_pair_new(uint32_t hash, void* key, void* value)
{
    map_pair_t* pair = (map_pair_t*)mem_allocate(sizeof(map_pair_t), &map_pair_free);
    pair->key   = key;
    pair->value = value;
    pair->hash  = hash;
    return pair;
}

static void map_free(void* obj)
{
    mem_release(((map_t*)obj)->tree);
}

static int map_compare_nodes(void* env, void* p_a, void* p_b)
{
    int cmp;
    cmp_t* user_comp = (cmp_t*)env;
    map_pair_t* pair_a = (map_pair_t*)p_a;
    map_pair_t* pair_b = (map_pair_t*)p_b;
    if (pair_a->hash < pair_b->hash) {
        cmp = -1;
    } else if (pair_a->hash > pair_b->hash) {
        cmp = 1;
    } else {
        cmp = cmp_compare(user_comp, pair_a->key, pair_b->key);
    }
    return cmp;
}

map_t* map_new(cmp_t* cmp, hashfn_t hash_fn)
{
    map_t* map  = (map_t*)mem_allocate(sizeof(map_t), &map_free);
    cmp_t* comp = cmp_new(cmp, &map_compare_nodes);
    map->hash_func = hash_fn;
    map->tree = rbt_new(comp);
    return map;
}

bool map_has_key(map_t* map, void* key)
{
    return (NULL != map_lookup(map, key));
}

size_t map_size(map_t* map)
{
    return rbt_size(map->tree);
}

void* map_lookup(map_t* map, void* key)
{
    map_pair_t  pair = { map->hash_func(key), key, NULL };
    rbt_node_t* curr = rbt_lookup(map->tree, &pair);
    void* value = (NULL == curr) ? NULL : ((map_pair_t*)curr->contents)->value;
    return value;
}

void map_insert(map_t* map, void* key, void* value)
{
    map_pair_t* pair = map_pair_new(map->hash_func(key), key, value);
    if (!rbt_lookup(map->tree, pair))
        rbt_insert(map->tree, pair);
    else
        mem_release(pair);
}

void map_delete(map_t* map, void* key)
{
    map_pair_t pair = { map->hash_func(key), key, NULL };
    rbt_delete(map->tree, &pair);
}

