#include "helper.h"

int len(char *arr){
  int i=0, result=0;
  while(arr[i++] != '\0') ++result;
  return result;
}

void get_str(char * arr, int bufferSize){
  int index=0;
  char c;

  while((c = getchar()) != '\n') {
    if(index >= bufferSize-1){
      ++index;
      continue;
    }
    arr[index] = c;
    ++index;
  }

  if(index < bufferSize-1) arr[index] = '\0';
  else arr[bufferSize-1] = '\0';
}

void concat(char *a, char *b){
  int sz = len(a);

  for(int i=0; i<len(b); ++i){
    a[sz+i] = b[i];
  }
  a[sz+len(b)] = '\0';
}

int open_file(char *str){
  // Opening the file
  return open(str,
    // Flags
    O_RDWR | O_CREAT,
    // Permisions
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int get_file_size(int fd){
  return lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET);
}

int str_equals(char *a, char *b){
  int len_a = len(a), len_b = len(b);

  if(len_a != len_b) return 0;

  for(int i=0; i<len_b; ++i){
    if(a[i] != b[i]) return 0;
  }

  return 1;
}
