int len(char *arr){
  int i=0, result=0;
  while(arr[i++] != '\0') ++result;
  return result;
}

void getStringFilled(char *arr, int bufferSize){
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

  if(index < bufferSize-1){
    while(index < bufferSize-1) arr[index++] = '*';
  }
  arr[bufferSize-1] = '\0';
}

void getString(char *arr, int bufferSize){
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
  // printf("%s: %d == %d\n", a, sz, len(a));
  for(int i=0; i<len(b); ++i){
    a[sz+i] = b[i];
  }
  a[sz+len(b)] = '\0';
}

char * inmutableConcat(char *a, char *b){
  char *arr;
  int size_a = len(a), size_b = len(b), i, k;

  arr = malloc(sizeof(char)*(size_a+size_b));

  for(i=0; i<size_a; ++i)
    arr[i] = a[i];

  for(k=0; i<size_a+size_b; ++i, ++k)
    arr[i] = b[k];

  arr[size_a+size_b] = '\0';

  return arr;
}

void copyString(char *a, char *b){
  int i=0;
  while(a[i] != '\0'){
    b[i] = a[i];
    ++i;
  }
  b[i] = '\0';
}

void fillEmptyString(char *a, char *b){
  int i=0;
  while(a[i] != '\0'){
    b[i] = a[i];
    ++i;
  }
  b[i] = '\0';
}

void fillString(char *str, int size, char c){
  int i=0, currentLength = len(str);
  for(i=currentLength; i<size-1; ++i)
    str[i] = c;

  str[size-1] = '\0';
}

void readField(char *bf, char *str, int *begin, int fieldSize, char fill){
  int limit = (*begin) + (fieldSize-1), i=0;
  while(((*begin)+i) < limit && bf[(*begin)+i] != fill){
    str[i] = bf[(*begin)+i];
    ++i;
  }

  (*begin) += fieldSize;

  if(i < fieldSize-1) str[i] = '\0';
  else str[fieldSize-1] = '\0';
}

int openFile(char *str){
  // Opening the file
  return open(str,
    // Flags
    O_RDWR | O_CREAT,
    // Permisions
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int getFileSize(int fd){
  return lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET);
}

void print(char *c){
  int i=0;
  while(c[i] != '\0') printf("%c", c[i++]);
  printf("\n");
}

int isNumber(char *arr){
  int i=0, a;
  while(arr[i] != '\0'){
    a = arr[i]-'0';
    if(a < 0 || a > 9) return 0;
    ++i;
  }
  return 1;
}

int charToInt(char *arr){
  int result = 0, p = len(arr)-1, i=0;

  while(arr[i] != '\0')
    result += pow(10, p--) * (arr[i++]-'0');


  return result;
}

char * to_lower(char *str){
  int i=0, length = len(str);
  char *result = malloc(sizeof(char)*length);

  while(str[i] != '\0'){
    if((int)str[i] >= 65 && (int)str[i] <= 90){
      int x = str[i] + 32;
      result[i] = (char)x;
    }else
      result[i] = str[i];
    ++i;
  }
  result[i] = '\0';

  return result;
}

int strEquals(char *a, char *b){
  int len_a = len(a), len_b = len(b);

  if(len_a != len_b) return 0;

  for(int i=0; i<len_b; ++i){
    if(a[i] != b[i]) return 0;
  }

  return 1;
}

/***
 To do

 Show all secondary index
 save secondary index at the end of the program

*/
