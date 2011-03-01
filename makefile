#argumentos de compilacao
CFLAGS = -ansi -pedantic -Wall -g

#headers
ED = ed/arc.h ed/digraph.h ed/graph.h ed/vertex.h

Mesa: graph.o main.o io.o
	gcc arc.o digraph.o graph.o main.o io.o -o Mesa $(CFLAGS)

main.o:
	gcc -c main.c

arc.o: ed/vertex.h ed/arc.h ed/arc.c
	gcc -c ed/arc.c

digraph.o: ed/vertex.h arc.o ed/digraph.h ed/digraph.c
	gcc -c ed/digraph.c

graph.o: ed/vertex.h digraph.o ed/graph.h ed/graph.c 
	gcc -c ed/graph.c

io.o: ed/vertex.h ed/digraph.h graph.o io.h io.c
	gcc -c io.c

clean:
	rm *.o
	rm Mesa
