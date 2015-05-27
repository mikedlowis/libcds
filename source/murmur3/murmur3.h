/**
  @file murmur3.h
  @brief Implementation of the murmur3 32-bit hash function.
  */
#ifndef MURMUR3_H
#define MURMUR3_H

#include "rt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculate the murmur3 32-bit hash of a region of memory.
 *
 * @param data Pointer to teh data to hash.
 * @param nbytes The number of bytes of data to hash.
 *
 * @return The 32-bit hash value.
 */
uint32_t murmur3_32(const uint8_t* data, size_t nbytes);

#ifdef __cplusplus
}
#endif

#endif /* MURMUR3_H */
