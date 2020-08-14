#include <stdlib.h>
#include "assembler.h"

int ic = 100, dc = 0;

int parse_symbol(char *s);
int parse_memory(char *m);
int parse_command(char *c);

int first_pass()
{
  char *c[4]; /* There are 4 words (seperated by space) at most */
  int line;
  int symbol = FALSE;
  int rtn = TRUE;

  while ((line = get_line_words(c)) != EOF)
  {
    if (c[3] != NULL) /* Meaning there is a symbol */
    {
      symbol = TRUE;
      rtn = parse_symbol(c[0]);
    }
    if (*(c[symbol]) == '.')
      rtn = parse_memory(c[symbol]);
    else
      rtn = parse_command(c[symbol]);
  }
}

int parse_symbol(char *s)
{

}

int parse_memory(char *s)
{

}

int parse_command(char *s)
{

}
