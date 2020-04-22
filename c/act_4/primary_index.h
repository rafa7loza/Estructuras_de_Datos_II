struct Primary_Index{
  int pk;
  char time[TIME_FORMAT_SIZE];
  int position;
};

void loadIndex(struct Primary_Index *index, int fd){
  int size = getFileSize(fd);
  for(int i=0, k=0; i<size; i += INDEX_REGISTER, ++k){
    read(fd, &index[k].pk, sizeof(int));
    read(fd, index[k].time, sizeof(char)*TIME_FORMAT_SIZE);
    read(fd, &index[k].position, sizeof(int));
  }
}

void printIndex(struct Primary_Index *index){
  printf("Primary key: %d\n", index->pk);
  printf("Last time: %s\n", index->time);
  printf("Position in file: %d\n", index->position);
}

void printAll(struct Primary_Index *index, int size){
  for(int i=0; i<size; ++i){
    printIndex(&index[i]);
  }
}

void showKeys(struct Primary_Index *index, int len){
  printf("\tIndices:\n");
  for(int i=0; i<len; ++i)
    printf("%d: %d\n", i+1, index[i].pk);
}

int getPosition(int key, struct Primary_Index *index, int len){
  for(int i=0; i<len; ++i)
    if(index[i].pk == key) return index[i].position;
  return -1;
}

void saveIndex(struct Primary_Index *index, int size, int *fd, char *file_name){

  close(*fd);
  (*fd) = open(file_name,
    // Flags
    O_RDWR | O_CREAT | O_TRUNC,
    // Permisions
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  lseek(*fd, 0, SEEK_SET);

  for(int i=0; i<size; ++i){
    write(*fd, &index[i].pk, sizeof(int));
    write(*fd, (char*)index[i].time, sizeof(char)*TIME_FORMAT_SIZE);
    write(*fd, &index[i].position, sizeof(int));
  }
}
