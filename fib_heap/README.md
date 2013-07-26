Fibonacci Heaps

Supported operations:

-	make_fib_heap()        -- creates and returns empty heap
-	fib_heap_insert(H,x)   -- inserts element x into heap H
-	fib_heap_min(H)        -- returns pointer to min element
-	fib_extract_min(H)     -- deletes min element from heap, returns pointer to it
-	fib_heap_union(H1,H2)  -- creates and returns a new heap H from H1 and H2
-	fib_decrease_key(H,x,k)-- assigns new value k to x, which is smaller than its previous value
-	fib_heap_delete(H,x)   -- deletes element x from heap H

-	make_node()            -- creates and returns a new node
-	fib_heap_link(H,y,x)   -- remove y from root list and make y a child of x
-	consolidate(H)         --
-	cut(H,x,y)             --
-	cascading_cut(H,y)     -- 

Reference: Cormen et al.
