#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>

#include "Buffer.h"

Buffer::Buffer(){
  this->filename = "test.bin";
  isSorted = true;
}

Buffer::Buffer(string file){
  this->filename = file;
  read(file);
}

void Buffer::merge(int left, int right, int m){
  int i, j, k;
  int sz_a = m - left + 1;
  int sz_b =  right - m;

  Index *cpA, *cpB;
  cpA = new Index[sz_a];
  cpB = new Index[sz_b];

  for (i = 0; i < sz_a; i++)
      cpA[i] = this->indexArray[left + i];
  for (j = 0; j < sz_b; j++)
      cpB[j] = this->indexArray[m + 1+ j];

  i = 0;
  j = 0;
  k = left;
  while (i < sz_a && j < sz_b){
    if (cpA[i].getIndex() <= cpB[j].getIndex()){
      this->indexArray[k] = cpA[i];
      i++;
    }
    else{
      this->indexArray[k] = cpB[j];
      j++;
    }
    k++;
  }

  while (i < sz_a){
    this->indexArray[k] = cpA[i];
    i++;
    k++;
  }

  while (j < sz_b){
    this->indexArray[k] = cpB[j];
    j++;
    k++;
  }
}

void Buffer::mergeSort(int left, int right){
  if(left < right){
    int m = (left+(right-1))/2;
    // cout << "left: " << left << ", right: " << right << ", m: " << m << endl;

    mergeSort(left, m);
    mergeSort(m+1, right);

    merge(left, right, m);
  }
}

void Buffer::sort(){
  mergeSort(0, this->size-1);
}

string Buffer::getFilename(){
    return this->filename;
}

void Buffer::read(){
  read(this->filename);
}

void Buffer::read(string filename){
  ifstream fin;

  fin.open(this->filename, ios::binary);
  cout << "Reading file " << this->filename << " . . . " << endl;

  int fileSize, pk, reference, objectSize;

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while(fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));

    // cout << pk << " - " << objectSize << " deb   . . " << endl;
    this->indexArray[this->size++] = Index(pk, objectSize);

    fin.seekg((int)fin.tellg() + objectSize - sizeof(int));
  }

  // Sort the index array
  this->sort();
  isSorted = true;
}

int Buffer::findValidKey(){
  // It is known that there cannot be repeated keys,
  // keys are actually 1-based index from the indexArray
  this->sort();
  // int maxKey = this->indexArray[this->size-1].getIndex();
  for(int i=0; i<this->size; ++i){
    if(this->indexArray[i].getIndex() != (i+1)){
      this->indexArray[this->size++].setIndex(this->size);
      return this->size;
    }
  }
  this->indexArray[this->size++].setIndex(this->size);
  return this->size;
}

Index* Buffer::getIndexArray(){
  return *&this->indexArray;
}

void Buffer::printArray(){
  if(!isSorted) this->sort();
  for(int i=0; i<this->size; ++i){
    cout << "Pk: " << this->indexArray[i].getIndex() <<
      ": " << this->indexArray[i].getReference() << endl;
  }
}

int Buffer::getArraySize(){
  return this->size;
}
