#include <stdio.h>
#include <stdlib.h>

#ifndef _MYLIB_H_
#define _MYLIB_H_

/* Function mem_init.
Gets memory heap from the system and initializes it to zero [using calloc instead of malloc]. 
This memory in turn will be used for all mem_alloc() functions in multiples of chunks.
Chunk size can be 16,32,64,128. Throws an error and exits if chunk size is anything else.
This function is only called once. If it's called again before calling mem_exit, throws an error and exits.

Could be modified to call it more than once and just add to the original chunk as a pointer.
But that would require chunk size to be same. Not implemented as of now.
*/
void mem_init(int no_of_bytes,int chunk_size);


/*Function mem_alloc.
Allocate number of chunks from the available memory pool such that allocated memory is >= no_of_bytes.
Returns pointer to the starting address if it can find the requuired no of chunks else returns NULL.
No particular care is taken as to which of the available blocks should be allocated to reduce fragmentation. 
*/
void * mem_alloc(int no_of_bytes);

/*Function mem_free.
Frees up the chunks (a block) of allocated memory and makes it available for the future use.
If all the blocks are freed, it merges them into a single block to remove fragmentation.
Other than this, no merging of the blocks takes place.
*/
void mem_free(void *ptr);

/*Function mem_dump.
Outputs snapshot of memory usauge. 
Prints for each block: size in chunks and status (allocated/free)
Prints block in random order. Allocated ones first, then free ones.
*/
void mem_dump();

/* Function mem_exit.
Returns error if used_list is not NULL. Otherwise de-allocates the heap.
*/
void mem_exit();

/*Structure to represent a block of chunks in the memory.*/
struct block_node {
	int node;
	struct block_node *nxt_node;
	int no_chunks;
	//char data[0];
	
}; 

#endif
