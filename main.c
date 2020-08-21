#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;
  FILE *file;
  /* loop through all file names recived as arguments and assemble each one
  individualy */
  for (i = 1; i < argc; i++)
  {
    if (!openfile(file, argv[i]))
      continue; /* add some kind of error indicating that the file does not
      exist / couldn't be accessed */
    if (first_pass(file))
      second_pass(file); /* add */
  }

  return 0;
}
