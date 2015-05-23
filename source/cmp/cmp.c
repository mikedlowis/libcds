/**
  @file cmp.c
  @brief See header for details
  */
#include "cmp.h"

static void cmp_free(void* obj)
{
    cmp_t* cmp = (cmp_t*)obj;
    if ((NULL != obj) && (NULL != cmp->env))
        mem_release(cmp->env);
}

cmp_t* cmp_new(void* env, cmpfn_t fn)
{
    cmp_t* cmp = (cmp_t*)mem_allocate(sizeof(cmp_t), cmp_free);
    cmp->env = env;
    cmp->fn  = fn;
    return cmp;
}

int cmp_compare(cmp_t* cmp, void* obja, void* objb)
{
    return cmp->fn(cmp->env, obja, objb);
}


