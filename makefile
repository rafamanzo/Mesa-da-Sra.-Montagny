#argumentos de compilacao
CFLAGS = -ansi -pedantic -Wall -g

Mesa: main.c
	gcc main.c -o Mesa $(CFLAGS)

clean:
	rm Mesa
