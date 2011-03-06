#include<stdlib.h>
#include<stdio.h>
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "ed/graph.h"
#include "io.h"
#include "mesa.h"

void solver(){
  int instance, i;
  int *side;
  Graph G;

  instance = 1;
  G = inputInstance();
  while(G != NULL){
    /*printf("\nAqui G->V=%d", G->V);*/
    outInstance(instance, processInstance(G));
    instance++;
    GRAPHdestroy(G);
    G = inputInstance();
  }
}

int processInstance(Graph G){
  int *flag, *side, i, j;

  side = malloc((G->V)*sizeof(int));
  flag = malloc((G->V)*sizeof(int));
  for(i = 0; i < G->V; i++){
    side[i] = STANDING;
    flag[i] = 0;
  }

  for(i = 1; i < G->V; i++){
    if(!recursiveCheck(G, i, side, flag)){
      return 0;
    }
    for(j = 1; j < G->V; j++){
      if(!flag[j]){
        i = j;
        j = G->V;
      }
    }
  }

  return 1;

}

int recursiveCheck(Graph G, Vertex actual, int *side, int *flag){
  int i;

  flag[actual] = 1;

  if(side[actual] == STANDING){
    side[actual] = LEFT;
  }

  for(i = 1; i < G->V; i++){
    if(G->adj[actual][i]){
      if(side[i] == side[actual]){
        return 0;
      }else if(side[i] == STANDING){
        side[i] = (side[actual] % 2) + 1;
        return recursiveCheck(G, i, side, flag);
      }
    }
  }

  return 1;
}
