#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readimg.h"



void read_ppm (FILE *infile, char *p, int x, int y, const char *file)
{   
  int end = 0;
  int count = 0;
  
  FILE *pImg2 = fopen (file, "wb");
  if (pImg2 == NULL)
  {
    printf("fopen write file failed\n");
    exit(EXIT_FAILURE);
  }
  // read the body
  while (end == 0) 
  {
    count = fread (p, sizeof (char), x*y*3, infile);
    if (count == x*y*3) 
    {
      end = 1;
    }
  }
  /* // write the header
  fprintf(pImg2, "P6\n");
  fprintf(pImg2, "%d %d\n%d", x, y, 255);
  // write the body
  fwrite (p, sizeof (char), x*y*3, pImg2); */
  fclose (pImg2);
}