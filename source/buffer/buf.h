/**
    @file buf.h
    @brief Implementation of a circular buffer.
    $Revision$
    $HeadURL$
*/
#ifndef BUF_H
#define BUF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdbool.h>

/* Forward declare our structure */
struct buf_t;

/** A structure defining a circular buffer */
typedef struct buf_t buf_t;

/**
 * @brief Creates a new buffer.
 *
 * @param size The fixed size of the new buffer.
 *
 * @return Pointer to the new buffer.
 */
buf_t* buf_new(size_t size);

/**
 * @brief Returns the size of the provided buffer.
 *
 * @param buf The buffer on which to operate.
 *
 * @return The size of the buffer.
 */
size_t buf_size(buf_t* buf);

/**
 * @brief The number of reads from the buffer.
 *
 * @param buf The buffer on which to operate.
 *
 * @return The number of reads.
 */
size_t buf_reads(buf_t* buf);

/**
 * @brief Return the number of writes to the buffer.
 *
 * @param buf The buffer on which to operate.
 *
 * @return The number of writes.
 */
size_t buf_writes(buf_t* buf);

/**
 * @brief Returns whether the buffer is empty.
 *
 * @param buf The buffer on which to operate.
 *
 * @return 1 if the buffer is empty 0 otherwise.
 */
bool buf_empty(buf_t* buf);

/**
 * @brief Returns whether the buffer is full.
 *
 * @param buf The buffer on which to operate.
 *
 * @return 1 if the buffer is full 0 otherwise.
 */
bool buf_full(buf_t* buf);

/**
 * @brief Clears all unread data from the provided buffer.
 *
 * @param buf           The buffer to clear.
 */
void buf_clear(buf_t* buf);

/**
 * @brief Reads an item from the provided buffer.
 *
 * @param buf The buffer to read from.
 *
 * @return Pointer to the data read from the buffer. NULL If no data was read.
 */
void* buf_read(buf_t* buf);

/**
 * @brief Writes data to the provided buffer.
 *
 * @param buf  The buffer to write to.
 * @param data The data to write.
 *
 * @return 1 on successful write 0 otherwise.
 */
bool buf_write(buf_t* buf, void* data);

#ifdef __cplusplus
}
#endif

#endif /* BUF_H */
