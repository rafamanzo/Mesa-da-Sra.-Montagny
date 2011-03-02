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
     G = inputInstance();
  }
}

int processInstance(Graph G){
  int i, j;
  int *side; /*array para marcar os lados da mesa*/

  side = malloc((G->V + 1)*sizeof(int));

  for(i = 1; i <= G->V; i++){
    side[i] = STANDING;
  }

  for(i = 1; i <= G->V; i++){
    if(side[i] == STANDING){
      side[i] = LEFT;
    }
    for(j = i + 1; j <= G->V; j++){
      if(G->adj[i][j] == 1){
        switch(side[j]){
          case STANDING:
            if(side[i] == RIGHT){
              side[j] = LEFT;
            }else{
              side[j] = RIGHT;
            }
            break;
          case RIGHT:
            if(side[i] == RIGHT){
              return 0;
            }
            break;
          case LEFT:
            if(side[i] == LEFT){
              return 0;
            }
            break; 
        }
      }
    }
  }

  free(side);

  return 1;
}
