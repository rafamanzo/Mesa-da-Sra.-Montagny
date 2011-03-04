#include <stdio.h>
#include <stdlib.h>
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "ed/graph.h"
#include "io.h"

int * inputLine(){
  int * line;

  line = malloc(2 * sizeof(int));

  if(scanf("%d %d", &line[0], &line[1]) == EOF){
    line[0] = -1;
    line[1] = -1;
  }

  return line;
}

Graph inputInstance(){
  Graph G;
  int *nums;
  int relations, i;

  nums = inputLine();
  if(nums[0] == -1 || nums[1] == -1){
    free(nums);
    return NULL;
  }else{
    G = GRAPHinit(nums[0] + 1);
    relations = nums[1];
    free(nums);

    for(i = 0; i < relations; i++){
      nums = inputLine();
      GRAPHinsertE(G, nums[0], nums[1]);
      free(nums);
    }

    return G;
  }  
}

void outInstance(int instance, int response){
  printf("Instancia %d", instance);
  if(response == 1){
    printf("\nsim\n\n");
  }else if(response == 0){
    printf("\nnao\n\n");
  }
}
