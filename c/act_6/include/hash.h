// #include "constants.h"
#include "client.h"
// #include "helper.h"

struct Hash{
  int regs[REGISTERS_SIZE];
  int used_regs;
};

int hash_function(char * bfr);
void hash_init(struct Hash * hptr);
void hash_load(int fd, int size, struct Hash * hptr);
void print_used(struct Hash * hptr);
void hash_insert(int fd, char * bfr, int csize);
int hash_find(int fd, char * bfr, struct Hash * hptr, struct Client * clptr);
