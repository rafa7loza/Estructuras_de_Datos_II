#include "Index.h"

Index::Index(){
  this->reference = -1;
  this->index = -1;
}

Index::Index(int ind, int ref){
  this->index = ind;
  this->reference = ref;
}

int Index::getIndex(){
  return this->index;
}

int Index::getReference(){
  return this->reference;
}

void Index::setIndex(int ind){
  this->index = ind;
}

void Index::setReference(int ref){
  this->reference = ref;
}
