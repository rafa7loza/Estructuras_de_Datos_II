#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>

#include "Buffer.h"
// #include "helpers.h"

using namespace std;

//Buffer::Buffer(){};

Buffer::Buffer(){}


void Buffer::read(){
  /*string filename = "Alumnos.bin";
  // assert(fileExists(filename) == true);

  ifstream fin;
  fin.open(filename, ios::bin);

  int fileSize, pk, reference;

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while(fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));

    cout << pk << " - " << objectSize << endl;

    fin.seekg(objectSize);
  }*/
}
