#include <stdio.h>
#include "input_manipulator.h"
#include "passes.h"

int main(int argc, char *argv[])
{
  int i;
  FILE *file;
  for (i = 1; i < argc; i++)
  {
    if (!openfile(file, argv[i]))
      continue;
    if (first_pass(file))
      second_pass(file);
  }
  return 0;
}
