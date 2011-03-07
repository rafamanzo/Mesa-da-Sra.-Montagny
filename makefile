####################################
## MAC0328 - Algoritmos em grafos ##
##                                ##
## rafamz                         ##
## macacada                       ##
## Rafael Reggiani Manzo          ##
## 6797150                        ##
####################################

#argumentos de compilacao
CFLAGS = -ansi -pedantic -Wall

#headers
ED = ed/arc.h ed/digraph.h ed/graph.h ed/vertex.h

Mesa: graph.o main.o io.o mesa.o
	gcc arc.o digraph.o graph.o main.o io.o mesa.o -o Mesa

main.o: main.c
	gcc -c main.c $(CFLAGS)

arc.o: ed/vertex.h ed/arc.h ed/arc.c
	gcc -c ed/arc.c $(CFLAGS)

digraph.o: ed/vertex.h arc.o ed/digraph.h ed/digraph.c
	gcc -c ed/digraph.c $(CFLAGS)

graph.o: ed/vertex.h digraph.o ed/graph.h ed/graph.c 
	gcc -c ed/graph.c $(CFLAGS)

io.o: ed/vertex.h ed/digraph.h graph.o io.h io.c
	gcc -c io.c $(CFLAGS)

mesa.o: ed/vertex.h ed/digraph.h ed/graph.h io.o mesa.h mesa.c
	gcc -c mesa.c $(CFLAGS)

clean:
	rm *.o
	rm Mesa
