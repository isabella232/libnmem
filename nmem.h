/*
SPDX-License-Identifier: MIT
MIT License
 
Copyright (c) 2019 Western Digital Corporation or its affiliates.
 
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice (including the next paragraph) shall be included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
