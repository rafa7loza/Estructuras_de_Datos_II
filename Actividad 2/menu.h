#ifndef MENU_H
#define MENU_H

#include <iostream>

using namespace std;

class Menu{
public:
  Menu();
  void home();
  void insert();
  void modifyClassA();
};

Menu::Menu(){}

void Menu::home(){
  cout << endl << "\t\tMenu" << endl
    << "1) Insert object to file." << endl
    << "2) Erase an object (PK)." << endl
    << "3) Show a single object (PK)." << endl
    << "4) Modify object (PK)." << endl
    << "5) Show all objects in file." << endl
    << "6) Exit." << endl
    << "Select an option: ";
}

void Menu::insert(){
  cout << endl << "1) Insert at the end." << endl
    << "2) Insert at the start. " << endl;
  cout << "Select an option: ";
}

void Menu::modifyClassA(){
  cout << endl << "1) Modify the string." << endl
    << "2) Modify the primary key." << endl
    << "Select an option: ";
}


#endif
