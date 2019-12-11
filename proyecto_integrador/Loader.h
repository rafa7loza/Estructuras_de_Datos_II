#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <fstream>
#include <string>

#include "Buffer.h"
#include "Graph.h"
#include "Alumno.h"
#include "Index.h"
// #include "helpers.h"

using namespace std;

class Loader{
private:
  void write(Alumno a);
  void read(int position, Alumno &a);
  string filename;

public:
  Loader(string filename);
  void graphToFile(Graph g);
  void fileToGraph(Graph &g, Buffer buffer);

};
#endif
