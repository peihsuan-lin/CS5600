main: main.c cache.o message.o database.o
	gcc -g main.c message.o cache.o database.o -o main -lsqlite3

message.o: message.c message.h
	gcc -Wall -g -c message.c

cache.o: cache.c cache.h
	gcc -Wall -g -c cache.c

database.o: database.c database.h
	gcc -Wall -g -c database.c

clean:
	rm -f *.o main