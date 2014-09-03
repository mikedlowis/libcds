/**
  @file cursor.h
  @brief Generic cursor module for moving over data structures.
  $Revision$
  $HeadURL$
  */
#ifndef CURSOR_H
#define CURSOR_H

#include "mem.h"

typedef enum {
    FORWARD,
    BACKWARD
} advance_dir_t;

typedef bool (*tester_t)(void* env, advance_dir_t dir);

typedef void (*advancer_t)(void* env, advance_dir_t dir);

typedef void* (*getter_t)(void* env);

typedef void (*setter_t)(void* env, void* val);

struct crsr_t;

typedef struct crsr_t crsr_t;

crsr_t* crsr_new(void* p_state, tester_t p_test, advancer_t p_advance, getter_t p_get, setter_t p_set);
crsr_t* crsr_copy(crsr_t* p_crsr);
void crsr_advance(crsr_t* p_crsr, int steps);
void crsr_next(crsr_t* p_crsr);
void crsr_prev(crsr_t* p_crsr);
bool crsr_has_next(crsr_t* p_crsr);
bool crsr_has_prev(crsr_t* p_crsr);
void* crsr_get(crsr_t* p_crsr);
void crsr_set(crsr_t* p_crsr, void* val);

#endif /* CURSOR_H */
