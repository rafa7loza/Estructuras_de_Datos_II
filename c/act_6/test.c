#include "hash.h"

void add_register(int fd, struct Client * clptr);

// Import functions from helper.h
extern void get_str(char * arr, int bufferSize);
extern void concat(char *a, char *b);
extern int open_file(char *str);
extern int create_filled_file(char * str, int size_in_bytes);
extern int file_exists(char * str);
extern int get_file_size(int fd);

// import functions from hash.h
extern int hash_function(char * bfr);
extern void map_fpos(int fd, char * bfr, int csize);
extern int hash_find(int fd, char * bfr, struct Client * clptr);
extern int create_file(char * file_name, int strsize);

// Import functions from client.h
extern void print_client(struct Client * clptr);

const int N = 30;

int main(){

  int regs, fd;
  struct Client client;
  char bfr[N];
  char fname[] = "pruebas";

  if(file_exists(fname) != -1)
    fd = open_file(fname);
  else
    fd = create_file(fname, sizeof(struct Client));

  printf("Tamaño del archivo %d\n", get_file_size(fd));

  printf("Ingrese el numero de registros: ");
  get_str(bfr, N);
  regs = atoi(bfr);

  while(regs--){
    // printf("%d\n", regs);
    add_register(fd, &client);

  }

  printf("Ingrese la llave primaria: ");
  get_str(bfr, N);
  hash_find(fd, bfr, &client);

  return 0;
}

void add_register(int fd, struct Client * clptr){

  int size = sizeof(struct Client);

  fill_client(clptr);
  map_fpos(fd, clptr->last_name_a, size);
  write(fd, clptr, size);

}
