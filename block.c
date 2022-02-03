#include<stdlib.h>
#include<ncurses.h>
#include<time.h>
#include"module_two.h"


void visible_blocks(struct block *arr, int count){
  chtype b;
  for (int i=0;i<count;i++){
    if (arr[i].time!=0){
      move(arr[i].y,arr[i].x);
      b=arr[i].point|COLOR_PAIR(arr[i].color);
      addch(b); 
    }
  }
  refresh();
}


void initial_blocks(struct block **arr_blocks,
	     int *count, int xmax, int ymax,
	     int ttime, int color){
  int new_count=*count;
  if ((*arr_blocks)!=NULL)
  {
   while ((*count)>1) delete_blocks(arr_blocks, count);
   *arr_blocks=NULL;
  }
  (*count)=new_count;
  *arr_blocks=
    (struct block *)
    calloc(*count, sizeof(struct block));
  srand(time(NULL));
  for (int i=0;i<(*count);i++){
    (*arr_blocks)[i].x=1+rand()%(xmax-2);
    (*arr_blocks)[i].y=1+rand()%(ymax-2);
    (*arr_blocks)[i].color=1+rand()%color;
    (*arr_blocks)[i].time=1+rand()%ttime;
    (*arr_blocks)[i].type=rand()%2;
    (*arr_blocks)[i].point=49+rand()%9;
  }
}

void work_blocks(struct block **arr_blocks, int count,
	  int xmax, int ymax, int ttime, int color){
  srand(time(NULL));
  for (int i=0;i<count;i++){
    if ((*arr_blocks)[i].time>0)
      ((*arr_blocks)[i].time)--;
    else
      if (rand()%2){
	 (*arr_blocks)[i].x=1+rand()%(xmax-2);
	 (*arr_blocks)[i].y=1+rand()%(ymax-2);
	 (*arr_blocks)[i].color=1+rand()%color;
	 (*arr_blocks)[i].time=1+rand()%ttime;
	 (*arr_blocks)[i].type=rand()%2;
         (*arr_blocks)[i].point=49+rand()%9;	
      }
  }
}

void add_blocks(struct block **arr_blocks, int *count,
	 int xmax, int ymax, int ttime, int color){
  *arr_blocks=
    (struct block *)
    realloc(*arr_blocks,(++(*count))*sizeof(struct block));
  srand(time(NULL));
  (*arr_blocks)[*count-1].x=1+rand()%(xmax-2);
  (*arr_blocks)[*count-1].y=1+rand()%(ymax-2);
  (*arr_blocks)[*count-1].color=1+rand()%color;
  (*arr_blocks)[*count-1].time=1+rand()%ttime;
  (*arr_blocks)[*count-1].type=rand()%2;
  (*arr_blocks)[*count-1].point=49+rand()%9;
}

void delete_blocks(struct block **arr_blocks, int *count){
  if (*count>1)
  *arr_blocks=
    (struct block *)realloc(*arr_blocks,(--(*count))*sizeof(struct block));
}

