/*******************

Nombre:       Loza Arechiga Andre Rafael
Codigo:       214589252
Asignatura:   Seminario de Solucion de Problemas
              De Estructuras de Datos 2
Seccion:      D18
Profesor:     Guerrero Segura Ramirez Miguel Angel

********************/

#include "hash.h"

// Define functions
void menu();
int init_file();
void add_register(int fd, struct Client * clptr);
void find_register(int fd, struct Client * clptr);

// Import functions from helper.h
extern void get_str(char * arr, int bufferSize);
extern void concat(char *a, char *b);
extern int open_file(char *str);
extern int create_filled_file(char * str, int size_in_bytes);
extern int file_exists(char * str);


// import functions from hash.h
extern int hash_function(char * bfr);
extern void map_fpos(int fd, char * bfr, int csize);
extern int hash_find(int fd, char * bfr, struct Client * clptr);
extern int create_file(char * file_name, int strsize);


// Import functions from client.h
extern void print_client(struct Client * clptr);

int main(){

  // Declare the variables
  int fd;
  char ch;
  struct Client client;

  fd = init_file();
  printf("Tamaño del archivo: %d Bytes\n", get_file_size(fd));

  do{
    menu();
    ch = getchar();
    clean;

    switch (ch) {
      case INSERT:{
        add_register(fd, &client);
        break;
      }
      case FIND: {
        find_register(fd, &client);
        break;
      }
      case EXIT: break;
      default: {
        printf("\nIngreso una opcion invalida, intente de nuevo.\n");
        break;
      }
    }
  }while( ch != EXIT );

  close(fd);
  return 0;
}

int init_file(){
  char file_name[BUF_SIZE];
  int size = sizeof(struct Client);

  printf("\t¡Bienvenido al programa !\n\nIngrese el nombre del archivo con el que desea trabajar: ");
  get_str(file_name, BUF_SIZE);
  concat(file_name, EXTENSION);

  if(file_exists(file_name) != -1)
    return open_file(file_name);
  else
    return create_file(file_name, size);
}

void add_register(int fd, struct Client * clptr){

  int size = sizeof(struct Client);

  fill_client(clptr);
  map_fpos(fd, clptr->last_name_a, size);
  write(fd, clptr, size);

}

void find_register(int fd, struct Client * clptr){
  char buf[BUF_SIZE];

  printf("Ingrese el registro que desea buscar: ");
  get_str(buf, BUF_SIZE);
  if( hash_find(fd, buf, clptr) == 1 )
    printf("\n");
    // print_client(clptr);
    // debug(clptr->last_name_a);


}

void menu(){
  printf("\n%c) Ingresar un registro.\n%c) Buscar registro por llave.\n%c) Salir.",
    INSERT, FIND, EXIT);
  printf("\nIngrese la accion que desea realizar: ");
}
