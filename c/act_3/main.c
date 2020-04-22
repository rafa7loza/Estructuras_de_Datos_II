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

#define FIELD_SIZE 40
#define REGISTER_SIZE 260
#define NUM_SIZE 5
#define BUFFER 80
#define REGISTERS 7

#define NEW_REGISTER '1'
#define READ_FROM_FILE '2'
#define EXIT '3'
#define DELIMITER '|'

struct Song{
  char title[FIELD_SIZE];
  char artists[FIELD_SIZE];
  char author[FIELD_SIZE];
  char distribuiter[FIELD_SIZE];
  char gender[FIELD_SIZE];
  char year[NUM_SIZE];
  char prices[NUM_SIZE];
};

// Defining the functions
void writeToFile(struct Song *song, int fd);
void readFromFile(int fd);
void readField(char *bf, char *arr, int *sz);
void initSong(struct Song *song);
void getString(char *arr, int bufferSize);
void concat(char *a, char *b);
int len(char *arr);
void printMenu();



char filename[BUFFER];


int main(){
  char extention[] = ".dat";
  struct Song song;
  int fileDescription;
  char opt;

  printf("Ingrese el nombre del archivo con el que desea trabajar: ");
  getString(filename, BUFFER);
  concat(filename, extention);

  // Opening the file
  fileDescription = open(filename,
    // Flags
    O_RDWR | O_CREAT,
    // Permisions
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if(fileDescription < 0){
    printf("Error al abrir el archivo. ( %d)\n", fileDescription);
    return 0;
  }

  do{
    printMenu();
    printf("Seleccione una opcion: ");
    opt = getchar();
    while ((getchar()) != '\n');
    switch (opt) {
      case NEW_REGISTER :{
        initSong(&song);
        writeToFile(&song, fileDescription);
        break;
      }
      case READ_FROM_FILE:{
        readFromFile(fileDescription);
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

  // Closing the file
  close(fileDescription);
  return 0;
}

void readFromFile(int fd){
  int cnt=0, songs=1;
  short register_size;
  char buffer[REGISTER_SIZE];

  // return to the beggining of the file
  lseek(fd, 0, 0);

  while(read(fd, &register_size, 2) > 0){

    int bytes = read(fd, buffer, register_size);

    if(bytes <= 0) return ;

    if(register_size >= REGISTER_SIZE)
      buffer[REGISTER_SIZE-1] = '\0';
    else
      buffer[register_size] = '\0';

    printf("\n====================\n");
    printf("Tamanio del registro: %d\n", register_size);
    printf("\tCancion # %d \n", songs++);

    int i = 0, pos;
    char aux[FIELD_SIZE];
    while(i < register_size){
      pos = 0;
      while(buffer[i] != DELIMITER){
        aux[pos++] = buffer[i++];
      }
      ++i;
      aux[pos] = '\0';

      switch (cnt%REGISTERS) {
        case 0:{
          printf("Titulo: ");
          break;
        }
        case 1:{
          printf("Artistas que la cantan: ");
          break;
        }
        case 2:{
          printf("Autor: ");
          break;
        }
        case 3:{
          printf("Sello musical o distribuidora: ");
          break;
        }
        case 4:{
          printf("Genero: ");
          break;
        }
        case 5:{
          printf("Anio de estreno: ");
          break;
        }
        case 6:{
          printf("Premios ganados: ");
          break;
        }
      }

      printf("%s\n", aux);
      ++cnt;

    }
    printf("\n====================\n");
  }
}

void writeToFile(struct Song *song, int fd){

  char newLine[] = "\n";
  char buffer[REGISTER_SIZE];
  int bf_len=0;

  // return to the end of the file
  lseek(fd, 0, 2);

  readField(buffer, song->title, &bf_len);
  readField(buffer, song->artists, &bf_len);
  readField(buffer, song->author, &bf_len);
  readField(buffer, song->distribuiter, &bf_len);
  readField(buffer, song->gender, &bf_len);
  readField(buffer, song->year, &bf_len);
  readField(buffer, song->prices, &bf_len);

  buffer[bf_len] = '\0';
  printf("%s\n", buffer);
  write(fd, &bf_len, 2);
  write(fd, (char *) buffer, bf_len);

  printf("%s successfully overwritten. \n", filename);
}

void readField(char *bf, char *arr, int *sz){
  int i=0;
  while(arr[i] != '\0') bf[(*sz)++] = arr[i++];
  bf[(*sz)++] = DELIMITER;
}

void initSong(struct Song *song){
  printf("Ingrese el titulo de la cancion: ");
  getString(song->title, REGISTER_SIZE);
  printf("Ingrese los artistas que cantan: ");
  getString(song->artists, REGISTER_SIZE);
  printf("Ingrese el autor: ");
  getString(song->author, REGISTER_SIZE);
  printf("Ingrese el sello musical o la distribuidora: ");
  getString(song->distribuiter, REGISTER_SIZE);
  printf("Ingrese el genero: ");
  getString(song->gender, REGISTER_SIZE);
  printf("Ingrese el anio de estreno: ");
  getString(song->year, NUM_SIZE);
  printf("Ingrese los premios obtenidos: ");
  getString(song->prices, NUM_SIZE);
}

void getString(char *arr, int bufferSize){
  int index=0;
  char c;
  while((c = getchar()) != '\n') {
    arr[index%bufferSize] = c;
    ++index;
  }
  if(index > bufferSize)
    arr[bufferSize] = '\0';
  else arr[index] = '\0';
}

void concat(char *a, char *b){
  int sz = strlen(a);
  for(int i=0; i<strlen(b); ++i){
    a[sz+i] = b[i];
  }
  a[sz+strlen(b)] = '\0';
}

int len(char *arr){
  int i, result=0;
  while(arr[i++] != '\0') ++result;
  return result;
}

void printMenu(){
  printf("\n1) Capturar cancion.\n2) Canciones del archivo.\n3) Salir.\n");
}
