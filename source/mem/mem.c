#include "mem.h"
#include <stdlib.h>
#include <assert.h>
#ifdef LEAK_DETECT_LEVEL
#include <stdbool.h>
#include <stdio.h>
#endif

typedef struct {
    int refcount;
    destructor_t p_finalize;
} obj_t;

typedef struct {
    intptr_t val;
} box_t;

/* If leak detection is turned on then we need to disable the mem_allocate macro
 * for the duration of this file. This allows us to use the original
 * mem_allocate function without modification in mem_allocate_ld */
#if (LEAK_DETECT_LEVEL == 2)
#undef mem_allocate
void* mem_allocate(size_t size, destructor_t p_destruct_fn);
#endif

#if (LEAK_DETECT_LEVEL > 0)
bool Handler_Registered = false;

#if (LEAK_DETECT_LEVEL == 2)
typedef struct block_t {
    void* p_obj;
    const char* p_file;
    int line;
    struct block_t* p_next;
} block_t;

block_t* Live_Blocks = NULL;
#elif (LEAK_DETECT_LEVEL == 1)
size_t Num_Allocations = 0;
#endif

static void summarize_leaks(void) {
    #if (LEAK_DETECT_LEVEL == 2)
    bool leak_detected = false;
    block_t* p_curr = Live_Blocks;
    /* Print out all the live blocks and where they were allocated from */
    while (NULL != p_curr)
    {
        block_t* to_be_freed = p_curr;
        printf("%p %s (line %d): %d references to object\n",
               p_curr->p_obj,
               p_curr->p_file,
               p_curr->line,
               mem_num_references(p_curr->p_obj));
        p_curr = p_curr->p_next;
        free(to_be_freed);
        leak_detected = true;
    }
    if(leak_detected)
        puts("Memory leak(s) detected!");
    #elif (LEAK_DETECT_LEVEL == 1)
    if(Num_Allocations > 0) {
        puts("Warning: Memory leak(s) detected!");
        printf("\nFor more details set the LEAK_DETECT_LEVEL build option to 2 or run the executable in valgrind.\n");
    }
    #endif
}

#if (LEAK_DETECT_LEVEL == 2)
void* mem_allocate_ld(size_t size, destructor_t p_destruct_fn, const char* p_file, int line)
{
    /* Allocate the object through the ordinary method */
    void* p_obj = mem_allocate(size, p_destruct_fn);
    /* Create a metadata block for it to track it's usage. */
    block_t* p_block = (block_t*)malloc(sizeof(block_t));
    p_block->p_obj  = p_obj;
    p_block->p_file = p_file;
    p_block->line   = line;
    p_block->p_next = Live_Blocks;
    Live_Blocks     = p_block;
    /* If we haven't already, register an exit handler that will printout the
     * unfreed objects before the program quits */
    if(!Handler_Registered)
    {
        atexit(summarize_leaks);
        Handler_Registered = true;
    }
    return p_obj;
}
#endif
#endif

#if (LEAK_DETECT_LEVEL == 2)
static void deregister_block(void* p_obj)
{
    block_t* p_prev = NULL;
    block_t* p_curr = Live_Blocks;
    while(NULL != p_curr)
    {
        if (p_obj == p_curr->p_obj)
        {
            block_t* p_doomed = p_curr;
            if(p_prev == NULL)
            {
                Live_Blocks = p_curr->p_next;
            }
            else
            {
                p_prev->p_next = p_curr->p_next;
            }
            free(p_doomed);
            break;
        }
        else
        {
            p_prev = p_curr;
            p_curr = p_curr->p_next;
        }
    }
}
#endif

void* mem_allocate(size_t size, destructor_t p_destruct_fn)
{
    obj_t* p_obj = (obj_t*)malloc(sizeof(obj_t) + size);
    p_obj->refcount = 1;
    p_obj->p_finalize = p_destruct_fn;
    #if (LEAK_DETECT_LEVEL == 1)
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

int mem_num_references(void* p_obj)
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
    assert(NULL != p_obj);
    p_hdr = (((obj_t*)p_obj)-1);
    p_hdr->refcount -= 1;
    if(p_hdr->refcount < 1)
    {
        #if (LEAK_DETECT_LEVEL == 2)
        deregister_block(p_obj);
        #elif (LEAK_DETECT_LEVEL == 1)
        Num_Allocations--;
        #endif
        if(p_hdr->p_finalize)
        {
            p_hdr->p_finalize(p_obj);
        }
        free(p_hdr);
    }
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

