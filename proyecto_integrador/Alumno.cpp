#include <iostream>
#include <string>

#include "Alumno.h"

using namespace std;

Alumno::Alumno(){
  // Use an auxiliary function to get a key that's is not used by another
  // user
  // key = assignKey();
  this->pk = 1;
}

void Alumno::setNames(string &s){
  this->names = s;
}

void Alumno::setLastNames(string &s){
  this->lastNames = s;
}

void Alumno::setEmailAdrress(string &s){
  this->email = s;
}

void Alumno::setPassword(string &s){
  this->password = s;
}

int Alumno::getPK(){
  return this->pk;
}

string Alumno::getNames(){
  return this->names;
}

string Alumno::getLastNames(){
  return this->lastNames;
}

string Alumno::getEmailAddress(){
  return this->email;
}

string Alumno::toString(){
  string s = to_string(this->pk) + ": " + this->names + " " + this->lastNames;
  return s;
}
