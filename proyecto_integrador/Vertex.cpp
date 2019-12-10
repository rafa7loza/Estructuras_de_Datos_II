#include "Vertex.h"

Vertex::Vertex(Alumno value){
  this->head = nullptr;
  this->nextVertex = nullptr;
  this->edgeCouter = 0;
  this->value = value;
}

bool Vertex::hasNext(){
  return this->nextVertex != nullptr;
}

Vertex* Vertex::next(){
  return this->nextVertex;
}

void Vertex::addNext(Alumno value){
  this->nextVertex = new Vertex(value);
}

string Vertex::getData(){
  return this->value.toString();
}
