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
#include <math.h>

#include "helper.h"
#include "constants.h"
#include "runner.h"
#include "primary_index.h"
#include "secondary_index.h"


// Defining the function
void addToIndex(struct Primary_Index *index, struct Runner *runner, int *regs);

void bubbleSort(struct Primary_Index *arr, int len);
void swapIndex(struct Primary_Index *a, struct Primary_Index *b);

void getRegisters(int fd, int *value);
void updateRegisters(int fd, int value);

void writeHeader(int fd);
void printMenu();
void secondaryMenu();

char file_name[BUFFER];
char file_name_extension[BUFFER];

int main(){
  struct Runner runner;
  struct Primary_Index index[INDEX_SIZE];

  struct Secondary_Index name_index[INDEX_SIZE];
  struct Secondary_Index city_index[INDEX_SIZE];
  struct Secondary_Index nationality_index[INDEX_SIZE];

  char indexFileName[BUFFER];

  char indexExtension[] = "_primary_index.dat";
  int key, positionInFile;
  int main_file_description, index_file_description;
  int fileSize, registers=0;
  char opt;

  printf("Ingrese el nombre del archivo con el que desea trabajar: ");
  getString(file_name, BUFFER);


  fillEmptyString(file_name, indexFileName);
  copyString(file_name, file_name_extension);

  concat(file_name_extension, EXTENSION);
  concat(indexFileName, indexExtension);

  // Opening the file
  main_file_description = openFile(file_name_extension);
  index_file_description = openFile(indexFileName);

  if(main_file_description < 0 || index_file_description < 0){
    printf("Error al abrir los archivos. (%d) (%d)\n", main_file_description, index_file_description);
    return 0;
  }

  fileSize = getFileSize(main_file_description);

  if(fileSize == 0) {
    printf("Creating the header description.\n");
    writeHeader(main_file_description);
  }

  getRegisters(main_file_description, &registers);
  printf("Numero de registros: %d\n", registers);

  fileSize = getFileSize(index_file_description);

  if(fileSize > 0) loadIndex(*&index, index_file_description);

  // Secondaries index implementation
  int name_index_size = loadSecondaryIndex(name_index, file_name, NAME);
  int city_index_size = loadSecondaryIndex(city_index, file_name, CITY);
  int nationality_index_size = loadSecondaryIndex(nationality_index, file_name, NATIONALITY);

  do{
    printMenu();
    printf("Seleccione una opcion: ");
    opt = getchar();
    // while ((getchar()) != '\n');
    clean;
    switch (opt) {
      case NEW_REGISTER :{
        initRunner(&runner);
        if(!runner.valid)
          printf("\nEl registro no se ha podido guardar, intentelo de nuevo.\n");
        else{
          // Adding secondary index
          int key = charToInt(runner.number);
          addSecondaryIndex(&name_index[registers], runner.name, key);
          addSecondaryIndex(&city_index[registers], runner.city, key);
          addSecondaryIndex(&nationality_index[registers], runner.nationality, key);

          addToIndex(&index[registers], &runner, &registers);
          bubbleSort(index, registers);

          writeToFile(&runner, main_file_description);
          updateRegisters(main_file_description, registers);

        }
        printf("\nFile size: %d\n", getFileSize(main_file_description));
        break;
      }
      case READ_FROM_FILE:{
        readLastFromFile(&runner, main_file_description);
        break;
      }
      case FIND:{
        char aux[BUFFER];

        // bubbleSort(index, registers);
        printf("Ingrese el numero del corredor que desea visualizar: ");
        getString(aux, BUFFER);
        key = charToInt(aux);
        positionInFile = getPosition(key, index, registers);
        printf("Position: %d\n", positionInFile);
        findRunner(&runner, positionInFile, main_file_description);
        if(runner.valid == 0)
          printf("El numero buscado no se encuentra, intente con otro numero.\n");
        else
          printRunner(&runner);

        break;
      }
      case SHOW_KEYS:{
        // bubbleSort(index, registers);
        showKeys(index, registers);
        break;
      }
      case EXIT:{
        saveIndex(index, registers, &index_file_description, indexFileName);

        // Save secondary index
        saveSecondaryIndex(name_index, registers, file_name, NAME);
        saveSecondaryIndex(city_index, registers, file_name, CITY);
        saveSecondaryIndex(nationality_index, registers, file_name, NATIONALITY);

        printf("\nTerminando programa.\n");
        break;
      }
      case PRINT_INDEX: {
        printAll(index, registers);
        break;
      }
      case SHOW_SECONDARY_INDEX:{
        printf("\tName index:\n");
        showAll(name_index, registers, "Nombre");
        printf("=========================\n");

        printf("\tCity index:\n");
        showAll(city_index, registers, "Ciudad");
        printf("=========================\n");

        printf("\tNationality index:\n");
        showAll(nationality_index, registers, "Nacionalidad");
        printf("=========================\n");
        break;
      }
      case FIND_BY_SECONDARY: {
        char aux[BUFFER];
        int key=-2;
        char sec_aux;

        secondaryMenu();
        sec_aux = getchar();
        clean;

        switch (sec_aux) {
          case FIND_NAME:{
            printf("Ingese el nombre del corredor: ");
            getString(aux, BUFFER);
            key = getKey(aux, name_index, registers);
            break;
          }
          case FIND_CITY:{
            printf("Ingese la ciudad del corredor: ");
            getString(aux, BUFFER);
            key = getKey(aux, city_index, registers);
            break;
          }
          case FIND_NATIONALITY:{
            printf("Ingese la nacionalidad del corredor: ");
            getString(aux, BUFFER);
            key = getKey(aux, nationality_index, registers);
            break;
          }
          default:{
            printf("Opcion invalida. \n");
            break;
          }
        }

        if(key == -1){
          printf("No se encuentra algun registro con estos datos.\n");
        }else if(key >= 0){
          positionInFile = getPosition(key, index, registers);
          printf("Position: %d\n", positionInFile);
          findRunner(&runner, positionInFile, main_file_description);
          printRunner(&runner);
        }

        break;
      }

      default: {
        printf("\nOpcion no valida . . . \n");
        break;
      }
    }
  }while(opt != EXIT);

  close(main_file_description);
  close(index_file_description);
  return 0;
}

void addToIndex(struct Primary_Index *index, struct Runner *runner, int *regs){
  index->position = 32 + (REGISTER_SIZE * (*regs));
  index->pk = charToInt(runner->number);
  copyString(runner->time, index->time);
  ++(*regs);
}

void writeHeader(int fd){
  lseek(fd, 0, SEEK_SET);
  int registers = 0;
  char fill[] = "******************************";
  write(fd, &registers, 2);
  write(fd, (char*) fill, strlen(fill));
}

void getRegisters(int fd, int *value){
  lseek(fd, 0, SEEK_SET);
  read(fd, *&value, 2);
}

void updateRegisters(int fd, int value){
  lseek(fd, 0, SEEK_SET);
  write(fd, &value, 2);
}

void swapIndex(struct Primary_Index *a, struct Primary_Index *b){
  struct Primary_Index temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(struct Primary_Index *arr, int len){
  int j, i;
  for(i=0; i < len-1; ++i){
    for(j=0; j<len-i-1; ++j){
      if(arr[j].pk > arr[j+1].pk)
        swapIndex(&arr[j], &arr[j+1]);
    }
  }
}

void printMenu(){
  printf("\n%c) Capturar corredor.", NEW_REGISTER);
  printf("\n%c) Ver ultimo registro del archivo.", READ_FROM_FILE);
  printf("\n%c) Buscar corredor por su numero.", FIND);
  printf("\n%c) Mostrar todos los numeros.", SHOW_KEYS);
  printf("\n%c) Buscar por llave secundaria.", FIND_BY_SECONDARY);
  printf("\n%c) Mostrar llaves secundarias.", SHOW_SECONDARY_INDEX);
  printf("\n%c) Salir.\n", EXIT);
}

void secondaryMenu(){
  printf("\n%c) Buscar por nombre.", FIND_NAME);
  printf("\n%c) Buscar por ciudad.", FIND_CITY);
  printf("\n%c) Buscar por nacionalidad.", FIND_NATIONALITY);
  printf("\nSeleccine una opcion: ");
}
