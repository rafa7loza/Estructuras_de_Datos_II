#include "hash.h"

static char a = 'a';

int hash_function(char * bfr){
  const int p = 53;
  int i=0;
  long long value = 0, p_pow = 1;

  while(bfr[i] != '\0'){
    value = (value + (bfr[i++] - a + 1 ) * p_pow ) % REGISTERS_SIZE;
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
  int key = hash_function(bfr), size = sizeof(struct Client);

  if( hptr->regs[ key ] == -1){
    printf("No se encuentra algun registro con esa llave\n");
    return 0;
  }

  printf("Key = %d, position in file = %d\n", key, hptr->regs[ key ]);
  do{
    lseek(fd, hptr->regs[ key ], SEEK_SET);
    read(fd, clptr, size);
    ++key;
  }while( str_equals(clptr->last_name_a, bfr) != 1 );

  return 1;

}

void hash_insert(struct Hash * hptr, char * bfr, int pfile){

  if( hptr->used_regs > REGISTERS_SIZE ){
    printf("Error: Ya no hay mas espacio en la memoria\n");
    return ;
  }

  int key = hash_function(bfr);

  if( hptr->regs[ key ] == -1 ){
    hptr->regs[ key ] = pfile;
    return ;
  }

  do{ key += 1 % REGISTERS_SIZE; }while( hptr->regs[ key ] != -1);

  hptr->regs[ key ] = pfile;
}

void print_used(struct Hash * hptr){
  for(int i=0; i<REGISTERS_SIZE; ++i)
    if( hptr->regs[i] != -1 )
      printf("{ Hash key: %d, Position in file: %d }\n", i, hptr->regs[i]);
}
