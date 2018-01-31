cipher: cipher.o
	gcc cipher.o -o cipher
	make test

cipher.o: cipher.c

test: test1 test2
test1:
	./cipher 1 spoon data.txt data.out
test2:
	./cipher 2 spoon data.out data.bak	