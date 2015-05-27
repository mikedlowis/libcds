/**
  @file murmur3.c
  @brief See header for details
*/
#include "murmur3.h"

/**
 * Get 32-bit Murmur3 hash.
 *
 * @param data      source data
 * @param nbytes    size of data
 *
 * @return 32-bit unsigned hash value.
 *
 * @code
 *  uint32_t hashval = murmur3_32((void*)"hello", 5);
 * @endcode
 *
 * @code
 *  MurmurHash3 was created by Austin Appleby  in 2008. The initial
 *  implementation was published in C++ and placed in the public.
 *    https://sites.google.com/site/murmurhash/
 *  Seungyoung Kim has ported its implementation into C language
 *  in 2012 and published it as a part of qLibc component.
 * @endcode
 */
uint32_t murmur3_32(const uint8_t* data, size_t nbytes)
{
    /* Initial hash value */
    uint32_t hash = 0;
    /* Magic numbers for the hash calculation */
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    /* Prepare to process the byte array as an array of uint32_ts */
    const int nblocks = nbytes / sizeof(uint32_t);
    const uint32_t* blocks = (const uint32_t *) (data);
    const uint8_t* tail = (const uint8_t *) (data + (nblocks * 4));
    /* Start processing the  data if we have it */
    if (data != NULL || nbytes != 0) {
        uint32_t blk;
        /* Process all of the full uint32_ts in the data */
        for (int i = 0; i < nblocks; i++) {
            blk = blocks[i];
            blk = blk * c1;
            blk = (blk << 15) | (blk >> (32 - 15));
            blk = blk * c2;
            /* Update the hash calculation */
            hash = hash ^ blk;
            hash = (hash << 13) | (hash >> (32 - 13));
            hash = (hash * 5) + 0xe6546b64;
        }

        /* Process the tail of the data */
        blk = 0;
        switch (nbytes & 3) {
            case 3:
                blk ^= tail[2] << 16;
            case 2:
                blk ^= tail[1] << 8;
            case 1:
                blk ^= tail[0];
                blk *= c1;
                blk = (blk << 15) | (blk >> (32 - 15));
                blk *= c2;
                hash ^= blk;
        };

        /* Post process the hash */
        hash = hash ^ nbytes;
        hash = hash ^ (hash >> 16);
        hash = hash * (0x85ebca6b);
        hash = hash ^ (hash >> 13);
        hash = hash * (0xc2b2ae35);
        hash = hash ^ (hash >> 16);
    }
    return hash;
}

