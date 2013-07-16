#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int * A;
int n,i,j,temp;

void generate()
{
	i = 0;
	while(i<n)
	{
        	*(A+i) = rand()%100;
		i++;
	}
}

void display()
{
        for(i=0;i<n;i++)
                printf("%d ",*(A+i));
}

void insertion_sort()
{
	for(i=0;i<n-1;i++)
	{
		j = i;
		temp = *(A+j+1);
		while(temp<A[j] && j>=0)
		{
			*(A+j+1) = *(A+j);
			j--;
		}
		*(A+j+1) = temp;
	}
}

void bubble_sort()
{
	for(i=0;i<n;i++)
	{
		j = 0;
		while(j<n-i-1)
		{
			if( *(A+j) > *(A+j+1) )
			{
				temp = *(A+j);
				*(A+j) = *(A+j+1);
				*(A+j+1) = temp;
			}
			j++;
		}
	}
}



void merge(int a, int m, int b)
{
	int * B;
        B = malloc((b-a+1)*sizeof(int));
        int k=a,j=m+1;
        i=0;
        while(k<=m && j<=b)
        {
                if(*(A+k)<*(A+j))
                {
                        *(B+i) = *(A+k);
                        i++;
                        k++;
                }
                else
                {
                        *(B+i) = *(A+j);
                        i++;
                        j++;
                }
        }


        while(j<=b)
        {
                *(B+i) = *(A+j);
                j++;
                i++;
        }

        while(k<=m)
        {
                *(B+i) = *(A+k);
                i++;
                k++;
        }
        for(i=0; i<(b-a+1); i++)
                *(A+a+i) = *(B+i);
}



void merge_sort(int a,int b)
{
        if(a<b)
        {
                merge_sort(a,(a+b)/2);
                merge_sort((a+b)/2+1,b);
                merge(a,(a+b)/2,b);
        }
}

void quick_sort(int first, int last)
{
    int pivot;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(*(A+i) <= *(A+pivot) && i<last)
                 i++;
             while(*(A+j) > *(A+pivot))
                 j--;
             if(i<j){
                 temp = *(A+i);
                 *(A+i) = *(A+j);
                 *(A+j) = temp;
             }
         }

         temp = *(A+pivot);
         *(A+pivot) = *(A+j);
         *(A+j) = temp;
         quick_sort(first,j-1);
         quick_sort(j+1,last);
    }
}

int main(int argc, char * argv[])
{
	i=0;
	n=atoi(argv[1]);
        srand(time(NULL));
        A = malloc(n*sizeof(int));
	double time;
        struct timeval t1,t2;

        generate();
	
	printf("List before sorting:\n");
	display();
/*
	//Insertion Sort
	gettimeofday(&t1,NULL);
	insertion_sort();
        gettimeofday(&t2,NULL);
        time = t2.tv_sec + (t2.tv_usec/1000000.0) - t1.tv_sec - (t1.tv_usec/1000000.0);
        printf("\nTime taken by insertion sort:%lfs\n",time);

	//Bubble Sort
	gettimeofday(&t1,NULL);
	bubble_sort();
        gettimeofday(&t2,NULL);
        time = t2.tv_sec + (t2.tv_usec/1000000.0) - t1.tv_sec - (t1.tv_usec/1000000.0);
        printf("\nTime taken by bubble sort:%lfs\n",time);

	//Merge Sort
	gettimeofday(&t1,NULL);
	merge_sort(0,n-1);
        gettimeofday(&t2,NULL);
        time = t2.tv_sec + (t2.tv_usec/1000000.0) - t1.tv_sec - (t1.tv_usec/1000000.0);
        printf("\nTime taken by merge sort:%lfs\n",time);
*/
	//Quick Sort
	gettimeofday(&t1,NULL);
	quick_sort(0,n-1);
        gettimeofday(&t2,NULL);
        time = t2.tv_sec + (t2.tv_usec/1000000.0) - t1.tv_sec - (t1.tv_usec/1000000.0);
        printf("\nTime taken by quick sort:%lfs\n",time);

	printf("\nList after sorting:\n");
	display();
	printf("\n");
}
