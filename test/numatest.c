#include <stdio.h>
#include <string.h>
#include <nmem.h>

int main(int args, char **env)
{
	int n;
	int cpu = atoi(env[1]);
	if (init_nmallocator(cpu)) {
		printf("Invalid numa node specified\n");
		return -1;
	}
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

        return 0;
}
