genRand: genRand-lin.o
	gcc genRand-lin.o -o genRand

genRand-lin.o: genRand-lin.c 
	gcc -c genRand-lin.c

clean:
	rm *.o genRand

test: genRand
	./genRand 10 output.txt
	./genRand 10 output.txt -a
	./genRand 10 
