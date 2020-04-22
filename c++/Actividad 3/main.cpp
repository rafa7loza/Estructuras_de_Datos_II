#include <iostream>
#include <fstream>
#include <vector>
#include "ClassA.h"
#include "ClassB.h"
#include "menu.h"

#define STR_LNG 20
#define MAX 9
#define FILENAME "file.bin"
#define AUX_FILE "aux.bin"
#define PK "pk"
#define STR "str"
#define ARR "arr"
#define LINE_SEPARATOR "=========================="

using namespace std;

ClassA createObject();
void appendToFile(ClassA obj, string filename);
void appendBeginOfFile(ClassA obj);
void readAllFromFile(string filename);
bool fileExists(string filename);
vector<int> findKeys(string filename);
bool existKey(int key, vector<int>keys);
ClassA findByKey(int key, string filename);
void printObject(ClassA a);
void copyFromAuxToFile(string aux, string filename);
void modifyAttribute(string type, int key);
void eraseObjectFromFile(int key);

int main(){

  ClassA a;
  Menu menu;
  int opt;
  vector<int> keys;

  do{
    menu.home();
    cin >> opt;

    switch (opt) {

      case 1: {
        int aux;

        do{
          menu.insert();
          cin >> aux;
          switch (aux) {
            case 1:{
              a = createObject();
              appendToFile(a, FILENAME);
              break;
            }
            case 2:{
              a = createObject();
              appendBeginOfFile(a);
              break;
            }
            default: {
              cout << "Wrong option, try again." << endl;
              break;
            }
          }
        }while(aux != 1 && aux != 2);
        break;
      }

      case 2: {
        int key;

        keys = findKeys(FILENAME);
        cout << "Enter the key of the object you want to erase:" << endl;
        cin >> key;

        if(existKey(key, keys)){
          eraseObjectFromFile(key);
        }else{
          cout << "The object that you're looking for doesn't exists." << endl;
        }
        break;
      }

      case 3: {
        int key;

        keys = findKeys(FILENAME);
        cout << "Enter the key of the object you want to show:" << endl;
        cin >> key;

        if(existKey(key, keys)){
          ClassA currentClassA = findByKey(key, FILENAME);
          printObject(currentClassA);
        }else{
          cout << "The object that you're looking for doesn't exists." << endl;
        }
        break;
      }

      case 4:{
        int key, aux;
        string type;

        keys = findKeys(FILENAME);
        cout << "Enter the key of the object you want to modify:" << endl;
        cin >> key;

        if(existKey(key, keys)){
          ClassA currentClassA = findByKey(key, FILENAME);
          printObject(currentClassA);

          do{
            menu.modifyClassA();
            cin >> aux;
            switch (aux) {
              case 1:{
                type = STR;
                break;
              }
              case 2:{
                type = PK;
                break;
              }
              case 3:{
                type = ARR;
                break;
              }
              default: {
                cout << "Wrong option, try again." << endl;
                break;
              }
            }
          }while(aux != 1 && aux != 2 && aux != 3);

          modifyAttribute(type, key);

        }else{
          cout << "The object that you're looking for doesn't exists." << endl;
        }
        break;
      }

      case 5: {
        readAllFromFile(FILENAME);
        break;
      }

      case 6: {
        cout << "You exited the program . . . " << endl;
        break;
      }
      
      default: {
        cout << "Wrong option, try again." << endl;
        break;
      }
    }

  }while(opt != 6);


  return 0;
}

ClassA createObject(){

  ClassA a;
  int pk, arrSize;
  string name;

  vector<int> keys = findKeys(FILENAME);
  while(true){
    cout << "Set primary key: ";
    cin >> pk;
    if(existKey(pk, keys)){
      cout << "This primary key already exists, please try another." << endl;
    }else break;
  }
  cout << "Set the string: ";
  cin.ignore();
  getline(cin, name);
  cout << "Set size of array: ";
  cin >> arrSize;

  a.setPK(pk);
  a.setString(name);
  a.setClassB(arrSize);

  return a;
}

void printObject(ClassA obj){
  ClassB *tb;
  tb = new ClassB[9];

  cout << LINE_SEPARATOR << endl << endl
    << "Primary key: " << obj.getPK() << endl
    << "String: " << obj.getString() << endl << endl;

  int arrSize = obj.getArrSize();
  tb = obj.getClassBArr();
  for(int i=0; i<arrSize; ++i){
    cout << "\tClassB_" << i+1 << endl
      << "Double: "<< tb[i].getValue() << endl
      << "Bool: " <<tb[i].getStatus() << endl << endl;
  }
  cout << LINE_SEPARATOR << endl;
}

void appendToFile(ClassA obj, string filename){
  ofstream fout;
  ClassB *b;
  b = new ClassB[MAX];
  b = obj.getClassBArr();
  string str = obj.getString();
  int pk = obj.getPK(), arrSize = obj.getArrSize(),  lng = STR_LNG;
  int objectSize, i, bSize=0;

  if(fileExists(filename)){
    fout.open(filename, ios::app);
  }else{
    fout.open(filename, ios::binary);
  }

  for(i=0; i<arrSize; ++i){
    bSize += sizeof(double) + sizeof(bool);
  }

  objectSize = (2+(arrSize*2)+1)*sizeof(int)+lng+1+bSize;

  fout.write( (char *) &objectSize, sizeof(int));
  fout.write( (char *) &pk, sizeof(int));
  fout.write( (char *) &lng, sizeof(int));

  char temp[lng+1];
  for(i=0; i<lng; ++i){
    temp[i] = str[i];
  }
  temp[lng] = '\0';
  fout.write(temp, lng+1);

  fout.write( (char *) &arrSize, sizeof(int));
  for(i = 0; i<arrSize; ++i){
    double value = b[i].getValue();
    bool status = b[i].getStatus();
    fout.write( (char *) &value, sizeof(double));
    fout.write( (char *) &status, sizeof(bool));
  }

  fout.close();
}

void appendBeginOfFile(ClassA obj){

  int i, sz;

  appendToFile(obj, AUX_FILE);
  vector<int> keys = findKeys(FILENAME);
  sz = keys.size();

  ClassA temp;
  for(i=0; i<sz; ++i){
    temp = findByKey(keys[i], FILENAME);
    appendToFile(*&temp, AUX_FILE);
  }

  copyFromAuxToFile(AUX_FILE, FILENAME);

}

void copyFromAuxToFile(string aux, string filename){
  int i, sz;

  vector<int> keys = findKeys(aux);
  sz = keys.size();

  if(fileExists(filename)){
    remove(filename.c_str());
  }

  ClassA temp;
  for(i=0; i<sz; ++i){
    temp = findByKey(keys[i], aux);
    appendToFile(*&temp, filename);
  }

  remove(aux.c_str());
}

void readAllFromFile(string filename){
  ifstream fin;
  fin.open(filename, ios::binary);

  int fileSize, objectSize, arrSize, pk, i, lng, cont=0;
  string str;
  double value;
  bool status;
  char temp[STR_LNG+1];


  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  cout << endl << LINE_SEPARATOR << endl;

  while (fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));
    fin.read( (char *) &lng, sizeof(int));
    fin.read(temp, lng+1);
    str = temp;

    cout << "\tObject A_" << ++cont << endl;

    cout << "Size: " << objectSize << endl
      << "PK: " << pk << endl
      << "String: " << str << endl;

    fin.read( (char *) &arrSize, sizeof(int));
    cout << "Size of array: " << arrSize << endl;
    for(i = 0; i<arrSize; ++i){
      fin.read( (char *) &value, sizeof(double));
      fin.read( (char *) &status, sizeof(bool));
      cout << "Double: " << value << endl
        << "Boolean: " << status << endl;
    }
    cout << LINE_SEPARATOR << endl;
  }

  fin.close();
}

void modifyAttribute(string type, int key){
  ifstream fin;
  fin.open(FILENAME, ios::binary);

  int fileSize, objectSize, arrSize, pk, i, lng;
  string str;
  double value;
  bool status;
  char temp[STR_LNG+1];

  ClassB b[MAX];

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while (fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));
    fin.read( (char *) &lng, sizeof(int));
    fin.read(temp, lng+1);
    str = temp;
    fin.read( (char *) &arrSize, sizeof(int));
    for(i = 0; i<arrSize; ++i){
      fin.read( (char *) &value, sizeof(double));
      fin.read( (char *) &status, sizeof(bool));
      ClassB tb(value, status);
      b[i] = tb;
    }

    ClassA a(pk, str, b, arrSize);

    if(pk == key){
      if(type == PK){
        int nPk;
        vector<int> keys = findKeys(FILENAME);

        while(true){
          cout << "Set the new primary key: ";
          cin >> nPk;
          a.setPK(nPk);
          if(existKey(nPk, keys)){
            cout << "This primary key already exists, please try another." << endl;
          }else break;
        }

        cout << "Primary key modified successfully. " << endl << endl;
      }else if(type == STR){
        string s;
        cout << "Set the new value of the string: ";
        cin.ignore();
        getline(cin, s);
        a.setString(s);

        cout << "String modified successfully. "<< endl << endl;
      }else if(type == ARR){
        int index;
        ClassB *bArr;
        bArr = new ClassB[MAX];
        bArr = a.getClassBArr();

        while(true){
          cout << "Select the 1-based index of the array you want to modify (size = "
            << arrSize << "): ";
          cin >> index;

          if(index > 0 && index <= arrSize){
            double nValue;
            bool nStatus;

            cout << "Modifying B_" << index << " Object." << endl << endl;
            cout << "Set the new value of the double: ";
            cin >> nValue;
            cout << "Set the new value of the boolean: ";
            cin >> nStatus;

            bArr[index-1].setValue(nValue);
            bArr[index-1].setStatus(nStatus);
            break;
          }else{
            cout << "The index you entered is out of range, try another. " << endl;
          }
        }
      }
    }
    appendToFile(*&a, AUX_FILE);
  }

  fin.close();

  copyFromAuxToFile(AUX_FILE, FILENAME);

}

void eraseObjectFromFile(int key){
  ifstream fin;
  fin.open(FILENAME, ios::binary);

  int fileSize, objectSize, arrSize, pk, i, lng;
  string str;
  double value;
  bool status;
  char temp[STR_LNG+1];

  ClassB b[MAX];

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while (fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));
    fin.read( (char *) &lng, sizeof(int));
    fin.read(temp, lng+1);
    str = temp;
    fin.read( (char *) &arrSize, sizeof(int));
    for(i = 0; i<arrSize; ++i){
      fin.read( (char *) &value, sizeof(double));
      fin.read( (char *) &status, sizeof(bool));
      ClassB tb(value, status);
      b[i] = tb;
    }

    ClassA a(pk, str, b, arrSize);

    if(pk != key){
      appendToFile(*&a, AUX_FILE);
      cout << "Object erased successfully. " << endl << endl;
    }
  }

  fin.close();

  copyFromAuxToFile(AUX_FILE, FILENAME);

}

vector<int> findKeys(string filename){

  ifstream fin;
  fin.open(filename, ios::binary);

  int fileSize, objectSize, arrSize, pk, i, lng;
  string str;
  double value;
  bool status;

  vector<int> keys;

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while (fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));
    keys.push_back(pk);
    fin.read( (char *) &lng, sizeof(int));
    fin.seekg(lng+1, ios::cur);
    fin.read( (char *) &arrSize, sizeof(int));
    for(i = 0; i<arrSize; ++i){
      fin.read( (char *) &value, sizeof(double));
      fin.read( (char *) &status, sizeof(bool));
    }
  }
  fin.close();
  return keys;
}

bool fileExists(string filename){
  ifstream file(filename.c_str());
  return file.good();
}

bool existKey(int key, vector<int>keys){
  int sz = keys.size(), i;
  for(i=0; i<sz; ++i){
    if(keys[i] == key) return true;
  }
  return false;
}

ClassA findByKey(int key, string filename){
  ifstream fin;
  fin.open(filename, ios::binary);

  int fileSize, objectSize, arrSize, pk, i, lng;
  string str;
  double value;
  bool status;
  char temp[STR_LNG+1];

  ClassB b[MAX];

  fin.seekg(0, ios::end);
  fileSize = (int)fin.tellg();
  fin.seekg(0, ios::beg);

  while (fin.tellg() < fileSize){
    fin.read( (char *) &objectSize, sizeof(int));
    fin.read( (char *) &pk, sizeof(int));
    fin.read( (char *) &lng, sizeof(int));
    fin.read(temp, lng+1);
    str = temp;
    fin.read( (char *) &arrSize, sizeof(int));
    for(i = 0; i<arrSize; ++i){
      fin.read( (char *) &value, sizeof(double));
      fin.read( (char *) &status, sizeof(bool));
      ClassB tb(value, status);
      b[i] = tb;
    }
    if(pk == key){
      fin.close();
      ClassA a(pk, str, b, arrSize);
      return a;
    }
  }
  fin.close();
  ClassA a(pk, str, b, arrSize);
  return a;
}
