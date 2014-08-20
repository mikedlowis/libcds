/**
  @file str.c
  @brief See header for details
  $Revision$
  $HeadURL$
*/
#include "str.h"
#include <assert.h>

/* Forward declare our struct */
struct str_t {
    size_t size;
    char data[];
};

str_t* str_new(const char* p_cstr)
{
    str_t* p_str = NULL;
    size_t len   = 0;
    assert(NULL != p_cstr);
    len   = strlen(p_cstr);
    p_str = (str_t*)mem_allocate(sizeof(str_t) + len + 1, NULL);
    p_str->size = len;
    memcpy(p_str->data, p_cstr, len+1);
    return p_str;
}

size_t str_size(str_t* p_str)
{
    assert(NULL != p_str);
    return p_str->size;
}

const char* str_cstr(str_t* p_str)
{
    assert(NULL != p_str);
    return p_str->data;
}

str_t* str_copy(str_t* p_str)
{
    str_t* p_newstr;
    assert(NULL != p_str);
    p_newstr = (str_t*)mem_allocate(sizeof(str_t) + p_str->size + 1, NULL);
    memcpy(p_newstr->data, p_str->data, p_str->size+1);
    p_newstr->size = p_str->size;
    return p_newstr;
}

char str_at(str_t* p_str, size_t index)
{
    assert(NULL != p_str);
    return (index >= p_str->size) ? '\0' : p_str->data[index];
}

str_t* str_set(str_t* p_str, size_t index, char val)
{
    str_t* p_newstr = NULL;
    assert(NULL != p_str);
    if (index < p_str->size)
    {
        p_newstr = str_copy(p_str);
        p_newstr->data[index] = val;
    }
    return p_newstr;
}

str_t* str_concat(str_t* p_str1, str_t* p_str2)
{
    assert(NULL != p_str1);
    assert(NULL != p_str2);
    return str_insert(p_str1, p_str1->size, p_str2);
}

str_t* str_insert(str_t* p_str1, size_t index, str_t* p_str2)
{
    str_t* p_newstr = NULL;
    assert(NULL != p_str1);
    assert(NULL != p_str2);
    if (index <= p_str1->size)
    {
        size_t newsize = sizeof(str_t) + p_str1->size + p_str2->size + 1;
        p_newstr = (str_t*)mem_allocate(newsize, NULL);
        memcpy(&(p_newstr->data[0]), p_str1->data, index);
        memcpy(&(p_newstr->data[index]), p_str2->data, p_str2->size);
        memcpy(&(p_newstr->data[index+p_str2->size]), &(p_str1->data[index]), p_str1->size-index);
        p_newstr->data[p_str1->size + p_str2->size] = '\0';
    }
    return p_newstr;
}

str_t* str_erase(str_t* p_str, size_t start, size_t end)
{
    str_t* p_newstr = NULL;
    size_t newsize  = 0;
    size_t endbytes = 0;
    assert(NULL != p_str);
    assert(start <= end);
    endbytes = (end >= p_str->size) ? 0 : (p_str->size - end);
    newsize = start + endbytes;
    p_newstr = (str_t*)mem_allocate(sizeof(str_t) + newsize + 1, NULL);
    memcpy(&(p_newstr->data[0]),     p_str->data,         start);
    memcpy(&(p_newstr->data[start]), &(p_str->data[end]), endbytes);
    p_newstr->size = newsize;
    p_newstr->data[newsize] = '\0';
    return p_newstr;
}

str_t* str_substr(str_t* p_str, size_t start, size_t end)
{
    str_t* p_newstr = NULL;
    assert(NULL != p_str);
    assert(start <= end);
    p_newstr = (str_t*)mem_allocate(sizeof(str_t) + (end - start) + 1, NULL);
    p_newstr->size = (end-start);
    memcpy(p_newstr->data, &(p_str->data[start]), end - start);
    p_newstr->data[p_newstr->size] = '\0';
    return p_newstr;
}

int str_compare(str_t* p_str1, str_t* p_str2)
{
    return strcmp(p_str1->data, p_str2->data);
}

size_t str_find(str_t* p_str1, str_t* p_str2)
{
    (void)p_str1;
    (void)p_str2;
    return 0;
}

size_t str_rfind(str_t* p_str1, str_t* p_str2)
{
    (void)p_str1;
    (void)p_str2;
    return 0;
}

