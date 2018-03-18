p1: operations.h main.o operations.o
	gcc main.o operations.o -Wall -o p2

main.o: operations.h main.c
	gcc -c main.c

operations.o: operations.h operations.c
	gcc -c operations.c

clean:
	rm -f p2 *.o data.bak data.out