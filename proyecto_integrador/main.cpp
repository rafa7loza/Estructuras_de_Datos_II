#include <iostream>

#include "Alumno.h"
#include "Menu.h"

using namespace std;

// Auxiliary functions
void setUser(Alumno &a);
void showUser();

int main(){
  // Main auxiliary variables
  int opt=0;
  Menu menu = Menu();
  Alumno auxUser;

  do{
    menu.mainMenu();
    cin >> opt;

    switch (opt){
      case 1:{
        setUser(auxUser);
        cout << auxUser.toString() << endl;
        break;
      }
      case 2:{
        break;
      }
      case 3:{
        break;
      }
      case 4:{
        break;
      }
      case 5:{
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

void setUser(Alumno &a){
  string aux;

  cout << "Ingrese el nombre o los nombres del usuario: ";
  cin.ignore();
  getline(cin, aux);
  a.setNames(aux);

  cout << "Ingrese el o los apellidos del usuario: ";
  getline(cin, aux);
  a.setLastNames(aux);

  cout << "Ingrese la dirección de correo: ";
  getline(cin, aux);
  a.setEmailAdrress(aux);

  cout << "Ingrese la contraseña: ";
  getline(cin, aux);
  a.setPassword(aux);
}

void showUser(){

}
