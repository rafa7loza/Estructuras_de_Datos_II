#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

using namespace std;

class Vertex;

class Edge{
private:
  Edge* nextEdge;
  Vertex* dest;

public:
  Edge(Vertex* dest);

  bool hasNext();
  Edge* next();
  void addNext(Vertex* v);
  string getData();
};

#endif
