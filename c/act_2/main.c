/*******************

Nombre:       Loza Arechiga Andre Rafael
Codigo:       214589252
Asignatura:   Seminario de Solucion de Problemas
              De Estructuras de Datos 2
Seccion:      D18
Profesor:     Guerrero Segura Ramirez Miguel Angel

********************/


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "helper.h"

#define MAX 100
#define MAX_BUFFER_SIZE 10000
#define BUFFER_SIZE 100
#define REGISTER_SIZE 50
// #define RFC_SIZE 13
// #define ZIP_SIZE 5
#define NEW_REGISTER '1'
#define SAVE_TO_FILE '3'
#define READ_FROM_FILE '2'
#define EXIT '4'
#define REGISTERS 7

struct User{
  char clientName[REGISTER_SIZE];
  char RFC[REGISTER_SIZE];
  char address[REGISTER_SIZE];
  char province[REGISTER_SIZE];
  char zipCode[REGISTER_SIZE];
  char diagnose[REGISTER_SIZE];
  char therapistName[REGISTER_SIZE];
};

void getString(char *c);
void initUser(struct User *user);
void printFields(struct User *user);
void concat(char *a, char *b);
void writeToFile();
void readFromFile();

char filename[MAX];
// int fileDescription;

int main(){

  struct User user[MAX];
  int index=0, fileDescription;
  char opt;

  printf("Ingrese el nombre del archivo con el que desea trabajar: ");
  getString(filename);
  concat(filename, ".txt");

  do{
    menu();
    printf("Seleccione una opcion: ");
    opt = getchar();
    while ((getchar()) != '\n');
    switch (opt) {
      case NEW_REGISTER :{
        initUser(&user[index++]);
        // writeToFile(user, index);
        break;
      }
      case SAVE_TO_FILE:{
        writeToFile(user, index);
        break;
      }
      case READ_FROM_FILE:{
        writeToFile(user, index);
        readFromFile();

        // for(int i=0; i<index; ++i){
        //   printf("====================\n");
        //   printFields(&user[i]);
        //   printf("====================\n");
        //
        // }
        break;
      }
      case EXIT:{
        printf("Terminando programa.\n");
        break;
      }
      default: {
        printf("Opcion no valida . . . \n");
        break;
      }
    }
  }while(opt != EXIT);


  return 0;
}

void getString(char *arr){
  int index=0;
  char c;

  while((c = getchar()) != '\n') arr[index++] = c;
  arr[index] = '\0';
}

void initUser(struct User *user){
  printf("Ingrese el nombre del cliente: ");
  getString(user->clientName);
  printf("Ingrese su RFC: ");
  getString(user->RFC);
  printf("Ingrese su direccion: ");
  getString(user->address);
  printf("Ingrese su estado de origen: ");
  getString(user->province);
  printf("Ingrese su codigo postal: ");
  getString(user->zipCode);
  printf("Ingrese la lesion diagnosticada: ");
  getString(user->diagnose);
  printf("Ingrese el nombre del fisioterapeuta asignado: ");
  getString(user->therapistName);
}

void printFields(struct User *user){
  // int index=0;
  // while(user->clientName[index] != '\0') printf("%c", user->clientName[index++]);
  // printf("\n");
  printf("Nombre del paciente: %s\n", user->clientName);
  // index=0;
  // while(user->RFC[index] != '\0') printf("%c", user->RFC[index++]);
  // printf("\n");
  printf("RFC: %s\n", user->RFC);
  // index=0;
  // while(user->address[index] != '\0') printf("%c", user->address[index++]);
  // printf("\n");
  printf("Direccion: %s\n", user->address);
  // index=0;
  // while(user->province[index] != '\0') printf("%c", user->province[index++]);
  // printf("\n");
  printf("Estado: %s\n", user->province);
  // index=0;
  // while(user->zipCode[index] != '\0') printf("%c", user->zipCode[index++]);
  // printf("\n");
  printf("Codigo postal: %s\n", user->zipCode);
  // index=0;
  // while(user->diagnose[index] != '\0') printf("%c", user->diagnose[index++]);
  // printf("\n");
  printf("Diagnostico: %s\n", user->diagnose);
  // index=0;
  // while(user->therapistName[index] != '\0') printf("%c", user->therapistName[index++]);
  // printf("\n");
  printf("Nombre del fisioterapeuta: %s\n", user->therapistName);
}

void concat(char *a, char *b){
  int len = strlen(a);
  for(int i=0; i<strlen(b); ++i){
    a[len+i] = b[i];
  }
  a[len+strlen(b)] = '\0';
}

void readFromFile(){
  char bf[MAX_BUFFER_SIZE];

  int fileDescription = open(filename, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if(fileDescription < 0){
    printf("Error al abrir el archivo. (%d)\n", fileDescription);
    return;
  }

  // char bf[MAX_BUFFER_SIZE];
  read(fileDescription, (char*) bf, MAX_BUFFER_SIZE);
  printf("%s\n", bf);

  int i = pos = cnt = 0;
  char aux[BUFFER_SIZE];
  printf("\n====================\n");
  while(bf[i] != EOF){

    if(bf[i] == '|' || bf[i] == '\n'){
      for(int j=0; j<i-pos; ++j){
        aux[j] = bf[pos+j];
      }
      aux[i-pos] = '\0';

      switch (cnt%REGISTERS) {
        case 0:{
          printf("Nombre paciente: ");
          break;
        }
        case 1:{
          printf("RFC: ");
          break;
        }
        case 2:{
          printf("Domicilio: ");
          break;
        }
        case 3:{
          printf("Estado: ");
          break;
        }
        case 4:{
          printf("Codigo Postal: ");
          break;
        }
        case 5:{
          printf("Diagnostico: ");
          break;
        }
        case 6:{
          printf("Nombre de fisioterapeuta: ");
          break;
        }
      }

      printf("%s\n", aux);
      pos = i+1;
      ++cnt;
    }
    if(bf[i] == '\n') printf("====================\n");
    ++i;

  }
}

void writeToFile(struct User *user, int len){

  printf("Escribiendo en el archivo %s . . .\n", filename);

  int fileDescription = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if(fileDescription < 0){
    printf("Error al abrir el archivo. (%d)\n", fileDescription);
    return ;
  }

  char delimiter[] = "|";
  char newLine[] = "\n";

  for(int i=0; i<len; ++i){
    write(fileDescription, (char*) user[i].clientName, strlen(user[i].clientName));
    write(fileDescription, (char*) delimiter, strlen(delimiter));
    write(fileDescription, (char*) user[i].RFC, strlen(user[i].RFC));
    write(fileDescription, (char*) delimiter, strlen(delimiter));
    write(fileDescription, (char*) user[i].address, strlen(user[i].address));
    write(fileDescription, (char*) delimiter, strlen(delimiter));
    write(fileDescription, (char*) user[i].province, strlen(user[i].province));
    write(fileDescription, (char*) delimiter, strlen(delimiter));
    write(fileDescription, (char*) user[i].zipCode, strlen(user[i].zipCode));
    write(fileDescription, (char*) delimiter, strlen(delimiter));
    write(fileDescription, (char*) user[i].diagnose, strlen(user[i].diagnose));
    write(fileDescription, (char*) delimiter, strlen(delimiter));
    write(fileDescription, (char*) user[i].therapistName, strlen(user[i].therapistName));
    write(fileDescription, (char*) newLine, strlen(newLine));
  }
  printf("Se ha escrito exitosamente en el archivo.\n");

}
