#include <iostream>
#include <vector>
#include <fstream>
#include "ClassA.h"

#define ARR_MAX 5
#define FILENAME "lista.txt"
#define TEMP "temp.txt"
#define DELIMITER '|'
#define LINE "==================================="

using namespace std;

void printMenuPrincipal();
void printMenuAgregar();
void printMenuModificar();
bool addEnd(int key, string str, int arr[]);
void readAll();
vector<int> getKeys();
bool isValidKey(int currentKey);
bool findKey(int key, vector<int> keys);
void copyToTempFile(int key,bool erase);
bool addStart(int key, string cadena, int arr[]);
void appendFromFile(bool append);
void saveObject(ClassA *obj, bool append);
void eraseElement(int key);
void editElement(int key);

int main(){
  int opt, key, arr[5];
  string str;

  do{
    printMenuPrincipal();
    cin >> opt;
    switch (opt) {
      case 1:{
        int aux;

        do{
          printMenuAgregar();
          cin >> aux;
          if(aux != 1 && aux != 2){
            cout << "Ingresó una opción incorrecta, intentelo de nuevo" << endl;
          }else{
            break;
          }
        }while(true);

        cout << "Ingrese la llave primaria del objeto: ";
        cin >> key;
        cout << "Ingrese la cadena del objeto: ";
        cin.ignore();
        getline(cin, str);

        for(int i=0; i<ARR_MAX; ++i){
          cout << "Ingrese el elemento " << i+1 << " del arreglo: " << endl;
          cin >> arr[i];
        }

        if(aux == 1 && addEnd(key, str, arr)){
          cout << "El objeto se ha agregado correctamente al final." << endl;
        }else if(aux == 2 && addStart(key, str, arr)){
          cout << "El objeto se ha agregado correctamente al inicio." << endl;
        }else{
          cout << "La llave primaria agregada ya existe, el elemento no se ha guardado" << endl;
        }
        break;
      }
      case 2:{
        int key;
        cout << "Ingrese la llave primaria del objeto que desea eliminar"
          << endl;
        cin >> key;
        if(!isValidKey(key)){
          eraseElement(key);
        }else{
          cout << "La llave primaria ingresada no existe." << endl;
        }
        break;
      }
      case 3:{
        int key;
        cout << "Ingrese la llave primaria del objeto que desea modificar"
          << endl;
        cin >> key;
        if(!isValidKey(key)){
          editElement(key);
        
        }else{
          cout << "La llave primaria ingresada no existe." << endl;
        }
        break;
      }
      case 4:{
        readAll();
        break;
      }
      case 5:{
        cout << "Terminando el programa . . ." << endl;
        break;
      }
      default:{
        cout << "Ingresó una opción incorrecta, intentelo de nuevo" << endl;
        break;
      }
    }
  }while(opt != 5);

  return 0;
}

void printMenuPrincipal(){
  cout << "\t\tMenu" << endl
    << "1) Agregar." << endl
    << "2) Eliminar por llave primaria." << endl
    << "3) Modificar por llave primaria." << endl
    << "4) Mostrar todos." << endl
    << "5) Salir" << endl
    << "\nIngrese una opción: ";
}

void printMenuAgregar(){
  cout << "1) Agregar al final." << endl
    << "2) Agregar al inicio." << endl
    << "\nIngrese una opción: ";
}

void printMenuModificar(){
  cout << "1) Entero" << endl
    << "2) Cadena" << endl
    << "3) Arreglo" << endl;
}

vector<int> getKeys(){
  vector<int> keys;
  ifstream fin(FILENAME);
  string key, dummy;
  while (getline(fin, key, DELIMITER)
    && getline(fin, dummy, DELIMITER)
    && getline(fin, dummy, DELIMITER)){
      keys.push_back(stoi(key));
  }
  fin.close();
  return keys;
}

bool findKey(int key, vector<int> keys){
  int sz = keys.size();
  for(int i=0; i<sz; ++i){
    if(keys[i] == key) return true;
  }
  return false;
}

bool isValidKey(int currentKey){
  vector<int> keys = getKeys();
  if(findKey(currentKey, keys)){
    return false;
  }else{
    return true;
  }
}

bool addEnd(int key, string cadena, int arr[]){
  if(!isValidKey(key)){
    return false;
  }
  ClassA *obj;
  obj = new ClassA(key, cadena, arr);
  saveObject(obj, true);
  return true;
}

bool addStart(int key, string cadena, int arr[]){
  if(!isValidKey(key)){
    return false;
  }

  ClassA *obj;
  obj = new ClassA(key, cadena, arr);

  copyToTempFile(-1, false);
  saveObject(obj, false);
  appendFromFile(true);
  remove(TEMP);

  return true;
}

void eraseElement(int key){
  copyToTempFile(key, true);
  appendFromFile(false);
  remove(TEMP);
}

void editElement(int key){
  int aux;
  string s1, s2, s3;
  ifstream fin(FILENAME);
  ofstream fout;
  fout.open(TEMP);

  do{
    printMenuModificar();
    cout << "Ingrese el elemento que desea modificar: ";
    cin >> aux;

    switch (aux) {
      case 1:{
        int temp;
        cout << "Ingrese el valor de la nueva llave primaria: ";
        cin >> temp;

        if(!isValidKey(temp)){
          cout << "La llave ingresada ya existe." << endl;
          key = -1;
        }

        while (getline(fin, s1, DELIMITER) &&
          getline(fin, s2, DELIMITER) &&
          getline(fin, s3, DELIMITER)){
            if(stoi(s1) == key){
              fout << endl << temp << DELIMITER << s2 << DELIMITER << s3 << DELIMITER;
              continue;
            }
            fout << s1 << DELIMITER << s2 << DELIMITER << s3 << DELIMITER;
          }
        break;
      }
      case 2:{
        string temp;
        cout << "Ingrese el valor de la nueva cadena: ";
        cin.ignore();
        getline(cin, temp);

        while (getline(fin, s1, DELIMITER) &&
          getline(fin, s2, DELIMITER) &&
          getline(fin, s3, DELIMITER)){
            if(stoi(s1) == key){
              fout << s1 << DELIMITER << temp << DELIMITER << s3 << DELIMITER;
              continue;
            }
            fout << s1 << DELIMITER << s2 << DELIMITER << s3 << DELIMITER;
          }
        break;
      }
      case 3:{
        int temp[5];

        for(int i=0; i<ARR_MAX; ++i){
          cout << "Ingrese el elemento " << i+1 << " del arreglo: " << endl;
          cin >> temp[i];
        }

        while (getline(fin, s1, DELIMITER) &&
          getline(fin, s2, DELIMITER) &&
          getline(fin, s3, DELIMITER)){
            if(stoi(s1) == key){
              fout << s1 << DELIMITER << s2 << DELIMITER;
              for(int i=0; i<ARR_MAX; ++i){
                fout << temp[i];
                if(i<4){
                   fout << " ";
                }
              }
              fout << DELIMITER;
              continue;
            }
            fout << s1 << DELIMITER << s2 << DELIMITER << s3 << DELIMITER;
          }
        break;
      }
      default:{
        cout << "Ingresó una opción incorrecta, intentelo de nuevo" << endl;
        break;
      }
    }
  }while(aux < 1 || aux > 3);
  fout.close();
  fin.close();

  appendFromFile(false);
  remove(TEMP);

}

void appendFromFile(bool append){
  ofstream fout;
  ifstream fin(TEMP);
  string s;
  if(append){
    fout.open(FILENAME, ios_base::app);
  }else{
    fout.open(FILENAME);
  }
  while (getline(fin, s)){
    fout << s << endl;
  }
  fout.close();
  fin.close();
}

void copyToTempFile(int key, bool erase){
  ifstream fin(FILENAME);
  ofstream fout;
  string s1;

  fout.open(TEMP);

  if(!erase){
    while (getline(fin, s1)){
      fout << s1 << endl;
    }
  }else{
    string s2, s3;
    while (getline(fin, s1, DELIMITER) &&
      getline(fin, s2, DELIMITER) &&
      getline(fin, s3, DELIMITER)) {
      if(stoi(s1) == key){
        continue;
      }else{
        fout << s1 << DELIMITER << s2 << DELIMITER << s3 << DELIMITER;
      }
    }
    fout.close();
    fin.close();
  }
}

void readAll(){
  ifstream fin(FILENAME);
  string s1, s2, s3;
  cout << endl << LINE << endl;
  while(getline(fin, s1, DELIMITER) &&
  getline(fin, s2, DELIMITER) &&
  getline(fin, s3, DELIMITER)) {
    fin.ignore();
    cout << "Llave primaria: " << s1 << endl
      << "Cadena: " << s2 << endl
      << "Arreglo: " << s3 << endl
      << LINE << endl;
  }

  fin.close();
}

void saveObject(ClassA *obj, bool append){
  ofstream fout;
  if(append){
    fout.open(FILENAME, ios_base::app);
  }else{
    fout.open(FILENAME);
  }

  fout << obj->getPrimaryKey() << DELIMITER;
  fout << obj->getCadena() << DELIMITER;
  int *a;
  a = obj->getArray();
  for(int i=0; i<ARR_MAX; ++i){
    fout << a[i];
    if(i < ARR_MAX-1){
      fout << " ";
    }
  }

  fout << DELIMITER << endl;
  fout.close();
}
