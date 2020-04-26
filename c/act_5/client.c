#include "client.h"


extern void get_str(char * arr, int bufferSize);

void fill_client(struct Client * cl){
  printf("Ingrese los siguientes datos:\nApellido paterno: ");
  get_str(cl->last_name_a, BUF_SIZE);
  printf("Apellido materno: ");
  get_str(cl->last_name_b, BUF_SIZE);
  printf("Nombre: ");
  get_str(cl->name, BUF_SIZE);
  printf("Dirección: ");
  get_str(cl->address, BUF_SIZE);
  printf("Numero de telefono: ");
  get_str(cl->phone, PHONE);
  printf("Edad del cliente: ");
  get_str(cl->age, AGE);
  printf("Horario: ");
  get_str(cl->schedule, SCHEDULE);
  printf("Fecha de pago: ");
  get_str(cl->date, DATE);

}
