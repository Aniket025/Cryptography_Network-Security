These ECB and CBC encryption files are only written for *.ppm files and won't work for
other formats, the ppm.c and ppm.h files are taken from Princeton University archives

ECB.out, CBC.out are execytable files which take filename as argument and perform
respective encryptions on the image file and store the cipher image in "image_after_ECB.ppm"
and "image_after_CBC.ppm" files respectively

if you want to compile the original c files, then make use of the Makefile provided or
use the commands provided

to use Makefile:
        1. open terminal
        2. go to the directory in which the Makefile is present
        3. type "make" without quotes and press enter

        this will take the make file and compile the c files and produce the executables

if you want to manual compilation, type the following commands(in that order):
        1. gcc -c ppm.c -o ppm.o
        2. ar -rcs libppm.a ppm.o
        3. gcc -c ECB_mode_DES.c
        4. gcc -c CBC_mode_DES.c
        5. gcc ECB_mode_DES.o -L. -lppm
	6. mv a.out ECB.out
        7. gcc CBC_mode_DES.o -L. -lppm
	8. mv a.out CBC.out

to execute the .out files:
        1. open terminal
        2. go to the directory in which the files are present
        3. type "./ECB.out image.ppm" without quotes to execute ECB.out on image.ppm
                --or--
           type "./ECB.out" without quotes to execute ECB.out and it will prompt you
           for a file name 
        4. type "./CBC.out image.ppm" without quotes to execute CBC.out on image.ppm
                --or--
           type "./CBC.out" without quotes to execute CBC.out and it will prompt you
           for a file name
