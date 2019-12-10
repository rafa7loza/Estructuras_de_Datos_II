#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <fstream>
#include <string>

#include "Alumno.h"

using namespace std;

void toChar(string &s, char c[]){
    int len = s.length(), i;
    for(i = 0; i<len; ++i){
      c[i] = s[i];
    }
    c[len] = '\0';
}

bool fileExists(string filename){
  ifstream file(filename.c_str());
  return file.good();
}

void setUser(Alumno &a, int key){
  string aux;
  a.setPK(key);

  cout << "Ingrese el nombre o los nombres del usuario: ";
  cin.ignore();
  getline(cin, aux);
  a.setNames(aux);

  cout << "Ingrese el o los apellidos del usuario: ";
  getline(cin, aux);
  a.setLastNames(aux);

  cout << "Ingrese la dirección de correo: ";
  getline(cin, aux);
  a.setEmailAdrress(aux);

  cout << "Ingrese la contraseña: ";
  getline(cin, aux);
  a.setPassword(aux);
}

void writeToBin(Alumno a, string filename){

  ofstream fout;

  if(fileExists(filename)){
    fout.open(filename, ios::app);
  }else{
    fout.open(filename, ios::binary);
  }

  int objectSize = a.getSize(), lng, n;
  char *c;
  string s;

  // First write the size of the full object.
  fout.write( (char *) &objectSize, sizeof(int));

  // Write the primary key
  n = a.getPK();
  fout.write( (char *) &n, sizeof(int));

  // Write the names
  s = a.getNames();
  lng = s.length();
  c = new char[lng+1];
  fout.write( (char *) &lng, sizeof(int));
  toChar(s, c);
  fout.write(c, lng+1);

  // Write the last names
  s = a.getLastNames();
  lng = s.length();
  c = new char[lng+1];
  fout.write( (char *) &lng, sizeof(int));
  toChar(s, c);
  fout.write(c, lng+1);

  // Write the email address
  s = a.getEmailAddress();
  lng = s.length();
  c = new char[lng+1];
  fout.write( (char *) &lng, sizeof(int));
  toChar(s, c);
  fout.write(c, lng+1);

  // Write the password
  s = a.getPassword();
  lng = s.length();
  c = new char[lng+1];
  fout.write( (char *) &lng, sizeof(int));
  toChar(s, c);
  fout.write(c, lng+1);

  // Write the number of friends
  n = a.getFriendsNum();
  fout.write( (char *) &n, sizeof(int));

  // Write the boolean array
  n = 10;
  bool *arr;
  arr = a.getArr();
  fout.write( (char *) &n, sizeof(int));
  for(int i=0; i<n; ++i){
    fout.write( (char *) &arr[i], sizeof(bool));
  }

  fout.close();
}

void readFromBin(string filename){
  ifstream fin;

  if(!fileExists(filename)) return;
  fin.open(filename, ios::binary);

  int fileSize, objectSize, n, lng;
  string str;
  char *c;
  bool interest;

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while(fin.tellg() < fileSize){
    // Size of the object
    fin.read( (char *) &objectSize, sizeof(int));

    // Read the primary key
    fin.read( (char *) &n, sizeof(int));
    cout << "PK: " << n << endl;

    for(int i=0; i<4; ++i){
      // Read the lines
      fin.read( (char *) &lng, sizeof(int));
      c = new char[lng+1];
      fin.read(c, lng+1);
      str = c;
      cout << str << endl;
    }

    // Read the number of friends
    fin.read( (char *) &n, sizeof(int));
    cout << "Number of friends: " << n << endl;

    // Read the boolean array
    fin.read( (char *) &n, sizeof(int));
    for(int i=0; i<n; ++i){
      fin.read( (char *) &interest, sizeof(bool));
      cout << interest << ", ";
    }
    cout << endl << endl;
  }

  fin.close();
}







#endif
