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
    int word_index;
    char word[32];

    int next_word_len = next_word(word, 32, line, word_index);
    if (next_word_len == -1)
    {
      add_error(line, "un-alphanumerical character found");
      continue;
    }
    word_index += next_word_len;

    if (word[0] == '.')
      parse_memory(word);
    else if (word[next_word_len - 1] == ':')
      parse_symbol(word);
    else
      parse_command(word);
  }

  return rtn;
}

int parse_symbol(char *s);
int parse_memory(char *m);
int parse_command(char *c);

int parse_symbol(char *s)
{
  if (!isalpha(s[0]))
    return 0;
  
}

int parse_memory(char *c[], int symbol)
{

}

int parse_command(char *c[], int symbol)
{

}
