#include "Edge.h"

Edge::Edge(Vertex* dest){
  this->dest = dest;
  this->next = nullptr;
}
