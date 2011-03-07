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

/*mesa.h*/
#define STANDING 0
#define RIGHT 1
#define LEFT 2

int processInstance(Graph G);
int recursiveCheck(Graph G, Vertex actual, int *side, int *flag);
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

/*mesa.c*/
void solver(){
  int instance;
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

/*main.c*/
int main(int argc, const char* argv[]){
  solver();
  return 0;
}
