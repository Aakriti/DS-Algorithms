all: mylib.o

mylib.o: mylib.h mylib.c
	gcc -o mylib.o -c mylib.c
	ar rvs libmylib.a mylib.o
	gcc example.c -o example libmylib.a

clean:
	rm mylib.o libmylib.a example
