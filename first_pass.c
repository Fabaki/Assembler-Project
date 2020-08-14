#include <stdlib.h>
#include <string.h>
#include "assembler.h"

int ic = 100, dc = 0;

int parse_symbol(char *s);
int parse_memory(char *m);
int parse_command(char *c);

int first_pass()
{
  char c[80];
  int line;
  int word;
  int symbol = FALSE;
  int rtn = TRUE;

  while ((line = get_line(c)) != EOF)
  {
    if (c[3] != NULL) /* Meaning there should be a symbol */
      symbol = TRUE;
  }

  return rtn;
}

int parse_symbol(char *s)
{

}

int parse_memory(char *c[], int symbol)
{


}

int parse_command(char *c[], int symbol)
{

}
