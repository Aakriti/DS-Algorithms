#include "fibheaplib.h"

#define FALSE 0
#define TRUE 1
int NegInf = -100;

heap * make_fib_heap()
{
  heap * H = malloc(sizeof(heap));
  H->n = 0;
  H->min = NULL;
  return H;
}

node * make_node(int k)
{
  node * nu = malloc(sizeof(node));
  nu->key = k;
  nu->left = nu;
  nu->right = nu;
  return nu;
}

void fib_heap_insert(heap * H, node * x)
{
  x->degree = 0;
  x->parent = NULL;
  x->child = NULL;
  x->mark = FALSE;

  if(H->min == NULL)
      H->min = x;
  else
  {
      //insert x into H's root list, to the right of H.min
      node * temp;
      temp = H->min->right;

      x->left = H->min;
      x->right = temp;
      temp->left = x;
      H->min->right = x;

      if(x->key < H->min->key)
          H->min = x;
  }
  H->n += 1;
}


node * fib_heap_min(heap * H)
{
  return H->min;
}


heap * fib_heap_union(heap * H1, heap * H2)
{
  if(H1->min == NULL)
      return H2;
  else if(H2->min == NULL)
      return H1;
  else
  {
      heap * H = make_fib_heap();
      node * tmp1,* tmp2;

      if(H1->min->key < H2->min->key)
          H->min = H1->min;
      else
          H->min = H2->min;

      H->n = H1->n + H2->n;

      //concatenate root list of H2 and H1.
      tmp1 = H1->min->right;
      tmp2 = H2->min->left;

      tmp1->left = tmp2;
      tmp2->right = tmp1;

      H1->min->right = H2->min;
      H2->min->left = H1->min;

      return H;
  }
}

void fib_heap_link(heap * H, node * y, node * x)
{
  node * tmp,* tmp2;
  //remove y from root list
  tmp = y->left;
  tmp2 = y->right;

  tmp->right = tmp2;
  tmp2->left = tmp;

  //make y a child of x
  if(x->child == NULL)
  {
      x->child = y;
      y->left = y;
      y->right = y;
  }
  else
  {
      tmp = x->child->right;
      x->child->right = y;
      y->left = x->child;
      y->right = tmp;
      tmp->left = y;
  }

  x->degree += 1;
  y->mark = FALSE;
}

void consolidate(heap * H)
{
  int i,j,d,DHn = H->n;
  node * A[DHn],* tmp,* x,* y,* exch;


  for(i=0;i<DHn;i++)
      A[i] = NULL;

  //tmp = H->min;
  x = H->min;
  j = 0;
  do{
      d = x->degree;

      while (A[d] != NULL && A[d] != x)
      {
          y = A[d];  //Another node with same degree as x
          if(x->key > y->key)
          {
              exch = x;
              x = y;
              y = exch;
          }
          fib_heap_link(H,y,x);
          A[d] = NULL;
          d += 1;
      }
      A[d] = x;
      x = x->right;
      j++;
    }while(j < DHn);

  H->min = NULL;

  for(i=0;i<DHn;i++)
  {
      if(A[i] != NULL)
      {
          A[i]->parent = NULL;
          if(H->min == NULL)
          {
              //Create a root list for H containing just A[i]
              H->min = A[i];
              A[i]->left = A[i];
              A[i]->right = A[i];
          }
          else
          {
              //insert A[i] into H's root list
              exch = H->min->right;
              A[i]->left = H->min;
              A[i]->right = exch;
              exch->left = A[i];
              H->min->right = A[i];

              if(A[i]->key < H->min->key)
                  H->min = A[i];
          }
      }
  }
}

node * fib_extract_min(heap * H)
{
  node * z, * x, * tmp1,* tmp2;
  z = H->min;
        
  if(z != NULL)
  {
      //Add all children of z to root list of H
      x = z->child;
      if(x != NULL) {
          tmp1 = z->right;
          tmp2 = x->left;

          tmp1->left = tmp2;
          tmp2->right = tmp1;

          z->right = x;
          x->left = z;

          //Set all the children's parent to NULL
          tmp2 = x;
          while(tmp2 != tmp1)
          {
              tmp2->parent = NULL;
              tmp2 = tmp2->right;
          }
      }

      //remove z from the root list
      if(z == z->right)
      {
          H->min = NULL;
      }
      else
      {
	  tmp1 = z->left;
	  tmp2 = z->right;

	  tmp1->right = tmp2;
	  tmp2->left = tmp1;

          H->min = tmp2; //not necessarily the new min
          consolidate(H);
      }
      H->n -= 1;
  }
  return z;
}


void cut(heap * H, node * x, node * y)
{
  node * tmp1, * tmp2;
  //remove x from child list of y
  if(y->degree == 1)
  {
      y->child = NULL;
  }
  else
  {
      if(y->child == x)
          y->child = x->right;
      tmp1 = x->left;
      tmp2 = x->right;
      tmp1->right = tmp2;
      tmp2->left = tmp1;
  }
  y->degree -= 1;

  //adding to root list
  tmp1 = H->min;
  tmp2 = H->min->right;

  tmp1->right = x;
  x->left = tmp1;
  tmp2->left = x;
  x->right = tmp2;

  x->parent = NULL;
  x->mark = FALSE;
}

void cascading_cut(heap * H,node * y)
{
  node * z;
  z = y->parent;
  if(z != NULL)
  {
      if(y->mark == FALSE)
          y->mark = TRUE;
      else
      {
          cut(H,y,z);
          cascading_cut(H,z);
      }
  }
}


void fib_decrease_key(heap * H,node * x, int k)
{
  if(k > x->key)
      return; //Error new key should be smaller

  node * y;

  x->key = k;
  y = x->parent;
  if(y != NULL && x->key < y->key)
  {
      cut(H,x,y);
      cascading_cut(H,y);
  }

  if(x->key < H->min->key)
      H->min = x;
}


void fib_heap_delete(heap * H,node * x)
{
  fib_decrease_key(H,x,NegInf);
  x = fib_extract_min(H);
}

