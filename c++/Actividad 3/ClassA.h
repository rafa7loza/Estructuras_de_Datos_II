#ifndef CLASSA_H
#define CLASSA_H

#include <iostream>
#include <string>
#include "ClassB.h"

#define MAX 9
#define STR_LNG 20

using namespace std;

class ClassA{
private:
  int primaryKey;
  string str;
  ClassB obj[MAX];
  int arrSize;

public:
  ClassA();
  ClassA(int pk, string &value, ClassB b[], int sz);
  void setPK(int value);
  void setString(string &value);
  void setClassB(int size);
  int getPK();
  string getString();
  int getArrSize();
  ClassB* getClassBArr();
};

ClassA::ClassA(){}

ClassA::ClassA(int pk, string &value, ClassB b[], int sz){
  primaryKey = pk;
  str = value;
  arrSize = sz;
  for(int i=0; i<sz; ++i){
    obj[i] = b[i];
  }

}

void ClassA::setPK(int value){
  primaryKey = value;
}

void ClassA::setString(string &value){
  int sz = value.length();
  if(sz < STR_LNG){
    int diff = STR_LNG - sz;
    for(int i=0; i<diff; ++i){
      value += " ";
    }
  }else{
    value = value.substr(0, STR_LNG);
  }
  str = value;
}

void ClassA::setClassB(int size){
  double value;
  bool isActive;
  ClassB b;
  for(int i=0; i<size; ++i){
    cout << "Creating object B_" << i+1 << endl;
    cout << "Enter the value of the double: ";
    cin >> value;
    cout << "Enter the value of the boolean: ";
    cin >> isActive;
    b.setValue(value);
    b.setStatus(isActive);
    obj[i] = b;
  }
  arrSize = size;
}

int ClassA::getPK(){
  return primaryKey;
}

string ClassA::getString(){
  return str;
}

int ClassA::getArrSize(){
  return arrSize;
}

ClassB* ClassA::getClassBArr(){
  return obj;
}

#endif
