#ifndef CLASS_H
#define CLASS_H
#include <iostream>

using namespace std;

class ClassA{

private:
  int primaryKey;
  string cadena;
  int arr[5];
public:
  ClassA(int key, string str, int a[]);
  void setPrimaryKey(int value);
  void setCadena(string &value);
  void setArray(int arr[]);
  int getPrimaryKey();
  string getCadena();
  int *getArray();
};

ClassA::ClassA(int key, string str, int a[]){
  primaryKey  = key;
  cadena = str;
  for(int i=0; i<5; ++i){
    arr[i] = a[i];
  }
}

void ClassA::setPrimaryKey(int value){
  primaryKey = value;
}

void ClassA::setCadena(string &value){
  cadena = value;
}

void ClassA::setArray(int value[]){
  for(int i=0; i<5; ++i){
    arr[i] = value[i];
  }
}

int ClassA::getPrimaryKey(){
  return primaryKey;
}

string ClassA::getCadena(){
  return cadena;
}

int* ClassA::getArray(){
  return arr;
}

#endif
