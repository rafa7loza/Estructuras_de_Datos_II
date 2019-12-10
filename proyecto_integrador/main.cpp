#include <iostream>

#include "Alumno.h"
#include "Loader.h"
#include "Menu.h"
#include "Buffer.h"
#include "helpers.h"
#include "Graph.h"
using namespace std;

const string FILENAME = "Alumnos.bin";

int main(){
  // Main auxiliary variables
  int opt=0;
  Menu menu = Menu();
  Buffer buffer(FILENAME);
  Loader loader(FILENAME);
  Alumno auxUser;
  Graph socialNetwork;

  do{
    menu.mainMenu();
    cin >> opt;

    switch (opt){
      case 1:{
        int key = buffer.findValidKey();
        cout << "Valid key gefunden " << key << "! ! !" << endl;
        setUser(auxUser, key);
        // cout << auxUser.toString() << endl;

        // writeToBin(auxUser, FILENAME);
        // cout << "User added to the file" << endl;
        socialNetwork.addUser(auxUser);
        // cout << "User added to the Graph successfully ! " << endl;

        break;
      }
      case 2:{
        break;
      }
      case 3:{
        // readFromBin(FILENAME);
        // buffer.printArray();
        // buffer.read();

        // socialNetwork.printVertex();

        /*Alumno* arr;
        arr = socialNetwork.getUsers();

        for(int i=0; i<socialNetwork.getVertexCount(); ++i){
          cout << arr[i].toString() << endl;
        }*/
        readFromBin(FILENAME);

        break;
      }
      case 4:{
        break;
      }
      case 5:{
        loader.graphToFile(socialNetwork);
        cout << "Saliendo del programa . . ." << endl;
        break;
      }
      default:{
        cout << "Opción incorrecta, intente de nuevo. " << endl;
        break;
      }
    }
  }while(opt != 5);
}
