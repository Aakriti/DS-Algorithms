#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main()
{
	int * ptr1,* ptr2,a,b;
	float * pt1,* pt2;
	printf("Arguments for mem_init\n(no. of bytes & chunk size):");
	scanf("%d %d",&a,&b);
	mem_init(a,b);
	mem_free(NULL);
	ptr1 = mem_alloc(10*sizeof(int));
	mem_dump();
	pt1 = mem_alloc(10*sizeof(float));
	mem_dump();
	mem_free(ptr1);
	mem_dump();
	ptr1 = mem_alloc(5*sizeof(int));
	mem_dump(); 
	pt2 = mem_alloc(12*sizeof(float));
	mem_dump();
	ptr2 = mem_alloc(5*sizeof(int));
	mem_dump();

/*	*(pt1) = 10.63;
	*(pt2) = 56.78;
	*(pt2 + 1) = *pt1 + *pt2;
	printf("\n%f + %f = %f\n",*(pt1),*(pt2),*(pt2+1));
*/

	mem_free(ptr1);
	mem_dump();
	ptr1 = mem_alloc(50*sizeof(int));
	mem_dump();
	mem_free(ptr1);
	mem_dump();
	mem_free(ptr2);
	mem_dump();
	mem_free(pt1);
	mem_free(pt2);
	mem_exit();

	mem_init(200,64);
}

