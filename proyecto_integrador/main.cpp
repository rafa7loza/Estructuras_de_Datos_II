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

  loader.fileToGraph(socialNetwork, buffer);
  cout << socialNetwork.getVertexCount()<< endl;

  do{
    menu.mainMenu();
    cin >> opt;

    switch (opt){
      case 1:{
        int key = buffer.findValidKey();
        // cout << "Valid key gefunden " << key << "! ! !" << endl;
        setUser(auxUser, key);
        // cout << "User added to the file" << endl;
        socialNetwork.addUser(auxUser);
        // cout << "User added to the Graph successfully ! " << endl;

        break;
      }
      case 2:{
        // Find the user by primary Key
        int userOption, pk, auxOption;
        string changeAttr;
        Alumno *currentUser;

        cout << "Ingrese la llave primaria del usuario: ";
        cin >> pk;
        currentUser = socialNetwork.findUser(pk);

        if(currentUser == nullptr){
          cout << "No existen usuarios en la red con ese identificador . . ." << endl;
          continue;
        }

        cout << currentUser->toString() << endl;
        menu.accessUser();
        cin >> userOption;
        // cin.ignore();

        switch (userOption) {
          case 1:{
            menu.modifyUser();
            cin >> auxOption;
            switch (auxOption) {
              case 1:{
                cout << "Ingrese el nuevo nombre: ";
                cin.ignore();
                getline(cin, changeAttr);
                currentUser->setNames(changeAttr);
                break;
              }
              case 2:{
                cout << "Ingrese los nuevos apellidos: ";
                cin.ignore();
                getline(cin, changeAttr);
                currentUser->setLastNames(changeAttr);
                break;
              }
              case 3:{
                cout << "Ingrese el nuevo correo: ";
                cin.ignore();
                getline(cin, changeAttr);
                currentUser->setEmailAdrress(changeAttr);
                break;
              }
              case 4: {
                cout << "Ingrese la nueva contraseña: ";
                cin.ignore();
                getline(cin, changeAttr);
                currentUser->setPassword(changeAttr);
                break;
              }
              default: {
                cout << "Opción inválida . . ."<< endl << endl;
                break;
              }
            }
            cout << currentUser->toString() << endl;
            break;
          }
          case 2:{
            break;
          }default:{
            cout << "Opción inválida . . ."<< endl << endl;
            break;
          }
        }
        break;
      }
      case 3:{
        // readFromBin(FILENAME);
        // buffer.printArray();
        // buffer.read();

        // socialNetwork.printVertex();

        Alumno* arr;
        arr = socialNetwork.getUsers();

        for(int i=0; i<socialNetwork.getVertexCount(); ++i){
          cout << arr[i].toString() << endl;
        }
        // readFromBin(FILENAME);

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
