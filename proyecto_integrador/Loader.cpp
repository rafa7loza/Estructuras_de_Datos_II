#include "Loader.h"

void toChar(string &s, char c[]);

Loader::Loader(string filename){
  this->filename = filename;
}

void Loader::write(Alumno a){
  ofstream fout;
  fout.open(this->filename, ios::app);

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
  n = a.getFriendsCounter();
  fout.write( (char *) &n, sizeof(int));
  int *frs;
  frs = a.getFriends();
  for(int i=0; i<n; ++i ){
    fout.write( (char *) &frs[i], sizeof(int));
  }

  // Write the boolean array
  n = a.getInterestsCounter();
  fout.write( (char *) &n, sizeof(int));
  bool *arr;
  arr = a.getInterests();
  for(int i=0; i<n; ++i){
    fout.write( (char *) &arr[i], sizeof(bool));
  }

  fout.close();

}

void Loader::graphToFile(Graph g){

  // Creates the file where data is going to be stored
  /*ofstream fout;
  fout.open(this->filename, ios::binary);
  fout.close();*/
  remove(this->filename.c_str());

  // Loading all the users from the graph
  Alumno* arr;
  int len = g.getVertexCount();
  arr = g.getUsers();

  for(int i=0; i<len; ++i){
    this->write(arr[i]);
  }
  cout << "Done writing file ! ! " << endl;
}

void toChar(string &s, char c[]){
    int len = s.length(), i;
    for(i = 0; i<len; ++i){
      c[i] = s[i];
    }
    c[len] = '\0';
}
