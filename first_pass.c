#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"
#define LINE_LEN 82

int ic = 100, dc = 0;

int parse()

void free_memory(char *pointers[], int len);

int first_pass(FILE *file)
{
  char line[LINE_LEN];
  int symbol = FALSE;
  int rtn = TRUE;
  int line_num = 0;

  while ((line = get_line(line, LINE_LEN, file)) != EOF)
  {
    int words_in_line = count_line_words(line, LINE_LEN);
    char *words[];

    ++line_num;
    get_line_words(line, LINE_LEN, words);

    int first_word_len = strlen(words[0]);
    if (*(words[0] + first_word_len - 1) == ':')
      symbol = TRUE;
    if (strcmp(words[symbol], ".data") == 0)
    {

      continue;
    }
    else if (strcmp(words[symbol], ".string") == 0)
    {

      continue;
    }
    else if (strcmp(words[symbol], ".entry") == 0)
    {

      continue;
    }
    else if (strcmp(words[symbol], ".extern") == 0)
    {

      continue;
    }
    else if (symbol)
    {
      char label_name[first_word_len];
      strncpy(label_name, words[0], first_word_len - 1);
      if (lookup(label_name) != NULL)
      {
        add_error(line_num, "Label already exists");
        free_memory(words, words_in_line);
        continue;
      }

      install(label_name, ic, CODE, 0);
    }

    if (inarray(words[symbol], two_oprands, two_oprands_len))
    {
      char arg1[32];
      char arg2[32];
      if (words_in_line == 4 + symbol)
      {
        /* The line is hopefully something like "LABEL: mov r1 , r2" */
        if (strcmp(words[2 + symbol], ",") == 0)
        {
          strcpy(arg1, words[1 + symbol]);
          strcpy(arg2, words[3 + symbol]);
        }
        else
        {
          add_error(line_num, "Too many oprands");
          free_memory(words, words_in_line);
          continue;
        }
      }
      else if (words_in_line == 3 + symbol)
      {
        /* Meaning there is (hopefully) a space between the arguments e.g "LABEL: mov r1, r2" */
        if (instring(',', words[1 + symbol], strlen(words[1 + symbol])))
        {
          if (*(words[1 + symbol] + strlen(words[1 + symbol] - 1)) == ',') /* is the last char ',' */
          {
            strncpy(arg1, words[1 + symbol], strlen(words[1 + symbol]) - 1);
            strcpy(arg2, words[2 + symbol]);
          }
          else
          {
            add_error(line_num, "Oprand containing \",\"");
            free_memory(words, words_in_line);
            continue;
          }
        }
        else
        {
          add_error(line_num, "No \",\" between oprands");
          free_memory(words, words_in_line);
          continue;
        }
      }
      else
      {
        add_error(line_num, "Oprand count not met");
        free_memory(words, words_in_line);
        continue;
      }

      int L = 3;

    }
    else if (inarray(words[symbol], one_oprand, one_oprand_len))
    {

    }
    else if (inarray(words[symbol], no_oprand, no_oprand_len))
    {

    }
    else
    {
      add_error(line_num, "Command isn't recognized");
      free_memory(words, words_in_line);
    }
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

void free_memory(char *pointers[], int len)
{
  int i;
  for (i = 0; i < len; i++)
    free(pointers[i]);
}
