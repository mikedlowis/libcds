/**
  @file buf.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include <stdlib.h>
#include "buf.h"

buf_t* buf_new(size_t size)
{
    buf_t* buf = NULL;
    if (size > 0)
    {
        buf         = (buf_t*) malloc( sizeof(buf_t) );
        buf->buffer = (void**) malloc( sizeof(void*) * size );
        buf->size   = size;
        buf->reads  = 0;
        buf->writes = 0;
    }
    return buf;
}

void buf_free(buf_t* buf, bool free_contents)
{
    buf_clear(buf,free_contents);
    free( buf->buffer );
    free( buf );
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

void buf_clear(buf_t* buf, bool free_contents)
{
    if (free_contents)
    {
        while ( !buf_empty(buf) )
        {
            free( buf_read(buf) );
        }
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

