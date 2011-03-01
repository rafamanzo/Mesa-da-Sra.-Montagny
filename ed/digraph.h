#define MAXVERTEX 1000

struct digraph{
  int V;
  int A;
  int **adj;
};

typedef struct digraph *Digraph;

void lblInit();
Digraph DIGRAPHinit(int vertexCount);
int** MATRIXint(int r, int c, int val);
void DIGRAPHinsertA(Digraph G, Vertex v, Vertex w);
void DIGRAPHremoveA(Digraph G, Vertex v, Vertex w);
void DIGRAPHshow(Digraph G);
int DIGRAPHpath(Digraph G, Vertex s, Vertex t);
void pathR(Digraph G, Vertex v);
