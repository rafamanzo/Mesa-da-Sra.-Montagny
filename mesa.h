/**********************************/
/* MAC0328 - Algoritmos em grafos */
/*                                */
/* rafamz                         */
/* macacada                       */
/* Rafael Reggiani Manzo          */
/* 6797150                        */
/**********************************/

#define STANDING 0
#define RIGHT 1
#define LEFT 2

int recursiveCheck(Graph G, Vertex actual, int *side, int *flag);
int processInstance(Graph G);
void solver();
