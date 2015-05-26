/**
  @file str.h
  @brief An updated string type for C.
*/
#ifndef STR_H
#define STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rt.h"
#include "vec.h"

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

/**
 * @brief Return the size of the string.
 *
 * @param p_str The string.
 *
 * @return The size of the string.
 */
size_t str_size(str_t* p_str);

/**
 * @brief Returns the underlying C-style string.
 *
 * @param p_str The string.
 *
 * @return The underlying C string.
 */
const char* str_cstr(str_t* p_str);

/**
 * @brief Return a new copy of the string.
 *
 * @param p_str The string to copy.
 *
 * @return The new copy of the string.
 */
str_t* str_copy(str_t* p_str);

/**
 * @brief Return a character at a given index in the string.
 *
 * @param p_str The string.
 * @param index The idnex of the character to fetch.
 *
 * @return The fetched character.
 */
char str_at(str_t* p_str, size_t index);

/**
 * @brief Creates a new copy of the string with the character at the provided
 *        index changed to the given value.
 *
 * @param p_str The string to copy.
 * @param index The index of the character to change.
 * @param val The new value for the character.
 *
 * @return The newly created string.
 */
str_t* str_set(str_t* p_str, size_t index, char val);

/**
 * @brief Creates a new string whose contents consist of the first input string
 *        followed by the second input string.
 *
 * @param p_str1 The first input string.
 * @param p_str2 The second input string.
 *
 * @return A newly created string.
 */
str_t* str_concat(str_t* p_str1, str_t* p_str2);

/**
 * @brief Creates a new string with the second string inserted at the given
 *        index of the first string.
 *
 * @param p_str1 The first input string.
 * @param index The index where the string will be inserted.
 * @param p_str2 The second input string.
 *
 * @return The newly created string.
 */
str_t* str_insert(str_t* p_str1, size_t index, str_t* p_str2);

/**
 * @brief Creates a newly created string with the given range erased.
 *
 * The new string is created by copying the input string with the range
 * specified erase. The range erased is from the start index up to, but not
 * including the end index.
 *
 * @param p_str The input string.
 * @param start The start index.
 * @param end The end index.
 *
 * @return The newly created string.
 */
str_t* str_erase(str_t* p_str, size_t start, size_t end);

/**
 * @brief Creates a new string by copying the range specifed from the input
 *        string.
 *
 * The new string is created by copying the specified range from the input
 * string. The range is from the start index up to and not including the end
 * index.
 *
 * @param p_str The input string.
 * @param start The start index.
 * @param end The end index.
 *
 * @return The newly created string.
 */
str_t* str_substr(str_t* p_str, size_t start, size_t end);

/**
 * @brief Compares the two input strings
 *
 * Returns an int representing the comparison with the following semantics:
 *
 *  <0 == The first character that does not match is lower in p_str1 than p_str2.
 *   0 == The strings are identical.
 *  >0 == The first character that does not match is greater in p_str1 than p_str2.
 *
 * @param p_str1 The first input string.
 * @param p_str2 The second input string.
 *
 * @return Integer representing the relationship.
 */
int str_compare(str_t* p_str1, str_t* p_str2);

/**
 * @brief Find the first occurrence of p_str2 in p_str1.
 *
 * @param p_str1 The string to be searched.
 * @param p_str2 The search string.
 *
 * @return The index of the first occurrence if a match is found and SIZE_MAX
 *         if no match is found.
 */
size_t str_find(str_t* p_str1, str_t* p_str2);

/**
 * @brief Find the last occurrence of p_str2 in p_str1.
 *
 * @param p_str1 The string to be searched.
 * @param p_str2 The search string.
 *
 * @return The index of the last occurrence if a match is found and SIZE_MAX
 *         if no match is found.
 */
size_t str_rfind(str_t* p_str1, str_t* p_str2);

/**
 * @brief Joins all of the strings in the given vector together separated by the
 *        join string.
 *
 * @param joinstr The string that will be used to separate the strings.
 * @param strs The vector of strings to be joined.
 *
 * @return The newly joined string.
 */
str_t* str_join(char* joinstr, vec_t* strs);

vec_t* str_split(str_t* str, str_t* splitstr);

#ifdef __cplusplus
}
#endif

#endif /* STR_H */
