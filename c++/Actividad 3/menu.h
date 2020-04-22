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
  void modifyClassB();
};

Menu::Menu(){}

void Menu::home(){
  cout << endl << "1) Insert element to file. " << endl
    << "2) Erase element from file (PK)." << endl
    << "3) Show element from file (PK)." << endl
    << "4) Modify element from file (PK)." << endl
    << "5) Show all elements from file." << endl
    << "6) Exit." << endl << endl;
    cout << "Select an option: ";
}

void Menu::insert(){
  cout << endl << "1) Insert at the end." << endl
    << "2) Insert at the start. " << endl;
  cout << "Select an option: ";
}

void Menu::modifyClassA(){
  cout << endl << "1) Modify the string." << endl
    << "2) Modify the primary key." << endl
    << "3) Modify an element of the array." << endl;
    cout << "Select an option: ";
}

void Menu::modifyClassB(){
  cout << endl << "1) Modify the boolean value." << endl
    << "2) Modify the double value. " << endl;
  cout << "Select an option: ";
}

#endif
