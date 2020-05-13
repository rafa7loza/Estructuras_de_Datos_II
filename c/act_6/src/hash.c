#include "hash.h"
// #include "constants.h"

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

void hash_init(struct Hash * hptr){
  for(int i=0; i<REGISTERS_SIZE; ++i)
    hptr->regs[i] = -1;
  hptr->used_regs = 0;
}

void hash_load(int fd, int size, struct Hash * hptr){
  int fsize = get_file_size(fd), key;
  char bfr[BUF_SIZE];
  int bfsize = sizeof(bfr);

  lseek(fd, 0, SEEK_SET);

  while(lseek(fd, 0, SEEK_CUR) < fsize){
    read(fd, &bfr, bfsize);
    key = hash_function(bfr);
    while( hptr->regs[ key ] != -1) key += 1 % REGISTERS_SIZE;
    hptr->regs[ key ] = lseek(fd, size - bfsize, SEEK_CUR) - size;
  }
}

int hash_find(int fd, char * bfr, struct Hash * hptr, struct Client * clptr){
  char * str = to_lower(bfr);
  int key = hash_function(str), size = sizeof(struct Client);
  int fpos = key * size;
  int fsize = size * REGISTERS_SIZE;
  char aux;

  // fpos += size;
  lseek(fd, fpos, SEEK_SET);
  read(fd, &aux, sizeof(char));
  printf("%c\n", aux);

  if( aux == FILL ){
    printf("No se encuentra algun registro con esa llave\n");
    return 0;
  }

  do{
    lseek(fd, fpos, SEEK_SET);
    read(fd, clptr, size);
    if(str_equals(to_lower(clptr->last_name_a), to_lower(bfr)) != 1)
      break;
    printf("Key = %d, position in file = %d\n", key, fpos);
    print_client(clptr);
    fpos += size % fsize;
  }while(fpos <= fsize);

  return 1;

}

void hash_insert(int fd, char * bfr, int csize){

  // Add assertion whether registers can be added to the file

  char aux;
  int key = hash_function(bfr);
  printf("key %d\n", key);
  int fpos = csize * key;

  do{
    printf("Position in file: %d\n", fpos);
    lseek(fd, fpos, SEEK_SET);
    read(fd, &aux, sizeof(char));
    fpos += csize;
  }while(aux != FILL);
  lseek(fd, -1, SEEK_CUR);

}

void print_used(struct Hash * hptr){
  for(int i=0; i<REGISTERS_SIZE; ++i)
    if( hptr->regs[i] != -1 )
      printf("{ Hash key: %d, Position in file: %d }\n", i, hptr->regs[i]);
}
