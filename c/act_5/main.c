/*******************

Nombre:       Loza Arechiga Andre Rafael
Codigo:       214589252
Asignatura:   Seminario de Solucion de Problemas
              De Estructuras de Datos 2
Seccion:      D18
Profesor:     Guerrero Segura Ramirez Miguel Angel

********************/


#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "hash.h"
// #include "client.h"
#include "helper.h"
#include "constants.h"

// Define functions
int init_file();
void add_register(int fd, struct Client * clptr, struct Hash * hptr);

void fill_client(struct Client * cl);
void find_register(int fd, struct Hash * hptr, struct Client * clptr);

void menu();

int main(){

  // Declare the variables
  int fd;
  char ch;
  struct Client client;
  struct Hash hash;

  hash_init(&hash);

  fd = init_file();

  hash_load(fd, sizeof(struct Client), &hash);
  print_used(&hash);


  do{
    menu();
    ch = getchar();
    clean;

    switch (ch) {
      case INSERT:{
        add_register(fd, &client, &hash);
        break;
      }
      case FIND: {
        find_register(fd, &hash, &client);
        break;
      }
      case EXIT: break;
      default: {
        printf("Ingreso una opcion invalida, intente de nuevo.");
        break;
      }
    }
  }while( ch != EXIT );

  close(fd);
  return 0;
}

int init_file(){
  char file_name[BUF_SIZE];

  printf("\t¡Bienvenido al programa !\n\nIngrese el nombre del archivo con el que desea trabajar: ");
  get_str(file_name, BUF_SIZE);
  concat(file_name, EXTENSION);

  return open_file(file_name);
}

void add_register(int fd, struct Client * clptr, struct Hash * hptr){

  int cpos, size = sizeof(struct Client);
  cpos = lseek(fd, 0, SEEK_END);

  fill_client(clptr);
  hash_insert(hptr, clptr->last_name_a, cpos);
  write(fd, clptr, size);

  print_used(hptr);
}

void find_register(int fd, struct Hash * hptr, struct Client * clptr){
  char buf[BUF_SIZE];

  printf("Ingrese el registro que desea buscar: ");
  get_str(buf, BUF_SIZE);
  if( hash_find(fd, buf, hptr, clptr) == 1 )
    debug(clptr->last_name_a);

}
void fill_client(struct Client * cl){
  printf("Ingrese el apellido paterno: ");
  get_str(cl->last_name_a, BUF_SIZE);
}

void menu(){
  printf("\n%c) Ingresar un registro.\n%c) Buscar registro por llave.\n%c) Salir.",
    INSERT, FIND, EXIT);
  printf("\nIngrese la accion que desea realizar: ");
}
