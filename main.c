#include <stdio.h>
#include "input_manipulator.h"
#include "passes.h"
#include "output.h"
#include "errors.h"

int main(int argc, char *argv[])
{
  int i;
  FILE *file = NULL;
  for (i = 1; i < argc; i++)
  {
    if (!openfile(file, argv[i]))
      continue;
    if (first_pass(file))
      second_pass(file);

    if (error_count != 0)
    {
      printf("Errors found at file %s:\n", argv[i]);
      print_errors();
    }
    else
      create_output(argv[i]);
    printf("\n");
  }
  return 0;
}
