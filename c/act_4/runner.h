struct Runner{
  int valid;
  char number[NUM_SIZE];
  char name[FIELD_SIZE_A];
  char address[FIELD_SIZE_A];
  char city[FIELD_SIZE_A];
  char nationality[FIELD_SIZE_B];
  char time[TIME_FORMAT_SIZE];
};

void initRunner(struct Runner *runner){
  runner->valid = 0;
  printf("Ingrese el numero del corredor: ");
  getString(runner->number, NUM_SIZE);

  if(!isNumber(runner->number)){
    printf("El valor ingresado no es un numero válido.\n");
    return;
  }

  int id = charToInt(runner->number);
  if(id < 0 || id > 2000){
    printf("El valor ingresado no es un numero válido.\n");
    return;
  }

  printf("Ingrese el nombre del corredor: ");
  getString(runner->name, FIELD_SIZE_A);
  printf("Ingrese su direccion: ");
  getString(runner->address, FIELD_SIZE_A);
  printf("Ingrese su ciudad de origen: ");
  getString(runner->city, FIELD_SIZE_A);
  printf("Ingrese su nacionalidad: ");
  getString(runner->nationality, FIELD_SIZE_B);
  printf("Ingrese su tiempo: ");
  getString(runner->time, TIME_FORMAT_SIZE);
  // printf("Tiempo record: %s\n", runner->time);
  runner->valid = 1;
}

void writeToFile(struct Runner *runner, int fd){
  fillString(runner->number, NUM_SIZE, FILL_CHAR);
  fillString(runner->name, FIELD_SIZE_A, FILL_CHAR);
  fillString(runner->address, FIELD_SIZE_A, FILL_CHAR);
  fillString(runner->city, FIELD_SIZE_A, FILL_CHAR);
  fillString(runner->nationality, FIELD_SIZE_B, FILL_CHAR);
  fillString(runner->time, TIME_FORMAT_SIZE, FILL_CHAR);

  lseek(fd, 0, SEEK_END);

  write(fd, (char *)runner->number, NUM_SIZE);
  write(fd, (char *)runner->name, FIELD_SIZE_A);
  write(fd, (char *)runner->address, FIELD_SIZE_A);
  write(fd, (char *)runner->city, FIELD_SIZE_A);
  write(fd, (char *)runner->nationality, FIELD_SIZE_B);
  write(fd, (char *)runner->time, TIME_FORMAT_SIZE);

  printf("\nRegister successfully written in file!\n");
}

void readLastFromFile(struct Runner *runner, int fd){

  int position = lseek(fd, 0, SEEK_END) - REGISTER_SIZE, bytes, k=0;
  char buffer[REGISTER_SIZE];

  lseek(fd, position, SEEK_SET);

  bytes = read(fd, buffer, REGISTER_SIZE);
  // printf("%d: %s\n", bytes, buffer);

  readField(buffer, runner->number, &k, NUM_SIZE, FILL_CHAR);
  printf("%s\n", runner->number);

  readField(buffer, runner->name, &k, FIELD_SIZE_A, FILL_CHAR);
  printf("%s\n", runner->name);

  readField(buffer, runner->address, &k, FIELD_SIZE_A, FILL_CHAR);
  printf("%s\n", runner->address);

  readField(buffer, runner->city, &k, FIELD_SIZE_A, FILL_CHAR);
  printf("%s\n", runner->city);

  readField(buffer, runner->nationality, &k, FIELD_SIZE_B, FILL_CHAR);
  printf("%s\n", runner->nationality);

  readField(buffer, runner->time, &k, TIME_FORMAT_SIZE, FILL_CHAR);
  printf("%s\n", runner->time);

}

void findRunner(struct Runner *runner, int pos, int fd){
  if(pos == -1) runner->valid = 0;
  else{
    int k=0;
    char buffer[REGISTER_SIZE];

    lseek(fd, pos, SEEK_SET);

    read(fd, buffer, REGISTER_SIZE);

    readField(buffer, runner->number, &k, NUM_SIZE, FILL_CHAR);
    readField(buffer, runner->name, &k, FIELD_SIZE_A, FILL_CHAR);
    readField(buffer, runner->address, &k, FIELD_SIZE_A, FILL_CHAR);
    readField(buffer, runner->city, &k, FIELD_SIZE_A, FILL_CHAR);
    readField(buffer, runner->nationality, &k, FIELD_SIZE_B, FILL_CHAR);
    readField(buffer, runner->time, &k, TIME_FORMAT_SIZE, FILL_CHAR);
    runner->valid = 1;
  }
}

void printRunner(struct Runner *runner){
  printf("Numero: %s\n", runner->number);
  printf("Nombre: %s\n", runner->name);
  printf("Domicilio: %s\n", runner->address);
  printf("Ciudad: %s\n", runner->city);
  printf("Nacionanlidad: %s\n", runner->nationality);
  printf("Tiempo: %s\n", runner->time);
}
