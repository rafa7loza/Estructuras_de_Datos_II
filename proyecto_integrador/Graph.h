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

  Vertex* findVertex(int key);
  void addFriends(Vertex* currentVertex, Alumno value);
  
public:
  Graph();
  void addUser(Alumno value);
  Alumno* getUsers();
  int getVertexCount();
  Alumno* findUser(int pk);

  void makeFriendRequest(int fromUser, int toUser);
  // void updateUser()


  void printVertex();
};

#endif
