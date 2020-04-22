#include "Edge.h"

Edge::Edge(Vertex* dest){
  this->dest = dest;
  this->nextEdge = nullptr;
}


bool Edge::hasNext(){
  return this->nextEdge !=  nullptr;
}

Edge* Edge::next(){
  return this->nextEdge;
}

void Edge::addNext(Vertex* v){
  this->nextEdge = new Edge(v);
}

string Edge::getData(){
  cout << this->dest->getData() << endl; 
  return this->dest->getData();
}
