#ifndef CLASSB_H
#define CLASSB_H

#include <iostream>

using namespace std;

class ClassB{
private:
  string value;
  bool status;

public:
  ClassB();
  ClassB(string v, bool a);
  void setString(string &val);
  void setStatus(bool s);
  string getString();
  bool getStatus();
};

ClassB::ClassB(){}

ClassB::ClassB(string v, bool a){
  value = v;
  status = a;
}

void ClassB::setString(string &val){
  value = val;
}

void ClassB::setStatus(bool s){
  status = s;
}

string ClassB::getString(){
  return value;
}

bool ClassB::getStatus(){
  return status;
}

#endif
