#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

int ic = 100, dc = 0;

int parse()

int first_pass(FILE *file)
{
  char line[82];
  int symbol = FALSE;
  int rtn = TRUE;

  while ((line = get_line(line, 82, file)) != EOF)
  {
    
  }

  return rtn;
}

int parse_symbol(char *line[], int line_len);
int parse_memory(char *line[], int line_len, int symbol);
int parse_command(char *line[], int line_len, int symbol);

int parse_symbol(char *s)
{
  int i;

  if (!isalpha(s[0]))
    return 0;
  for (i = 1; isalnum(s[i]); i++)
    ;
  if (s[i] != ':') /* checking if all label chars are alphanumeric */
    return 0;
  if (lookup(s) != NULL)
    return -1;
  return 1;
}

int parse_memory(char *m, int symbol)
{
  int word_index = 0;
  char buffer[8];
  word_index += next_word(buffer, 8, m, word_index);
  if (strcmp(buffer, ".data") == 0)
  {

  }
  else if (strcmp(buffer, ".string") == 0)
  {

  }
  else if (strcmp(buffer, ".entry") == 0)
  {

  }
  else if (strcmp(buffer, ".extern") == 0)
}

int parse_command(char *c, int symbol)
{

}
