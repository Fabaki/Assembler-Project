#include <stdio.h>
#include "input_manipulator.h"
#include "passes.h"
#include "output.h"
#include "errors.h"

int main(int argc, char *argv[])
{
  int error_count = 0;
  int i;
  FILE *file = NULL;

  /* go through each file name received as an argument and treat them individually */
  for (i = 1; i < argc; i++)
  {
    file = openfile(file, argv[i]);
    if (file == NULL)
    {
      printf("Error: file doesn't exist\n");
      continue;
    }
    if (first_pass(file)) {
        fclose(file);
        file = openfile(file, argv[i]);
        second_pass(file);
    }

    if (get_error_count() != 0)
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
