cipher: cipher.o polybius.o
	gcc polybius.o cipher.o -o cipher
polybius.o: polybius.c polybius.h
	gcc -c polybius.c
cipher.o: cipher.c 
	gcc -c cipher.c
clean:
	rm *.o cipher *.gchpqueuepmain
test: cipher
	./cipher -e "This is a secret message"
	./cipher -d "44232443 2443 11 431513421544 32154343112215"