#include <stdio.h>
#include <stdlib.h>
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "ed/graph.h"
#include "io.h"

int inputNum(){
  int i, j;
  char num[3]; /* como 0 <= n <= 100, a maior string possível tem 3 caracteres  */
  char *ret;
  char c;  

  /*limpa buffer de leitura*/
  for(i = 0; i < 3; i++){
    num[i] = '0';
  }

  c = getchar();
  i = 0;

  while(c != ' ' && c != '\n' && c != EOF && i < 3){
    num[2 - i] = c;
    i++;
    c = getchar();
  }

  if(c == EOF){
    return -1;
  }else{
    ret = malloc(i*sizeof(char));

    for(j = 3 - i; j >= 0; j--){
      ret[j] = num[j + i - 1];
    }

    return atoi(ret);
  }
}

int * inputLine(){
  int * line;

  line = malloc(2 * sizeof(int));

  line[0] = inputNum();
  if(line[0] != -1){
    line[1] = inputNum();
  }else{
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
    printf("\nsim\n");
  }else if(response == 0){
    printf("\nnao\n");
  }
}
