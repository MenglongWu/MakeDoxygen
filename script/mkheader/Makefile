

all: main.o
	gcc -g main.o -o mkheader

main.o:main.c
	gcc -c main.c -std=gnu99
clean:
	@-rm -f *.o
	@-rm -f mkheader