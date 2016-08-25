#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"

#define X 128
#define Y 128

char buffer[X][Y];

int move(int *x, int *y, int dir)
{
  switch(dir)
  {
     case 0:
       (*y)++;
       break;
     case 1:
       (*x)++;
       break;
     case 2:
       (*y)--;
       break;
     case 3:
       (*x)--;
       break;
  }
  if(*x >= X || *x < 0)
    return 0;
  if(*y >= Y || *y < 0)
    return 0;

  return 1;
}

int main(int argc, char *argv[])
{
  unsigned int dir = 0;
  int x_pos = X/2;
  int y_pos = Y/2;
  int quit = 1;

  start_encode(X, Y, 10);

  while(quit)
  {
     if(buffer[x_pos][y_pos])
     {
        dir = (dir-1)%4;
        buffer[x_pos][y_pos] = 0;
	quit = move(&x_pos, &y_pos, dir);
        next_frame((char *) buffer);
     }
     else
     {
        dir = (dir+1)%4;
        buffer[x_pos][y_pos] = 1;
        quit = move(&x_pos, &y_pos, dir);
        next_frame((char *) buffer);
     }
  }
 
  finish_encode(); 

  return 0;
}
