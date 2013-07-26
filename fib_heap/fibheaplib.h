#include<stdio.h>
#include<stdlib.h>

#ifndef _FIBHEAPLIB_H_
#define _FIBHEAPLIB_H_


struct node
{
  int key;
  int degree;
  int mark;
  struct node * parent;
  struct node * left;
  struct node * right;
  struct node * child;
};
typedef struct node node;

typedef struct
{
  int n;
  node * min;
}heap;


// creates and returns empty heap
heap * make_fib_heap();

// creates and returns a new node
node * make_node(int k);

// inserts element x into heap H
void fib_heap_insert(heap * H, node * x);

// returns pointer to min element
node * fib_heap_min(heap * H);

// creates and returns a new heap H from H1 and H2
heap * fib_heap_union(heap * H1, heap * H2);

// remove y from root list and make y a child of x
void fib_heap_link(heap * H, node * y, node * x);

//
void consolidate(heap * H);

// deletes min element from heap, returns pointer to it
node * fib_extract_min(heap * H);

//
void cut(heap * H, node * x, node * y);

//
void cascading_cut(heap * H,node * y);

// assigns new value to x to k, which is smaller than its previous value
void fib_decrease_key(heap * H,node * x, int k);

// deletes element x from heap H
void fib_heap_delete(heap * H,node * x);


#endif
