#ifndef CLASSB_H
#define CLASSB_H

#include <iostream>

using namespace std;

class ClassB{
private:
  double value;
  bool status;

public:
  ClassB();
  ClassB(double v, bool a);
  void setValue(double val);
  void setStatus(bool s);
  double getValue();
  bool getStatus();
};

ClassB::ClassB(){}

ClassB::ClassB(double v, bool a){
  value = v;
  status = a;
}

void ClassB::setValue(double val){
  value = val;
}

void ClassB::setStatus(bool s){
  status = s;
}

double ClassB::getValue(){
  return value;
}

bool ClassB::getStatus(){
  return status;
}

#endif
