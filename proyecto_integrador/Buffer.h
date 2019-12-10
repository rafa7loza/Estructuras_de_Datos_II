#ifndef BUFFER_H
#define BUFFER_H

#include <string>

#include "Index.h"

using namespace std;

const int SZ = 1e3;

class Buffer{
private:
  Index indexArray[SZ];
  int size=0;
  string filename;

  // helpers
  bool isSorted;

  // Private methods
  void sort();
  void merge(int left, int right, int m);
  void mergeSort(int left, int right);

public:
  // Constructors
  Buffer();
  Buffer(string file);

  // Getters
  string getFilename();
  Index getIndexArray();

  void read();
  void read(string filename);

  int findValidKey();
  void printArray();


};

#endif
