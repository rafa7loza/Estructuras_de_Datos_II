#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <string>

using namespace std;

// Might change
const int MAX = 1e5;

class Alumno{
private:
  int pk;
  string names;
  string lastNames;
  string email;
  string password;

  // Array of the friends
  int friends[MAX]={0};
  int friendsCounter=0;

  // Interests are stored in an bool array
  bool interests[MAX]={false};
  int interestsCounter=0;

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
  int* getFriends();
  int getFriendsCounter();
  bool* getInterests();
  int getInterestsCounter();

  // Aux methods
  string toString();
  int getSize();
};

#endif
