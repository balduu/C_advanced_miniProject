// Name: Nguyen Minh Hoang
#include<stdio.h>
#include "btree.h"

// gcc week5-practice.c -Lbtree/lib -lbt -Ibtree/inc
int main(){
    char pb[] = "phonebook.db";
    
    // Initialization
    btinit();
    BTA *book;
    
    // Open a b-tree file
    book = btopn(pb, 0, 0);
    if (book == NULL)
        book = btcrt(pb, 0, 0);
    
    // Insert a key
    binsky(book, "chung", 981999999);
    binsky(book, "diep", 981999999);
    
    bupdky(book,"chung",1234);
    
    // Find a key
    long value;
    int res = bfndky(book, "chung", &value);
    if (res == 0)
        printf("Phone number: %ld\n", value);
    else
        printf("Not found\n");
    
    // Close
    btcls(book);
}
