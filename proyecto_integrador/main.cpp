#include <iostream>

#include "Alumno.h"
#include "Menu.h"
#include "Buffer.h"
// #include "Index.h"
#include "helpers.h"

#define FILENAME "Alumnos.bin"

using namespace std;


int main(){
  // Main auxiliary variables
  int opt=0;
  Menu menu = Menu();
  Buffer buffer(FILENAME);
  Alumno auxUser;

  do{
    menu.mainMenu();
    cin >> opt;

    switch (opt){
      case 1:{
        setUser(auxUser);
        cout << auxUser.toString() << endl;
        string s=auxUser.toString();

        writeToBin(auxUser, FILENAME);

        break;
      }
      case 2:{
        break;
      }
      case 3:{
        readFromBin(FILENAME);
        buffer.printArray();
        // buffer.read();


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
