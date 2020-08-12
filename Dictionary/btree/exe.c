#include <stdio.h>
#include "btree.h"
int main() {
  char pb[] = "phonebook.db";
  
  btinit();
  BTA *book;
  
  bansky(book,"chung",123456789);
  binsky(book,"trung",987654321);

  long value;
  int res = bfndky(book,"chung",&value);
  if(res==0) 
    printf("phone : %ld\n",value);
  else {printf("not found\n");
  
  btcls(book);
  return 0;
}
