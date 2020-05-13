#include "client.h"

int hash_function(char * bfr);
void map_fpos(int fd, char * bfr, int csize);
int hash_find(int fd, char * bfr, struct Client * clptr);
int create_file(char * file_name, int strsize);
