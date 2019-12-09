#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <string>

// Might change
const int LEN_INTERESTS = 10;

using namespace std;

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
  void setNames(string &s);
  void setLastNames(string &s);
  void setEmailAdrress(string &s);
  void setPassword(string &s);

  // Getters
  int getPK();
  string getNames();
  string getLastNames();
  string getEmailAddress();

  string toString();
};

#endif
