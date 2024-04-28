output: LinP.CS5600.LearnC.o mpg2km.o
	gcc LinP.CS5600.LearnC.o mpg2km.o -o output
LinP.CS5600.LearnC.o: LinP.CS5600.LearnC.c
	gcc -c LinP.CS5600.LearnC.c
mpg2km.o: mpg2km.c mpg2km.h
	gcc -c mpg2km.c 
clean:
	rm *.o output