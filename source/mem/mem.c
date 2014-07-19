#include "mem.h"
#include <stdlib.h>

typedef struct {
    int refcount;
    destructor_t p_finalize;
} obj_t;

typedef struct {
    intptr_t val;
} box_t;

void* mem_allocate(size_t size, destructor_t p_destruct_fn)
{
    obj_t* p_obj = (obj_t*)malloc(sizeof(obj_t) + size);
    p_obj->refcount = 1;
    p_obj->p_finalize = p_destruct_fn;
    return (void*)(p_obj+1);
}

void mem_retain(void* p_obj)
{
    obj_t* p_hdr = (((obj_t*)p_obj)-1);
    p_hdr->refcount += 1;
}

void mem_release(void* p_obj)
{
    obj_t* p_hdr = (((obj_t*)p_obj)-1);
    p_hdr->refcount -= 1;
    if(p_hdr->refcount < 1)
    {
        if(p_hdr->p_finalize)
        {
            p_hdr->p_finalize(p_obj);
        }
        free(p_hdr);
    }
}

void mem_autorelease(void* p_obj)
{
}

void mem_releaseall(void)
{
}

void* mem_box(intptr_t val)
{
    box_t* p_box = (box_t*)mem_allocate(sizeof(box_t), NULL);
    p_box->val = val;
    return (void*)p_box;
}

intptr_t mem_unbox(void* p_box)
{
    return ((box_t*)p_box)->val;
}

