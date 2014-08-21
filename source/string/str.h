/**
  @file str.h
  @brief An updated string type for C.
  $Revision$
  $HeadURL$
*/
#ifndef STR_H
#define STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdbool.h>
#include "mem.h"

/* Forward declare our struct */
struct str_t;

/** A safe string data structure */
typedef struct str_t str_t;

/**
 * @brief Create a new string with the contents of the C style string.
 *
 * @param p_cstr The C string to copy.
 *
 * @return Pointer to the newly constructed string.
 */
str_t* str_new(const char* p_cstr);

size_t str_size(str_t* p_str);

const char* str_cstr(str_t* p_str);

str_t* str_copy(str_t* p_str);

char str_at(str_t* p_str, size_t index);

str_t* str_set(str_t* p_str, size_t index, char val);

str_t* str_concat(str_t* p_str1, str_t* p_str2);

str_t* str_insert(str_t* p_str1, size_t index, str_t* p_str2);

str_t* str_erase(str_t* p_str, size_t start, size_t end);

str_t* str_substr(str_t* p_str, size_t start, size_t end);

int str_compare(str_t* p_str1, str_t* p_str2);

size_t str_find(str_t* p_str1, str_t* p_str2);

size_t str_rfind(str_t* p_str1, str_t* p_str2);

#ifdef __cplusplus
}
#endif

#endif /* STR_H */
