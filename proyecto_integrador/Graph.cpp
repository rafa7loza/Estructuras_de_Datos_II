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
  if(this->source == nullptr) {
    this->source = new Vertex(value);
    addFriends(this->source, value);
  }
  else{
    Vertex* aux = this->source;
    while(aux->hasNext()){
      aux = aux->next();
    }
    aux->addNext(value);
    addFriends(aux->next(), value);
  }
  ++vertexCounter;
}

void Graph::addFriends(Vertex* currentVertex, Alumno value){
  int n = value.getFriendsCounter();
  if(n > 0){
    int *friends;
    friends = new int[n];
    for(int i=0; i<n; ++i){
      Vertex* thatVertex = findVertex(friends[i]);
      thatVertex->addEdge(currentVertex);
      currentVertex->addEdge(thatVertex);
    }
  }
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

Alumno* Graph::findUser(int pk){
  if(this->source == nullptr) return nullptr;

  // Alumno arr[MAX];
  Vertex* aux = this->source;

  while(aux->hasNext()){
    // Alumno a = aux->getData();
    if(aux->getValue().getPK() == pk){
      Alumno *a = aux->getValuePtr();
      return a;
    }
    aux = aux->next();
  }
  return nullptr;
}

Vertex* Graph::findVertex(int key){
  if(this->source == nullptr) return nullptr;

  Vertex* aux = this->source;

  while(aux->hasNext()){
    if(aux->getValue().getPK() == key) return aux;
    aux = aux->next();
  }
  return nullptr;
}

void Graph::makeFriendRequest(int fromUser, int toUser){
  Vertex* from = findVertex(fromUser);
  Vertex* to = findVertex(toUser);
  from->addEdge(to);
}


// For debugging the progamm

void Graph::printVertex(){
  if(this->source == nullptr) return ;

  Vertex* auxVertex = this->source;
  while(auxVertex->hasNext()){
    cout << auxVertex->getData() << endl << endl;
    auxVertex->printEdges();
    auxVertex = auxVertex->next();
  }
  cout << auxVertex->getData() << endl;
  auxVertex->printEdges();
}
