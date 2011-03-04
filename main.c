#include <stdio.h>
#include <stdlib.h>

/*vertex.h*/
#define Vertex int

/*digraph.h*/
#define MAXVERTEX 1000

struct digraph{
  int V;
  int A;
  int **adj;
};

typedef struct digraph *Digraph;

void lblInit();
Digraph DIGRAPHinit(int vertexCount);
void DIGRAPHdestroy(Digraph G);
int** MATRIXint(int r, int c, int val);
void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w);
void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w);
void DIGRAPHshow(Digraph G);
int DIGRAPHpath(Digraph G, Vertex s, Vertex t);
void pathR(Digraph G, Vertex v);

/*graph.h*/
#define GRAPHinit DIGRAPHinit
#define GRAPHdestroy DIGRAPHdestroy
#define GRAPHshow DIGRAPHshow
#define GRAPHpath DIGRAPHpath
#define Graph Digraph

void GRAPHinsertE(Graph G, Vertex v, Vertex w);
void GRAPHremoveE(Graph G, Vertex v, Vertex w);

/*io.h*/
Graph inputInstance();
void outInstance(int instance, int response);
int inputNum();
int * inputLine();

/*mesa.h*/
#define STANDING 0
#define RIGHT 1
#define LEFT 2

int processInstance(Graph G);
void solver();

/*digraph.c*/
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
  int i,j;

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

/*graph.c*/
void GRAPHinsertE(Graph G, Vertex v, Vertex w){
  DIGRAPHinsertA(G, v, w);
  DIGRAPHinsertA(G, w, v);
}

void GRAPHremoveE(Graph G, Vertex v, Vertex w){
  DIGRAPHremoveA(G, v, w);
  DIGRAPHremoveA(G, w, v);
}

/*io.c*/
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

/*mesa.c*/
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

/*main.c*/
int main(int argc, const char* argv[]){
  solver();
  return 0;
}
