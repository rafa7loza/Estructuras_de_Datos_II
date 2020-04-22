struct Secondary_Index{
  char field[FIELD_SIZE_A];
  int key;
};


void saveSecondaryIndex(struct Secondary_Index *index, int size, char *file_name, char *index_type){
  char *suffix = inmutableConcat(index_type, EXTENSION);
  char *index_file_name = inmutableConcat(file_name, suffix);

  int fd = open(index_file_name,
    // Flags
    O_RDWR | O_CREAT | O_TRUNC,
    // Permisions
    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  lseek(fd, 0, SEEK_SET);

  for(int i=0; i<size; ++i){
    write(fd, (char*)&index[i].field, sizeof(char)*FIELD_SIZE_A);
    write(fd, &index[i].key, sizeof(int));
  }

  close(fd);
}

int loadSecondaryIndex(struct Secondary_Index *index, char *file_name, char *index_type){

  char *suffix = inmutableConcat(index_type, EXTENSION);
  char *index_file_name = inmutableConcat(file_name, suffix);

  int fd = openFile(index_file_name);
  int size = getFileSize(fd), k=0;
  lseek(fd, 0, SEEK_SET);

  for(int i=0; i<size; i += SECONDARY_INDEX_REGISTER, ++k){
    read(fd, index[k].field, sizeof(char)*FIELD_SIZE_A);
    read(fd, &index[k].key, sizeof(int));
  }
  close(fd);

  return k;
}

void addSecondaryIndex(struct Secondary_Index *index, char *value, int key){
  copyString(value, index->field);
  index->key = key;
}

void printSecondaryIndex(struct Secondary_Index *index, char *type){
  printf("%s => %s\n", type, index->field);
  printf("Llave secundaria => %d\n", index->key);
}

void showAll(struct Secondary_Index *index, int size, char *type){
  for(int i=0; i<size; ++i){
    printSecondaryIndex(&index[i], type);
  }
}

int getKey(char *field, struct Secondary_Index *index, int size){
  char *str = to_lower(field);

  for(int i=0; i<size; ++i){
    char *aux = to_lower(index[i].field);
    if(strEquals(aux, str) == 1) return index[i].key;
  }
  return -1;
}
