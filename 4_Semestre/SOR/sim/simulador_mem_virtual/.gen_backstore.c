#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
  FILE *fp;
  unsigned char c;
  srand(time(NULL));

  fp = fopen("backstore.bin","w");
  if(fp == NULL)
  {
    fprintf(stderr,"cannot write to backstore.bin");
    return 1;
  }

  for(int i = 0 ; i < 65536 ; i++)
  {
    c = (char) (rand() % 26) + 65;
    fprintf(fp,"%c",c);
  }

  fclose(fp);

  return 0;
}
