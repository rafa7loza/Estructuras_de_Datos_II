#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define debug(str) printf("Debug: ** %s **\n", str)
#define clean while ((getchar()) != '\n')

int str_equals(char *a, char *b);
int len(char *arr);
void get_str(char * arr, int bufferSize);
void concat(char *a, char *b);
int open_file(char *str);
int get_file_size(int fd);
