load-mem: load-mem-lin.o dynblock.o
	gcc load-mem-lin.o dynblock.o -o load-mem
load-mem-lin.o: load-mem-lin.c
	gcc -c load-mem-lin.c
dynblock.o: dynblock.c dynblock.h
	gcc -c dynblock.c 
clean:
	rm *.o load-mem