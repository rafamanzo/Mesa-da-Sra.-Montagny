/**********************************/
/* MAC0328 - Algoritmos em grafos */
/*                                */
/* rafamz                         */
/* macacada                       */
/* Rafael Reggiani Manzo          */
/* 6797150                        */
/**********************************/

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "digraph.h"

int *lbl;

void lblInit(){
  int i;

  lbl = malloc(MAXVERTEX*sizeof(int));

  for(i = 0; i < MAXVERTEX; i++){
    lbl[i] = -1;
  }  
}

Digraph DIGRAPHinit(int vertexCount){
  Digraph G;

  G = malloc(sizeof(struct digraph));
  G->V = vertexCount;
  G->A = 0;
  G->adj = MATRIXint(vertexCount, vertexCount, 0);

  return G;
}

void DIGRAPHdestroy(Digraph G){
  int i;

  for(i = 0; i < G->V; i++){
    free(G->adj[i]);
  }

  free(G->adj);
  free(G);
}

int ** MATRIXint(int r, int c, int val){
  int **m;
  int i, j;

  m = malloc(r*sizeof(int *));

  for(i = 0; i < r; i++){
    m[i] = malloc(c*sizeof(int));
    for(j = 0; j < c; j++){
      m[i][j] = val;
    }
  }
  
  return m; 
}

void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w){
  if(G->adj[v][w] == 0 && v != w){
    G->adj[v][w] = 1;
    G->A++;
  }
}

void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w){
  if(G->adj[v][w] == 1 && v != w){
    G->adj[v][w] = 0;
    G->A--;
  }
}

void DIGRAPHshow(Digraph G){
  int i,j;

  for(i = 0; i < G->V; i++){
    printf("\n%d:",i);
    for(j = 0; j < G->V; j++){
      if(G->adj[i][j] == 1){
        printf(" %d", j);
      }
    }
  }
}

int DIGRAPHpath(Digraph G, Vertex s, Vertex t){
  int i;

  for(i = 0; i < G->V; i++){
    lbl[i] = -1;
  }

  pathR(G,s);

  if(lbl[t] == -1){
    return 0;
  }else{
    return 1;
  }
}

void pathR(Digraph G, Vertex v){
  int i;

  lbl[v] = 1;
  
  for(i = 0; i < G->V; i++){
    if(G->adj[v][i] == 1 && lbl[i] == -1){
      pathR(G, i);
    }
  }
} 
