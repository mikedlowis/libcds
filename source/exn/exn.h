/**
  @file exn.h
  @brief An implementation of exception handling in pure ANSI C.
  $Revision$
  $HeadURL$
*/
#ifndef EXN_H
#define EXN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rt.h"
#include <setjmp.h>

typedef struct exn_t {
    const struct exn_t* p_parent;
} exn_t;

typedef enum {
    EXN_BEGIN   = 0,
    EXN_TRY     = 1,
    EXN_CATCH   = 2,
    EXN_FINALLY = 3,
    EXN_DONE    = 4
} exn_state_t;

typedef struct {
    jmp_buf context;
    exn_state_t state;
} exn_handler_t;

//typedef void (*)(const exn_t* p_exn);

#define DECLARE_EXCEPTION(exname) \
    extern const exn_t exname

#define DEFINE_EXCEPTION(exname, parent) \
    const exn_t exname = { parent }

DECLARE_EXCEPTION(RuntimeException);
DECLARE_EXCEPTION(NullPointerException);
DECLARE_EXCEPTION(AssertionException);
DECLARE_EXCEPTION(AbortException);
DECLARE_EXCEPTION(ArithmeticException);
DECLARE_EXCEPTION(IllegalInstructionException);
DECLARE_EXCEPTION(SegmentationException);

void exn_prep(void);
bool exn_process(void);
void exn_throw(const exn_t* p_type);
void exn_rethrow(void);
bool exn_catch(const exn_t* p_type);
const exn_t* exn_current(void);
exn_handler_t* exn_handler(void);
void exn_assert(bool expr);

#define try \
    for(exn_prep(), setjmp(exn_handler()->context); exn_process();) \
        if (exn_handler()->state == EXN_TRY)

#define catch(type) \
    else if ((exn_handler()->state == EXN_CATCH) && exn_catch(&(type)))

#define finally \
    else if (exn_handler()->state == EXN_FINALLY)

#define throw(type) exn_throw(&(type))

#define rethrow() exn_rethrow()

#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr) exn_assert(expr)
#endif

#ifdef __cplusplus
}
#endif

#endif /* EXN_H */
