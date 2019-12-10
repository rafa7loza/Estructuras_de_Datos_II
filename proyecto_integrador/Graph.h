#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

#include "Vertex.h"
#include "Alumno.h"

using namespace std;

class Vertex;

class Graph{
private:
  Vertex* source;
  int vertexCounter;

public:
  Graph();
  void addUser(Alumno value);
  Alumno* getUsers();
  int getVertexCount();

  void printVertex();
};

#endif
