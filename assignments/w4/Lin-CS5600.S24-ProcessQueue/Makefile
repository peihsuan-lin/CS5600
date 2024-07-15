qtest: queue.o queuetest.o
	gcc queuetest.o queue.o -o qtest
queue.o: queue.c
	gcc -c queue.c
queuetest.o: queuetest.c
	gcc -c queuetest.c 
clean:
	rm *.o qtest