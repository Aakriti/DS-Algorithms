Code is contained in mylib.h and mylib.c

Run make to create mylib.o and libmylib.a, the object file and library file respectively.

example.c is an example file containing the main function which uses this library.
It can be compiled by:

gcc example.c -o example libmylib.a

OR

gcc example.c -o example mylib.o

This will link it to my library.

./example will execute the code. 


------------------------------------------------------------------------------------------------------------------------------------

Library for memory management. The library provides following function calls that can be linked from the source code written in 'C'.

mem_init(no_of_bytes,chunk_size)
gets memory heap from the system and initializes it. This memory in turn will be used for all mem_alloc() functions in 
multiples of chunks. Chunk size can be 16,32,64,128 

void *ptr mem_alloc(int no_of_bytes)
Allocate number of chunks from the available memory pool such that allocated memory is <= no_of_bytes

mem_free(void *ptr)
Frees up the chunks (a block) of allocated memory and makes it available for the future use

mem_dump()
output snapshot of memory usauge. Prints for each block: size in chunks and status (allocated/free)

mem_exit()
returns error if used_list is not NULL, otherwise de-allocates the heap.

The program maintains two lists i) used_list and ii) Free_list.

Each block node is represented by following structure.
struct block_node { 
int node ;
struct block_node *nxt_node ;
//etc.
}

Mem_init() function initializes used_list and free_list.
