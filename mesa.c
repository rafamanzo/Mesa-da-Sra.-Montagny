/**********************************/
/* MAC0328 - Algoritmos em grafos */
/*                                */
/* rafamz                         */
/* macacada                       */
/* Rafael Reggiani Manzo          */
/* 6797150                        */
/**********************************/

#include<stdlib.h>
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "ed/graph.h"
#include "io.h"
#include "mesa.h"

void solver(){
  int instance;
  Graph G;

  instance = 1;
  G = inputInstance();
  while(G != NULL){
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
  }

  for(i = 1; i < G->V; i++){
    if(!recursiveCheck(G, i, side, flag)){
      free(side);
      free(flag);
      return 0;
    }
    for(j = 1; j < G->V; j++){
      if(!flag[j]){
        i = j - 1;
        j = G->V;
      }
    }
  }

  free(side);
  free(flag);
  return 1;

}

int recursiveCheck(Graph G, Vertex actual, int *side, int *flag){
  int i;

  flag[actual] = 1;

  if(side[actual] == STANDING){
    for(i = 1; i < G->V; i++){
      if(G->adj[actual][i]){
        if(side[i] != STANDING){
          side[actual] = (side[i] % 2) + 1;
          i = G->V;
        }
      }
    }

    if(side[actual] == STANDING){
      side[actual] = LEFT;
    }
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
