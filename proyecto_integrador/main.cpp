#include <iostream>

#include "Alumno.h"
#include "Loader.h"
#include "Menu.h"
#include "Buffer.h"
#include "helpers.h"
#include "Graph.h"
using namespace std;

const string FILENAME = "Alumnos.bin";

void modifyUser(Menu m, Alumno* currentUser);
void showFriends(Alumno* currentUser, Graph network);
void showRequests(Alumno *currentUser, Graph network);
void sendFriendRequest(int currentUserKey, Graph &network);

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
        int userOption, pk;
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

        switch (userOption) {
          case 1:{
            modifyUser(menu, currentUser);
            cout << currentUser->toString() << endl;
            break;
          }
          case 2:{
            showFriends(currentUser, socialNetwork);
            break;
          }
          case 3:{
            sendFriendRequest(currentUser->getPK(), socialNetwork);
            break;
          }
          case 4:{
            break;
          }
          case 5:{
            showRequests(currentUser, socialNetwork);
            break;
          }
          default:{
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

        socialNetwork.printVertex();

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


void modifyUser(Menu m, Alumno* currentUser){
  m.modifyUser();
  int auxOption;
  string changeAttr;
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
}

void showFriends(Alumno* currentUser, Graph network){
  int n = currentUser->getFriendsCounter();
  if(n == 0){
    cout << "El usuario no tiene amigos :(" << endl;
  }else{
    int *friends;
    friends = new int[n];
    friends = currentUser->getFriends();
    for(int i=0; i<n; ++i){
      Alumno* user;
      user = network.findUser(friends[i]);
      cout << user->toString() << endl;
    }
  }
}

void showRequests(Alumno *currentUser, Graph network){
  int n = currentUser->getRequestsCounter();
  if(n==0){
    cout << "No hay solicitudes de amistad." << endl;
  }else{
    int *requests;
    requests = new int[n];
    requests = currentUser->getRequests();
    for(int i=0; i<n; ++i){
      Alumno* user;
      user = network.findUser(requests[i]);
      cout << "El usuario " << user->toString()
        << " te ha enviado una solicitud de amistad. " << endl;
    }
  }
}

void sendFriendRequest(int currentUserKey, Graph &network){
  int userKey;
  Alumno *user;

  cout << "Ingrese el identidicador del usuario: ";
  cin >> userKey;

  user = network.findUser(userKey);

  // validate if they are already friends
  // bool areFriends(Alumno a, Alumno b)

  if(user == nullptr){
    cout << "No se encontró el identidicador del usuario. "<< endl;
    return;
  }

  user->addRequest(currentUserKey);
  network.makeFriendRequest(currentUserKey, userKey);

  cout << "Se ha enviado la solicitud correctamente. " << endl;
}
