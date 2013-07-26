all: fibheaplib.o

fibheaplib.o: fibheaplib.h fibheaplib.c
	gcc -o fibheaplib.o -c fibheaplib.c
	ar rvs libfibheaplib.a fibheaplib.o

test:
	gcc test.c -o test libfibheaplib.a

clean:
	rm libfibheaplib.a fibheaplib.o
