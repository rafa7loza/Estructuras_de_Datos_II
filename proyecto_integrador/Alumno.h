#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <string>

using namespace std;

// Might change
const int LEN_INTERESTS = 10;

class Alumno{
private:
  int pk;
  string names;
  string lastNames;
  string email;
  string password;
  int friends=0;
  // Interests are stored in an bool array
  bool interests[LEN_INTERESTS]={false};

public:

  Alumno();

  // Setters
  void setPK(int key);
  void setNames(string &s);
  void setLastNames(string &s);
  void setEmailAdrress(string &s);
  void setPassword(string &s);

  // Getters
  int getPK();
  string getNames();
  string getLastNames();
  string getEmailAddress();
  string getPassword();
  int getFriendsNum();
  bool* getArr();

  // Aux methods
  string toString();
  int getSize();
};

#endif
