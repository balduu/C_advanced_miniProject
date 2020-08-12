#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "btree.h"
#include"soundex.h"

/* 
   Kiem tra du lieu trong cac cay btree
 */
/* 
   In ra cay soundex 
*/
void printSoundexTree(BTA *soundexTree){
  char en[40],soundex[5];
  int rsize;
  int i=0;
  btsel(soundexTree,"",soundex,5*sizeof(char),&rsize); //printf("1\n");
  while(btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0){
    printf("%s\n%s\n",en,soundex);
  }
}
/*
  In cay tu dien ban dau
*/
void printDic(BTA *Dic){
  char en[40],mean[100000];
  int rsize;
  int i=0;
  btsel(Dic,"",mean,100000*sizeof(char),&rsize); //printf("1\n");
  while(btseln(Dic,en,mean,100000*sizeof(char),&rsize)==0){
    printf("%s\n%s\n",en,mean);
  }
}
