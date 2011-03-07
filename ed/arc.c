/**********************************/
/* MAC0328 - Algoritmos em grafos */
/*                                */
/* rafamz                         */
/* macacada                       */
/* Rafael Reggiani Manzo          */
/* 6797150                        */
/**********************************/

#include "vertex.h"
#include "arc.h"

Arc ARC(Vertex v, Vertex w){
  Arc e;
  e.v = v;
  e.w = w;
  return e;
}
