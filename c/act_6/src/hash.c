#include "hash.h"

extern char * to_lower(char *str);

static char a = 'a';

int hash_function(char * bfr){
  char * str = to_lower(bfr);
  const int p = 53;
  int i=0;
  long long value = 0, p_pow = 1;

  while(str[i] != '\0'){
    value = (value + (str[i++] - a + 1 ) * p_pow ) % REGISTERS_SIZE;
    p_pow = (p * p_pow) % REGISTERS_SIZE;
  }

  return value;
}

int hash_find(int fd, char * bfr, struct Client * clptr){
  char * str = to_lower(bfr);
  unsigned short cnt, i;
  int key = hash_function(str), size = sizeof(struct Client);
  int fpos;
  int curKey = key;
  int flg = 1;
  // clptr = NULL;

  do{
    fpos = curKey * ((size * CONTAINER) + sizeof(unsigned short));
    lseek(fd, fpos, SEEK_SET);
    read(fd, &cnt, sizeof(unsigned short));

    // printf("Clientes: %d\n", cnt);
    if( cnt ){
      for(i=0; i<cnt; ++i){
        read(fd, clptr, size);
        // printf("a: %d, b: %d\n", hash_function(clptr->last_name_a), key);
        if( str_equals(to_lower(clptr->last_name_a), to_lower(bfr)) ){
          flg = 0;
          print_client(clptr);
        }
        // printf("Position in file.%ld\n", lseek(fd, 0, SEEK_CUR));
      }
    }
    curKey = (curKey+1)%REGISTERS_SIZE;

  }while(cnt && curKey != key);

  if(flg){
    printf("No se encuentra algun registro con esa llave\n");
    return 0;
  }
  return 1;

}

void map_fpos(int fd, char * bfr, int csize){

  unsigned short times;
  int key = hash_function(bfr);
  int fpos = key * ((csize * CONTAINER) + sizeof(unsigned short));
  printf("{key: %d, Position: %d}\n", key, fpos);

  lseek(fd, fpos, SEEK_SET);
  read(fd, &times, sizeof(unsigned short));
  lseek(fd, -sizeof(unsigned short), SEEK_CUR);

  // assert(times >= 0 && times < 3);
  if(times > 2){
    int initialPos = key;
    do{
      initialPos = (initialPos+1) % REGISTERS_SIZE;
      fpos = initialPos * ((csize * CONTAINER) + sizeof(unsigned short));
      printf("{key: %d, Position: %d}\n", initialPos, fpos);
      lseek(fd, fpos, SEEK_SET);
      read(fd, &times, sizeof(unsigned short));
      lseek(fd, -sizeof(unsigned short), SEEK_CUR);
    }while(times > 2);
  }

  printf("%d registros en el compartimento.\n", times);

  // Update the number of registes
  ++times;
  write(fd, &times, sizeof(unsigned short));

  // Locate cursor in the position to write
  lseek(fd, (times-1)*csize, SEEK_CUR);

}


int create_file(char * file_name, int strsize){
  char ch = FILL;
  unsigned short initval = 0;

  int fd = open(file_name,
    // Flags
    O_RDWR | O_CREAT,
    // Permisions
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  char * bfr;
  int total_len = CONTAINER * strsize;
  printf("Structure is %d bytes length (%d).\n", strsize, total_len);
  bfr = (char *) malloc(sizeof(char) * total_len);
  memset(bfr, ch, total_len);

  lseek(fd, 0, SEEK_SET);

  for(int i=0; i<REGISTERS_SIZE; ++i){
    write(fd, &initval, sizeof(unsigned short));
    write(fd, bfr, total_len);
  }

  return fd;
}
