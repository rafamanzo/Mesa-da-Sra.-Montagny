#include "vertex.h"
#include "digraph.h"
#include "graph.h"

void GRAPHinsertE(Graph G, Vertex v, Vertex w){
  DIGRAPHinsertA(G, v, w);
  DIGRAPHinsertA(G, w, v);
}

void GRAPHremoveE(Graph G, Vertex v, Vertex w){
  DIGRAPHremoveA(G, v, w);
  DIGRAPHremoveA(G, w, v);
}
