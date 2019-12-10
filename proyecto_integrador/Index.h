#ifndef INDEX_H
#define INDEX_H

class Index{
private:
  int index;
  int reference;

public:
  Index();

  Index(int ind, int ref);
  int getIndex();
  int getReference();
  void setIndex(int ind);
  void setReference(int ref);
};


#endif
