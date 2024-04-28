arger-lin: LinP.CS5600.CmdArgsC.c checkArgs.o letterConvert.o
	gcc LinP.CS5600.CmdArgsC.c checkArgs.o letterConvert.o -o arger-lin
checkArgs.o: checkArgs.c checkArgs.h
	gcc -c checkArgs.c 
letterConvert.o: letterConvert.c letterConvert.h
	gcc -c letterConvert.c
clean:
	rm *.o arger-lin