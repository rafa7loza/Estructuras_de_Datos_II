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
  cout << "Size of the object: " << objectSize << endl;
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

void Loader::read(int position, Alumno &a){
  ifstream fin;

  fin.open(this->filename, ios::binary);

  int n, lng;
  string str;
  char *c;

  fin.seekg(position);

  /*// Object size
  fin.read( (char *) &n, sizeof(int));
  cout << n << endl;*/

  // Read the primary key
  fin.read( (char *) &n, sizeof(int));
  a.setPK(n);
  // cout << n << endl;

  // Read the names
  fin.read( (char *) &lng, sizeof(int));
  c = new char[lng+1];
  fin.read(c, lng+1);
  str = c;
  a.setNames(str);
  // cout << str << endl;

  // Read the last names
  fin.read( (char *) &lng, sizeof(int));
  c = new char[lng+1];
  fin.read(c, lng+1);
  str = c;
  a.setLastNames(str);
  // cout << str << endl;

  // Read the email address
  fin.read( (char *) &lng, sizeof(int));
  c = new char[lng+1];
  fin.read(c, lng+1);
  str = c;
  a.setEmailAdrress(str);
  // cout << str << endl;

  // Read the password
  fin.read( (char *) &lng, sizeof(int));
  c = new char[lng+1];
  fin.read(c, lng+1);
  str = c;
  a.setPassword(str);
  // cout << str << endl;

  // Read the array of friends
  fin.read( (char *) &n, sizeof(int));
  for(int i=0; i<n; ++i){
    int frs;
    fin.read( (char *) &frs, sizeof(int));
    a.addFriend(frs);
  }

  // Read the array of interests
  fin.read( (char *) &n, sizeof(int));
  for(int i=0; i<n; ++i){
    bool interest;
    fin.read( (char *) &interest, sizeof(bool));
    if(interest) a.addInterest(i);
  }

  fin.close();
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

void Loader::fileToGraph(Graph &g, Buffer buffer){
  Alumno alumno;
  int size = buffer.getArraySize(), pos=(int) sizeof(int);
  Index* indexArray;
  indexArray = new Index[size];
  indexArray = buffer.getIndexArray();
  // cout << size << endl;

  for(int i=0; i<size; ++i){
    cout << "Position in file: " << pos << endl;
    // cout << indexArray[i].getIndex() << " - " << indexArray[i].getReference() << endl;
    read(pos, alumno);
    cout << alumno.toString() << endl;
    g.addUser(alumno);
    pos += indexArray[i].getReference() + (int)sizeof(int);
  }
}

void toChar(string &s, char c[]){
    int len = s.length(), i;
    for(i = 0; i<len; ++i){
      c[i] = s[i];
    }
    c[len] = '\0';
}
