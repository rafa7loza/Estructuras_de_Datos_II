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

Alumno Vertex::getValue(){
  return this->value;
}

Alumno* Vertex::getValuePtr(){
  return &this->value;
}

void Vertex::addEdge(Vertex* v){
  if(this->head == nullptr) this->head = new Edge(v);
  else{
    Edge* aux = this->head;
    while(aux->hasNext()){
      aux = aux->next();
    }
    aux->addNext(v);
  }
  ++edgeCouter;
}

void Vertex::printEdges(){
  if(this->head == nullptr){
    cout << " N U L L " << endl;
    return;
  }else{
    Edge* aux = this->head;
    cout << "|" << endl;
    cout << "-->" << aux->getData() << endl;
    while(aux->hasNext()){
      cout << "|" << endl;
      cout << "-->" << aux->getData() << endl;
      aux = aux->next();
    }
  }
}
