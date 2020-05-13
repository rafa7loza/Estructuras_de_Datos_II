#include "hash.h"

// Import functions from helper.h
extern void get_str(char * arr, int bufferSize);
extern void concat(char *a, char *b);
extern int open_file(char *str);
extern int create_filled_file(char * str, int size_in_bytes);
extern int file_exists(char * str);


// import functions from hash.h
extern void hash_init(struct Hash * hptr);
extern void hash_load(int fd, int size, struct Hash * hptr);
extern void print_used(struct Hash * hptr);
extern void hash_insert(int fd, char * bfr, int csize);
extern int hash_find(int fd, char * bfr, struct Hash * hptr, struct Client * clptr);
extern int create_file(char * file_name, int strsize);
// Import functions from client.h
extern void print_client(struct Client * clptr);

int main(){

  create_file("casa", sizeof(struct Client));
  return 0;
}
