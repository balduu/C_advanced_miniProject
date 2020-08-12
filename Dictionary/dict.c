#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "btree.h"
#include "search.h"
#include "getch.h"
#define MAXSIZE 20000

// gcc -o dict dict.c -Lbtree/lib -lbt -Ibtree/inc

int main() {

  int c;
  int dem=0;
  BTA *Dic,*soundexTree;
  Dic = btopn("tudien", 0, 0);
  if (Dic == NULL) {
    Dic = btcrt("tudien",0,0);
    // ==============================================
    FILE *fp = fopen("anhviet2.txt" , "r");
    if(fp == NULL) 
      {
	printf("Xảy ra lỗi đọc file \n");
	return(-1);
      }
    
    fgetc(fp);
    while(!feof(fp)){
      char mean_[MAXSIZE]; 
      char mean[MAXSIZE];
      char word[50];
      
      
      fscanf(fp,"%[^/]s",word);
      word[strlen(word)-1]='\0';
      // printf("%s\n",word);
      
      int i=0;
      char c='\n';
      
      while(c!='@')
	{
	  c=fgetc(fp);
	  if(c==EOF) break;
	  
	  mean_[i]=c;
	  i=i+1;
	}
      if(c==EOF) mean_[i-2]='\0'; else mean_[i-3]='\0';
      strcpy(mean,word);
      strcat(mean,mean_);
      //printf("%s\n",mean);
      int x = btins(Dic,word,mean,MAXSIZE);
      if(x==0)  {
	dem++;
	printf("%s\n",word);
      }
    }
    printf("Đã nhập vào %d từ \n",dem);
    fclose(fp);
  }
  else printf("Đã khởi tạo từ điển \n");
  
  soundexTree = btopn("soundexTree", 0, 0);
  if (soundexTree == NULL) {
    creatSoundexTree(Dic,&soundexTree);
  }
  else printf("Đã khởi tạo soundexTree\n");
  do {
    printf("==========================\n");
    printf("1-Tra từ \n");
    printf("2-Thêm từ và từ điển\n");
    printf("3-Sửa từ trong từ điển\n");
    printf("4-Xóa từ \n");
    printf("5-Thoát \n");
    printf("Nhập lựa chọn :");
    scanf("%d",&c);
    
    switch(c) {
    case 1: {
      int i = 0;
      char key[100], value[MAXSIZE];
      getchar();
      printf("Nhập từ cần tìm : ");
      do {
	key[i] = getch();
	if(key[i]== 127) {
	  //printf("\b \b");
	  i = i-1;
	  key[i]='\0';
	}
	else {
	  //printf("%c",key[i++]);
	  i++;
	  key[i]='\0';
	}
	
	puts(key);
	printf("---------\n");
	int x;
	x=MultiComplete(soundexTree,key);
	printf("-----------------------------------\n");
      } while((key[i-1] != '\t') && (key[i-1] != '\n'));
      char c = key[i-1];
      key[i-1] = '\0';
      
      printf("------\n");

      if(c=='\t') {
	char result[100];
	int x;
	x=autoComplete(soundexTree,key,result);
	if(x!=0) {
	  printf("\n%s\n---------\n",result);
	  int num2;
	  int res2 = btsel(Dic,result,value,MAXSIZE,&num2);
	  if (res2 == 0)
	    printf("Mean: %s\n------------------------\n", value);
	  else {
	    printf("Không tìm thấy từ \n-------------------\n");
	  }
	}
	else {
	  printf("\nKhông tìm thấy từ \n--Gợi ý có thể \n-------------------\n");
	  char suggest[15][100];
	  char word[100];
	  int i,k;
	  k=suggestion(soundexTree,key,suggest);
	  if(k!=0)
	    for(i=0;i<9;i++) {
		printf("%s\n",suggest[i]);
	    }
	  else printf("Không có từ gợi ý \n-------------------\n");
	}
      }
      
      else if(c=='\n') {
	char value[MAXSIZE];
	int num;
	int res = btsel(Dic,key,value,MAXSIZE,&num);
	if (res == 0)
	  printf("Mean: %s\n", value);
	else {
	  printf("\nKhông tìm thấy từ \n--Gợi ý có thể\n-------------------\n");
	  char suggest[15][100];
	  char word[100];
	  int i,k;
	  k=suggestion(soundexTree,key,suggest);
	  if(k!=0)
	    for(i=0;i<9;i++) {
		printf("%s\n",suggest[i]);
	    }
	  else printf("Không có từ gợi ý \n-------------------\n");
	}
      }
      
    } break;
    case 2: {
      printf("Thêm từ vào từ điển  \n");
      char key[100],value[MAXSIZE];
      printf("Nhập từ cần thêm :\n");
      printf("Eng: ");
      getchar();
      gets(key);
      printf("Vie: ");
      gets(value);
      int i = btins(Dic,key,value,MAXSIZE);
      char soundex[5];
      Soundex(soundex,key,4,1);
      btins(soundexTree,key,soundex,5*sizeof(char));
      if(i==0)
	printf("Thêm từ thành công \n");
      else
	printf("Thêm từ thất bại \n");
    } break;
    case 3: {
      printf("Sửa từ trong từ điển  \n");
      char key[100],value[MAXSIZE];
      printf("Nhập từ cần sửa :\n");
      printf("Eng: ");
      getchar();
      gets(key);
      printf("Vie: ");
      gets(value);
      int x = btupd(Dic,key,value,MAXSIZE);
      if(x==0) printf("Sửa từ thành công \n");
    } break;
    case 4: {
      printf("4- Xóa từ \n");
      char key[100],value[MAXSIZE];
      int num;
      printf("Nhập từ cần xóa :\n");
      printf("Eng: ");
      getchar();
      gets(key);
      int res1 = btsel(Dic,key,value,MAXSIZE,&num);
      int res2 = btsel(Dic,key,value,MAXSIZE,&num);
      if (res1 + res2 == 0) {
        int x = btdel(Dic,key);
	int y = btdel(soundexTree,key);
	if((x==0) && (y==0)) printf("Xóa thành công \n");
      }
      else
        printf("Không tồn tại từ này \n");
    } break;
    case 5: {
      printf("Kết thúc sử dụng \n");
    } break;
    default : {
      printf("Lựa chọn sai \n");
    } break;
    }
  } while(c!=5);

  btcls(Dic);
  btcls(soundexTree);
  return 0;
}
