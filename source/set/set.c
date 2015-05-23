/**
  @file set.c
  @brief See header for details
  */
#include "set.h"

typedef struct {
    void* value;
    uint32_t hash;
} set_pair_t;

struct set_t {
    hashfn_t hash_func;
    rbt_t* tree;
};

static void set_pair_free(void* obj)
{
    mem_release(((set_pair_t*)obj)->value);
}

static set_pair_t* set_pair_new(void* value, uint32_t hash)
{
    set_pair_t* pair = (set_pair_t*)mem_allocate(sizeof(set_pair_t), &set_pair_free);
    pair->value = value;
    pair->hash  = hash;
    return pair;
}

static void set_free(void* obj)
{
    mem_release(((set_t*)obj)->tree);
}

static int set_compare_nodes(void* env, void* p_a, void* p_b)
{
    int cmp;
    cmp_t* user_comp = (cmp_t*)env;
    set_pair_t* pair_a = (set_pair_t*)p_a;
    set_pair_t* pair_b = (set_pair_t*)p_b;
    if (pair_a->hash < pair_b->hash) {
        cmp = -1;
    } else if (pair_a->hash > pair_b->hash) {
        cmp = 1;
    } else {
        cmp = cmp_compare(user_comp, pair_a->value, pair_b->value);
    }
    return cmp;
}

set_t* set_new(cmp_t* cmp, hashfn_t hash_fn)
{
    set_t* set  = (set_t*)mem_allocate(sizeof(set_t), &set_free);
    cmp_t* comp = cmp_new(cmp, &set_compare_nodes);
    set->hash_func = hash_fn;
    set->tree = rbt_new(comp);
    return set;
}

bool set_contains(set_t* set, void* value)
{
    set_pair_t pair = { value, set->hash_func(value) };
    return (NULL != rbt_lookup(set->tree, &pair));
}

size_t set_size(set_t* set)
{
    return rbt_size(set->tree);
}

void set_insert(set_t* set, void* value)
{
    set_pair_t* pair = set_pair_new(value, set->hash_func(value));
    if (!rbt_lookup(set->tree, pair))
        rbt_insert(set->tree, pair);
    else
        mem_release(pair);
}

void set_delete(set_t* set, void* value)
{
    set_pair_t pair = { value, set->hash_func(value) };
    rbt_delete(set->tree, &pair);
}

