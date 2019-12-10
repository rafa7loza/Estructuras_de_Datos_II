#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

using namespace std;

class Vertex;

class Edge{
private:
  Edge* next;
  Vertex* dest;

public:
  Edge(Vertex* dest);
};

#endif
