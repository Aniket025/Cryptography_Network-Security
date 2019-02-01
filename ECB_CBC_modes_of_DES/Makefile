both: ECB.out CBC.out
	
ECB.out: ECB_mode_DES.o libppm.a
	gcc ECB_mode_DES.o -L. -lppm
	mv a.out ECB.out

CBC.out: CBC_mode_DES.o libppm.a
	gcc CBC_mode_DES.o -L. -lppm
	mv a.out CBC.out

ECB_mode_DES.o: ECB_mode_DES.c ppm.o
	gcc -c ECB_mode_DES.c

CBC_mode_DES.o: CBC_mode_DES.c ppm.o
	gcc -c CBC_mode_DES.c

libppm.a: ppm.o
	ar -rcs libppm.a ppm.o

ppm.o: ppm.c ppm.h
	gcc -c ppm.c -o ppm.o

clear:
	rm ECB.out CBC.out ECB_mode_DES.o CBC_mode_DES.o libppm.a ppm.o