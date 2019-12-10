#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>

#include "Edge.h"
#include "Alumno.h"

using namespace std;

class Vertex;
class Edge;

class Vertex{
private:
  Edge* head;
  Vertex* nextVertex;

  int edgeCouter;
  Alumno value;

public:
  Vertex(Alumno value);
  bool hasNext();
  Vertex* next();
  void addNext(Alumno value);

  string getData();
  Alumno getValue();

};

#endif
