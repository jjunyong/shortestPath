sPath:sPath.o
	gcc -o sPath sPath.o
sPath.o: sPath.c
	gcc -c sPath.c
clean:
	rm sPath *.o
