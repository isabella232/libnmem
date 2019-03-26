/*
SPDX-License-Identifier: MIT
MIT License
 
Copyright (c) 2019 Western Digital Corporation or its affiliates.
 
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice (including the next paragraph) shall be included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <nmem.h>

int main(int args, char **env)
{
	int n;
	int cpu = atoi(env[1]);

	printf("Init NUMA memory allocator\n");
	if (init_nmallocator(cpu)) {
		printf("Invalid numa node specified\n");
		return -1;
	}

	printf("Allocate memory from  NUMA memory allocator\n");
        int size = 1024*1024;
        void *mem = nmalloc(size);
        if(mem == NULL){
                printf("could not allocate memory on node %d!\n", cpu);
		return -1;
        } else {
		printf("allocated memory: %p on node %d\n", mem, cpu);
	}

	memset(mem, 0xBD, size);
	mem = nmrealloc(mem, size - 1024);
	printf("realloced memory: %p %x\n", mem, *(unsigned char *)(mem+size - 1025));
	memset(mem+size - 1536, 0xCD, 512);
	mem = nmrealloc(mem, size + 1024);
	printf("realloced memory: %p %x\n", mem, *(unsigned char *)(mem+size - 1535));
	memset(mem+size, 0xDD, 1024);
	printf("memory: %p %x %x %x\n", mem, *(unsigned char *) mem, 
			*(unsigned char *) (mem+size - 1536),
			*(unsigned char *) (mem+size));
	printf("free memory: %p\n", mem);
	nmfree(mem);

	printf("Uninit  NUMA memory allocator\n");
	uninit_nmallocator();

	printf("Try to allocate memory from NUMA allocator now\n");
	mem = nmalloc(size);
	if (mem == NULL) {
	    printf("Success: Can't allocate memory as NUMA memory allocator is not init-ed\n");
	} else {
	    printf("Failure: Can allocate memory even when NUMA memory allocator is not init-ed\n");
	    nmfree(mem);
	}
	printf("Tests completed\n");
        return 0;
}
