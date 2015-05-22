/**
  @file set.h
  @brief TODO: Describe this file
  */
#ifndef SET_H
#define SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rbt.h"

typedef uint32_t (*hashfn_t)(const void* obj);

struct set_t;
typedef struct set_t set_t;

set_t* set_new(comparator_t comparator);

bool set_contains(set_t* p_set, void* value);

size_t set_size(set_t* set);

void set_insert(set_t* set, void* value);

void set_delete(set_t* set, void* value);

#ifdef __cplusplus
}
#endif

#endif /* SET_H */
