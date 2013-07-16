#include "mylib.h"

int CHUNK_SIZE = 0,CHUNK_TOTAL = 0,NUM_BLOCKS = 0,INIT_ONCE = 0;
struct block_node *used_list = NULL,*free_list = NULL,*i_ptr = NULL,*j_ptr=NULL,*k_ptr=NULL,*base = NULL;

void mem_init(int no_of_bytes,int chunk_size)
{
	if(INIT_ONCE != 0)
	{
		printf("Operation failed! You will have to free the memory already in use and start over.\n");
		//return;
		exit(0);
	}
	else
	{
		INIT_ONCE = 1;
	}

	int overhead_bytes; //some estimate based on no_of_bytes and chunk_size. Taking worst case.
	overhead_bytes = sizeof(struct block_node)*(no_of_bytes/chunk_size);

	printf("\n---mem_init---\n");	
	if(chunk_size == 16 || chunk_size == 32 || chunk_size == 64 || chunk_size == 128)
	{
		free_list = calloc(no_of_bytes + overhead_bytes/2,1);
		base = free_list;
		CHUNK_SIZE = chunk_size;
	}
	else
	{
		printf("\nError: Invalid Chunk size! (16,32,64 or 128 only).\n");
		exit(0);
	}

	NUM_BLOCKS++;
	free_list->no_chunks = (no_of_bytes)/CHUNK_SIZE;
	CHUNK_TOTAL = (no_of_bytes)/CHUNK_SIZE;
	free_list->nxt_node = NULL;
	free_list->node = NUM_BLOCKS;
}

void * mem_alloc(int no_of_bytes)
{
	printf("\n---mem_alloc---\n");
	int req_chunks = 0,xtra = sizeof(struct block_node);
	if(no_of_bytes % CHUNK_SIZE == 0)
	{
		req_chunks = no_of_bytes/CHUNK_SIZE;
	}
	else
	{
		req_chunks = 1 + no_of_bytes/CHUNK_SIZE;
	}

	//Allocate req_chunks from free_list to used_list.
	i_ptr = free_list;
	k_ptr = NULL;
	while(i_ptr != NULL)
	{
		if(i_ptr->no_chunks > req_chunks)
		{
			//update free_list and used_list.
			NUM_BLOCKS++;
			j_ptr = (struct block_node *)((char *)i_ptr + xtra + req_chunks*CHUNK_SIZE);
			j_ptr->nxt_node = i_ptr->nxt_node;
			j_ptr->no_chunks = i_ptr->no_chunks - req_chunks;
			j_ptr->node = i_ptr->node;
			if(k_ptr != NULL)
				k_ptr->nxt_node = j_ptr;
			else
				free_list = j_ptr;

			j_ptr = used_list;
			if(j_ptr == NULL) 
			{
				used_list = i_ptr;
				used_list->no_chunks = req_chunks;
				used_list->nxt_node = NULL;
				used_list->node = NUM_BLOCKS;
			}
			else
			{
				while(j_ptr->nxt_node!=NULL)
					j_ptr = j_ptr->nxt_node;
	
				j_ptr->nxt_node = i_ptr;
				j_ptr->nxt_node->no_chunks = req_chunks;
				j_ptr->nxt_node->nxt_node = NULL;
				j_ptr->nxt_node->node = NUM_BLOCKS;
			}
			printf("Allocating %d blocks..\n",req_chunks);
			return (char *)i_ptr+xtra ;
		}
		else
		{
			k_ptr = i_ptr;
			i_ptr = i_ptr->nxt_node;
		}
	}
	if(i_ptr == NULL)
	{
		printf("Can't allocate! No Space!\n");
		return NULL;
		//exit(0);
	}
}

void mem_free(void *ptr)
{
	int count,xtra = sizeof(struct block_node);
	printf("\n---mem_free---\n");
	
	if(ptr == NULL)
		return;

	i_ptr = ptr;
	i_ptr = (struct block_node *)((char *)i_ptr - xtra);

	//Remove from used list.
	k_ptr = used_list;
	if(k_ptr == i_ptr)
		used_list = used_list->nxt_node;
	else
	{
		while(k_ptr != i_ptr)
		{
			j_ptr=k_ptr;
			k_ptr=k_ptr->nxt_node;
		}
		j_ptr->nxt_node = i_ptr->nxt_node;
	}

	//Add to free list.
	j_ptr = free_list;
	if(j_ptr == NULL)
		free_list = i_ptr;
	else
	{
		while(j_ptr->nxt_node!=NULL)
			j_ptr=j_ptr->nxt_node;

		j_ptr->nxt_node = i_ptr;
	}
	i_ptr->nxt_node=NULL;
	

	//If all the blocks are freed, join them up into a single block to remove fragmentation.
	count = 0;
	i_ptr = free_list;
	while(i_ptr != NULL)
	{
		count += i_ptr->no_chunks;
		i_ptr = i_ptr->nxt_node;		
	}
	if(count == CHUNK_TOTAL)
	{
		NUM_BLOCKS = 1;
		used_list = NULL;
		free_list = base;
		base->node=NUM_BLOCKS;
		base->nxt_node=NULL;
		base->no_chunks=CHUNK_TOTAL;
	}
}

void mem_dump()
{
	printf("\n---mem_dump---\n");
	//Display each block with no of chunks along with free/used info.
	int free=0,used=0;
	
	i_ptr = used_list;
	while(i_ptr != NULL)
	{
		printf("Block: \t Chunks contained:%3d \t Status: In Use\n",i_ptr->no_chunks);
		used += i_ptr->no_chunks;
		i_ptr = i_ptr->nxt_node;		
	}
	
	i_ptr = free_list;
	while(i_ptr != NULL)
	{
		printf("Block: \t Chunks contained:%3d \t Status: Free\n",i_ptr->no_chunks);
		free += i_ptr->no_chunks;
		i_ptr = i_ptr->nxt_node;
	}
	printf("Total free chunks:%3d\nTotal used chunks:%3d\n\n",free,used);
}

void mem_exit()
{
	printf("\n---mem_exit successful---\n\n");
	INIT_ONCE = 0;
	if(used_list == NULL)
	{
		if(base != NULL)
			free(base);
	}
	else
	{
		printf("\nError: Used_list not null.\n");
		exit(0);
	}
}
