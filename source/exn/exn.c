/**
  @file exn.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include "exn.h"
#include <stdio.h>

#ifdef TESTING
extern void test_exit(int);
#define exit(status) test_exit(status)
#endif

//#ifndef EXN_MAX_NUM_HANDLERS
//#define EXN_MAX_NUM_HANDLERS (8)
//#endif

typedef struct exn_stack_t {
    struct exn_stack_t* p_next;
    exn_handler_t handler;
} exn_stack_t;

DEFINE_EXCEPTION(RuntimeException,            NULL);
DEFINE_EXCEPTION(NullPointerException,        &RuntimeException);
DEFINE_EXCEPTION(AssertionException,          &RuntimeException);
DEFINE_EXCEPTION(AbortException,              &RuntimeException);
DEFINE_EXCEPTION(ArithmeticException,         &RuntimeException);
DEFINE_EXCEPTION(IllegalInstructionException, &RuntimeException);
DEFINE_EXCEPTION(SegmentationException,       &RuntimeException);

static bool Exn_Handled = true;
static const exn_t* Exn_Current = NULL;
static exn_stack_t* Exn_Handlers = NULL;

static void exn_uncaught(const exn_t* p_exn) {
    (void)p_exn;
    fprintf(stderr, "Error: Uncaught Exception\n");
    exit(1);
}

static void exn_pop(void) {
    exn_stack_t* p_prev = Exn_Handlers;
    Exn_Handlers = p_prev->p_next;
    free(p_prev);
}

void exn_prep(void) {
    exn_stack_t* p_prev = Exn_Handlers;
    Exn_Handlers = (exn_stack_t*)malloc(sizeof(exn_stack_t));
    Exn_Handlers->p_next = p_prev;
    Exn_Handlers->handler.state = EXN_BEGIN;
    Exn_Handled = true;
}

bool exn_process(void) {
    bool ret = true;
    switch(exn_handler()->state) {
        case EXN_BEGIN:
            exn_handler()->state = EXN_TRY;
            break;

        case EXN_TRY:
            exn_handler()->state = (!Exn_Handled) ? EXN_CATCH : EXN_FINALLY;
            break;

        case EXN_CATCH:
            exn_handler()->state = EXN_FINALLY;
            break;

        case EXN_FINALLY:
            if (!Exn_Handled)
                exn_rethrow();
            else
                exn_handler()->state = EXN_DONE;
            break;

        case EXN_DONE:
            exn_pop();
            ret = false;
            break;

        default:
            fprintf(stderr, "Error: Exception handler entered an invalid state\n");
            exit(1);
            break;
    }
    return ret;
}

void exn_throw(const exn_t* p_type) {
    if (Exn_Handlers == NULL) {
        exn_uncaught(Exn_Current);
    } else {
        Exn_Current = p_type;
        Exn_Handled = false;
        longjmp(exn_handler()->context,1);
    }
}

void exn_rethrow(void) {
    exn_pop();
    exn_throw(Exn_Current);
}

bool exn_catch(const exn_t* p_type) {
    const exn_t* p_current;
    for(p_current = exn_current(); p_current != NULL; p_current = p_current->p_parent)
    {
        if (p_current == p_type)
        {
            Exn_Handled = true;
            break;
        }
    }
    return Exn_Handled;
}

const exn_t* exn_current(void) {
    return Exn_Current;
}

exn_handler_t* exn_handler(void) {
    return (NULL != Exn_Handlers) ? &(Exn_Handlers->handler) : NULL;
}

void exn_assert(bool expr) {
    if(!expr) {
        exn_throw(&AssertionException);
    }
}

