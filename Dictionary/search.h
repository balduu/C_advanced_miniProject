#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "btree.h"
#include"soundex.h"


/*
  Tao cay soundex de su dung trong ham tu hoan thanh sau va goi y ket qua
 */
void creatSoundexTree(BTA *Dic, BTA **soundexTree){
  char en[40],vi[100000];
  int rsize,i=0;
  char soundex[5];
  *soundexTree=btcrt("soundexTree",0,0);
  btsel(Dic,"",vi,100000*sizeof(char),&rsize);
  while(btseln(Dic,en,vi,100000*sizeof(char),&rsize)==0){
    Soundex(soundex,en,4,1);
    btins(*soundexTree,en,soundex,5*sizeof(char));
    i++;
  }
  printf("da them %d vao soundexTree\n",i);
}

/*
  Ham goi y ket qua tim kiem
 */
int suggestion(BTA *soundexTree, char *word, char s[][100]){
  int rsize,i=0;
  char en[40],soundex[7],code[5];
  Soundex(code,word,4,1);
  btsel(soundexTree,"",soundex,5*sizeof(char),&rsize);
  while(btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0 && i<10){
    if(strcmp(code,soundex)==0) // kiem tra cach phat am
      strcpy(s[i++],en);
  }
  return i;
}

/*
  Kiem tra s1 co trong phan dau cua s2 hay khong
  tra ve 1 neu thanh cong
*/
int check(char *s1, char *s2){
  int len1=strlen(s1);
  int len2=strlen(s2),i;
  if(len1>len2) return 0;
  else{
    for(i=0;i<len1;i++){
      if(s1[i]!=s2[i])
	return 0;
    }
  }
  return 1;
}

/*
  Tim kiem tu complete, luu trong xau result,
  tra ve 1 neu thanh cong, 0 neu that bai
*/
int autoComplete(BTA *soundexTree, char *word, char *result){
  //int len1=strlen(word);
  int rsize;
  char en[40], soundex[5];
  btsel(soundexTree,"",soundex,5*sizeof(char),&rsize);
  while(btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0){
    if(check(word,en)==1){
      strcpy(result,en);
      return 1;
    }
  }
  return 0;
}

/*
  Goi y cac tu co the xuat hien 
*/
int MultiComplete(BTA *soundexTree, char *word){
  int rsize,i=0;
  char en[40], soundex[5];
  btsel(soundexTree,"",soundex,5*sizeof(char),&rsize);
  while((btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0))
    {
    if(check(word,en)==1){
      puts(en);
      i++;
      if(i>6) {
	return 1; }
    }
  }
  return 0;
}


