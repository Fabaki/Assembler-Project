#include <stdlib.h>

int main(int argc, char *argv[])
{
  int i;
  for (int i = 1; i < argc; i++)
  {
      checkfile(argv[1]);
  }
  return 0;
}
