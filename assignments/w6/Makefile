main: main.c
	gcc main.c -o main

cipher.o: cipher.c polybius.h
	gcc -c cipher.c

polybius.o: polybius.c polybius.h
	gcc -c polybius.c

queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm *.o main
