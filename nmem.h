#ifndef __NMEM_H
#define __NMEM_H

#include <stdlib.h>

/* Call init_nmallocator before making any memory allocation/free calls
 * node: Input NUMA node. All allocations will be made from memory local to this NUMA node.
 * return value: 0 for success.
 */
int init_nmallocator(int node);

/* Call uninit_nmallocator (pairs with init_nmallocator) when memory allocation from the
 * given node is not required anymore.
 */
void uninit_nmallocator(void);

/* Allocate size_t sized object */
void *nmalloc(size_t);

/* Free the memory associated with the void* ptr */
void nmfree(void *);

/* Reallocate memory with a size size_t and return the ptr to the newly reallocated memory.
 * In case of failure, old ptr is not modified. For success, the passed in ptr and the
 * return ptr points to the same location in memory.
 */
void *nmrealloc(void *ptr, size_t size);

#endif
