#argumentos de compilacao
CFLAGS = -ansi -pedantic -Wall

Mesa: main.c
	gcc main.c -o Mesa $(CFLAGS)

clean:
	rm Mesa
