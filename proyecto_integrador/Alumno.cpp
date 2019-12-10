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

void Alumno::setPK(int key){
    this->pk = key;
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

string Alumno::getPassword(){
  return this->password;
}

string Alumno::toString(){
  string s = to_string(this->pk) + ": " + this->names + " " + this->lastNames;
  return s;
}

int Alumno::getFriendsCounter(){
  return this->friendsCounter;
}

int* Alumno::getFriends(){
    return *&this->friends;
}

int Alumno::getInterestsCounter(){
  return this->interestsCounter;
}

bool* Alumno::getInterests(){
  return *&this->interests;
}

int Alumno::getSize(){
  // 8 is the number of bytes that tells me the size of the strings and arrays
  // including the pk
  return 8*sizeof(int) + this->names.length() + this->lastNames.length() + this->email.length() + this->password.length() + (this->interestsCounter*sizeof(bool)) + (this->friendsCounter*sizeof(int));
}
