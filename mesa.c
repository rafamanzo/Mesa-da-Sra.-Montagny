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
    DIGRAPHdestroy(G);
    G = inputInstance();
  }
}

int processInstance(Graph G){
  int i;
  int *side; /*array para marcar os lados da mesa*/

  side = malloc((G->V + 1)*sizeof(int));

  for(i = 1; i <= G->V; i++){
    side[i] = STANDING;
  }

  for(i = 1; i <= G->V; i++){
    if(side[i] == STANDING){
      side[i] = LEFT;
    }
    for(j = i + 1; j < G->V; j++){
      if(G->adj[i][j] == 1){
        side[j] = (side[i] % 2) + 1;
      }
    }
  }

  free(side);

  return 1;
}
