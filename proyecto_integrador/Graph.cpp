#include "Graph.h"

Graph::Graph(){
  this->source = nullptr;
  this->vertexCounter = 0;
}

void Graph::addUser(Alumno value){
  if(this->source == nullptr) this->source = new Vertex(value);
  else{
    Vertex* aux = this->source;
    while(!aux->hasNext()){
      aux = aux->next();
    }
    aux->addNext(value);
  }
}


// For debugging the progamm

void Graph::printVertex(){
  if(this->source == nullptr) return ;

  Vertex* aux = this->source;
  while(aux->hasNext()){
    cout << aux->getData() << endl;
    cout << aux->hasNext() << endl;
    aux = aux->next();
  }

}
