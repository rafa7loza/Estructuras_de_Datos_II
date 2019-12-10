#ifndef BUFFER_H
#define BUFFER_H

#include "Index.h"

const int SZ = 1e3;

class Buffer{
  //friend class Index;
private:
  Index indexArray[100];
  int size=0;

public:
  Buffer();
  //Buffer(string filename);
  // void readFromFile(string filename);
  void read();
};

#endif
