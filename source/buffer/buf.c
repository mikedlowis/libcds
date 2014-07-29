/**
  @file buf.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include <stdlib.h>
#include "buf.h"
#include "mem.h"

static void buf_free(void* p_buf);

buf_t* buf_new(size_t size)
{
    buf_t* buf = NULL;
    if (size > 0)
    {
        buf         = (buf_t*) mem_allocate(sizeof(buf_t), &buf_free);
        buf->buffer = (void**) malloc( sizeof(void*) * size );
        buf->size   = size;
        buf->reads  = 0;
        buf->writes = 0;
    }
    return buf;
}

size_t buf_size(buf_t* buf)
{
    return (size_t)buf->size;
}

bool buf_empty(buf_t* buf)
{
    return (buf->reads == buf->writes);
}

bool buf_full(buf_t* buf)
{
    int full = !buf_empty(buf);
    full &= ((buf->reads % buf->size) == (buf->writes % buf->size));
    return full;
}

void buf_clear(buf_t* buf)
{
    void* entry;
    while ( !buf_empty(buf) )
    {
        entry = buf_read(buf);
        if (NULL != entry)
            mem_release( entry );
    }
    buf->reads  = 0;
    buf->writes = 0;
}

void* buf_read(buf_t* buf)
{
    void* data = NULL;
    if (!buf_empty(buf))
    {
        data = buf->buffer[ buf->reads % buf->size ];
        buf->reads++;
    }
    return data;
}

bool buf_write(buf_t* buf, void* data)
{
    bool success = false;
    if (!buf_full(buf))
    {
        buf->buffer[ buf->writes % buf->size ] = data;
        buf->writes++;
        success = true;
    }
    return success;
}

static void buf_free(void* p_buf)
{
    buf_clear((buf_t*)p_buf);
    free( ((buf_t*)p_buf)->buffer );
}

