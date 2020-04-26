#include "client.h"


extern void get_str(char * arr, int bufferSize);

void fill_client(struct Client * cl){
  printf("Ingrese el apellido paterno: ");
  get_str(cl->last_name_a, BUF_SIZE);
}
