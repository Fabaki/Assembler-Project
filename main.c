#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;
  FILE *file;
  for (i = 1; i < argc; i++)
  {
    openfile(file, argv[i]);
    if (first_pass(file))
      second_pass(file); /* add */
    
  }
  return 0;
}
