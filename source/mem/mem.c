/**
  @file mem.c
  @brief See header for details
  */
#include "mem.h"
#include <stdio.h>

typedef struct {
    int refcount;
    destructor_t p_finalize;
} obj_t;

typedef struct {
    intptr_t val;
} box_t;

#if (LEAK_DETECT_LEVEL > 0)
bool Handler_Registered = false;
size_t Num_Allocations = 0;
#endif

#if (LEAK_DETECT_LEVEL > 0)
#ifndef TESTING
static
#endif
void summarize_leaks(void) {
    if(Num_Allocations > 0) {
        puts("Warning: Memory leak(s) detected!");
        printf("\nFor more details set the LEAK_DETECT_LEVEL build option to 2 or run the executable in valgrind.\n");
    }
}
#endif

void* mem_allocate(size_t size, destructor_t p_destruct_fn)
{
    obj_t* p_obj = (obj_t*)malloc(sizeof(obj_t) + size);
    p_obj->refcount = 1;
    p_obj->p_finalize = p_destruct_fn;
#if (LEAK_DETECT_LEVEL > 0)
    Num_Allocations++;
    /* If we haven't already, register an exit handler that will printout the
     * unfreed objects before the program quits */
    if(!Handler_Registered)
    {
        atexit(summarize_leaks);
        Handler_Registered = true;
    }
#endif
    return (void*)(p_obj+1);
}

int mem_refcount(void* p_obj)
{
    obj_t* p_hdr;
    assert(NULL != p_obj);
    p_hdr = (((obj_t*)p_obj)-1);
    return p_hdr->refcount;
}

void* mem_retain(void* p_obj)
{
    obj_t* p_hdr;
    assert(NULL != p_obj);
    p_hdr = (((obj_t*)p_obj)-1);
    p_hdr->refcount += 1;
    return p_obj;
}

void mem_release(void* p_obj)
{
    obj_t* p_hdr;
    if (NULL != p_obj) {
        p_hdr = (((obj_t*)p_obj)-1);
        p_hdr->refcount -= 1;
        if(p_hdr->refcount < 1)
        {
            #if (LEAK_DETECT_LEVEL > 0)
            Num_Allocations--;
            #endif
            if(p_hdr->p_finalize)
            {
                p_hdr->p_finalize(p_obj);
            }
            free(p_hdr);
        }
    }
}

void mem_swap(void** loc, void* obj)
{
    void* old = *loc;
    *loc = obj;
    mem_release(old);
}

void* mem_box(intptr_t val)
{
    box_t* p_box = (box_t*)mem_allocate(sizeof(box_t), NULL);
    p_box->val = val;
    return (void*)p_box;
}

intptr_t mem_unbox(void* p_box)
{
    assert(NULL != p_box);
    return ((box_t*)p_box)->val;
}

