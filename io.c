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
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "ed/graph.h"
#include "io.h"

Graph inputInstance(){
  Graph G;
  int in1, in2;
  int relations, i;

  if(scanf("%d %d", &in1, &in2) == EOF){
    return NULL;
  }

  G = GRAPHinit(in1 + 1);
  relations = in2;

  for(i = 0; i < relations; i++){
    scanf("%d %d", &in1, &in2);
    GRAPHinsertE(G, in1, in2);
  }

  return G;  
}

void outInstance(int instance, int response){
  printf("Instancia %d", instance);
  if(response == 1){
    printf("\nsim\n\n");
  }else if(response == 0){
    printf("\nnao\n\n");
  }
}
