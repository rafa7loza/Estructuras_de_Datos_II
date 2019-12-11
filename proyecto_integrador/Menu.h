#ifndef MENU_H
#define MENU_H

#include <iostream>

using namespace std;

class Menu{
public:
  Menu();
  void mainMenu();
  void accessUser();
  void modifyUser();
  void friendRequests();

private:

};
/*
enum MainEnums{
  ADD, ACCESS, SHOW_NET, SHOW_LIST
}
*/

Menu::Menu(){}

void Menu::mainMenu(){
  cout << "\n\tMENU PRINCIPAL" << endl
    << "1) Agregar Usuario." << endl
    << "2) Acceder Usuario." << endl
    << "3) Mostrar red." << endl
    << "4) Mostrar lista invertida."<< endl
    << "5) Salir." << endl << endl
    << "Seleccione una opción: ";
}

void Menu::accessUser(){
  cout << "\n1) Modificar usuario." <<endl
   << "2) Mostrar lista de amigos." << endl
   << "3) Agregar amigo." << endl
   << "4) Eliminar amigo." << endl
   << "5) Ver solicitudes de amistad." << endl
   << "6) Eliminar cuenta." << endl
   << "7) Agregar/Eliminar intereses." << endl << endl
   << "Seleccione una opción: ";
}

void Menu::friendRequests(){
  cout << "\n1) Aceptar solicitud." << endl
    << "2) Rechazar solicitud." << endl << endl
    << "Seleccione una opción: ";
}

void Menu::modifyUser(){
  // Modificacion de usuarios listando sus atributos
  // Queda pendiente para cuando estén definidos sus atributos
  cout << "1) Cambiar nombres." << endl
    << "2) Cambiar Apellidos. " << endl
    << "3) Cambiar correo." << endl
    << "4) Cambiar contraseña." << endl << endl
    << "Seleccione una opción: ";
}

#endif
