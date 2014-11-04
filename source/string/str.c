/**
  @file str.c
  @brief See header for details
*/
#include "str.h"

/* Forward declare our struct */
struct str_t
{
    size_t size;
    char data[];
};

static str_t* str_allocate(size_t len)
{
    size_t block_size = sizeof(str_t) + (sizeof(char) * (len + 1));
    str_t* p_str = (str_t*)mem_allocate(block_size, NULL);
    p_str->size = len;
    p_str->data[p_str->size] = '\0';
    return p_str;
}

str_t* str_new(const char* p_cstr)
{
    str_t* p_str = NULL;
    assert(NULL != p_cstr);
    p_str = str_allocate(strlen(p_cstr));
    memcpy(p_str->data, p_cstr, p_str->size+1);
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
    assert(NULL != p_str);
    return str_substr(p_str, 0, p_str->size);
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
        p_newstr = str_allocate(p_str1->size + p_str2->size);
        memcpy(&(p_newstr->data[0]), p_str1->data, index);
        memcpy(&(p_newstr->data[index]), p_str2->data, p_str2->size);
        memcpy(&(p_newstr->data[index+p_str2->size]), &(p_str1->data[index]), p_str1->size-index);
    }
    return p_newstr;
}

str_t* str_erase(str_t* p_str, size_t start, size_t end)
{
    str_t* p_newstr = NULL;
    size_t endbytes = 0;
    assert(NULL != p_str);
    assert(start <= end);
    endbytes = (end >= p_str->size) ? 0 : (p_str->size - end);
    p_newstr = str_allocate(start + endbytes);
    memcpy(&(p_newstr->data[0]),     p_str->data,         start);
    memcpy(&(p_newstr->data[start]), &(p_str->data[end]), endbytes);
    return p_newstr;
}

str_t* str_substr(str_t* p_str, size_t start, size_t end)
{
    str_t* p_newstr = NULL;
    assert(NULL != p_str);
    assert(start <= end);
    p_newstr = str_allocate(end - start);
    memcpy(p_newstr->data, &(p_str->data[start]), end - start);
    return p_newstr;
}

int str_compare(str_t* p_str1, str_t* p_str2)
{
    assert(NULL != p_str1);
    assert(NULL != p_str2);
    return strcmp(p_str1->data, p_str2->data);
}

size_t str_find(str_t* p_str1, str_t* p_str2)
{
    size_t idx = SIZE_MAX;
    assert(NULL != p_str1);
    assert(NULL != p_str2);
    for(size_t i = 0; i < p_str1->size; i++) {
        if(0 == strncmp(&(p_str1->data[i]), p_str2->data, p_str2->size))
        {
            idx = i;
            break;
        }
    }
    return idx;
}

size_t str_rfind(str_t* p_str1, str_t* p_str2)
{
    size_t idx = SIZE_MAX;
    assert(NULL != p_str1);
    assert(NULL != p_str2);
    for(size_t i = p_str1->size; i > 0; i--) {
        if(0 == strncmp(&(p_str1->data[i-1]), p_str2->data, p_str2->size))
        {
            idx = i-1;
            break;
        }
    }
    return idx;
}

str_t* str_join(char* joinstr, vec_t* strs) {
    str_t* ret = str_new("");
    str_t* jstr = str_new(joinstr);
    for (size_t idx = 0; idx < vec_size(strs); idx++) {
        str_t* str = (str_t*)vec_at(strs, idx);
        if (str_size(ret) > 0)
            mem_swap((void**)&ret, str_concat(ret, jstr));
        mem_swap((void**)&ret, str_concat(ret, str));
    }
    mem_release(jstr);
    return ret;
}

vec_t* str_split(str_t* str, str_t* splitstr) {
    vec_t* vec = vec_new(0);
    size_t index = str_find(str, splitstr);
    if (index != SIZE_MAX) {
        str_t* therest = str_substr(str, index + str_size(splitstr), str_size(str));
        vec_push_back( vec, str_substr(str, 0, index) );
        if (SIZE_MAX != str_find(str, splitstr)) {
            vec_t* nextsplit = str_split(therest, splitstr);
            for (size_t idx = 0; idx < vec_size(nextsplit); idx++) {
                vec_push_back( vec, mem_retain( vec_at(nextsplit, idx) ) );
            }
            mem_release(nextsplit);
        } else {
            vec_push_back( vec, therest );
        }
    }
    return vec;
}

