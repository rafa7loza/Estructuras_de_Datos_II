#include "Graph.h"

// const int MAX = 1e6;

Graph::Graph(){
  this->source = nullptr;
  this->vertexCounter = 0;
}

int Graph::getVertexCount(){
  return this->vertexCounter;
}

void Graph::addUser(Alumno value){
  if(this->source == nullptr) this->source = new Vertex(value);
  else{
    Vertex* aux = this->source;
    while(aux->hasNext()){
      aux = aux->next();
    }
    aux->addNext(value);
  }
  ++vertexCounter;
}

Alumno* Graph::getUsers(){
  if(this->source == nullptr) return nullptr;

  // Alumno arr[MAX];
  Vertex* aux = this->source;
  Alumno *arr;
  arr = new Alumno[this->vertexCounter];
  int i=0;

  while(aux->hasNext()){
    // Alumno a = aux->getData();
    arr[i++] = aux->getValue();
    aux = aux->next();
  }
  arr[i] = aux->getValue();
  return *&arr;
}


// For debugging the progamm

void Graph::printVertex(){
  if(this->source == nullptr) return ;

  Vertex* aux = this->source;
  while(aux->hasNext()){
    cout << aux->getData() << endl;
    // cout << aux->hasNext() << endl;
    aux = aux->next();
  }
  cout << aux->getData() << endl;
}
