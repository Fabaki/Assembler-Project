#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input_manipulator.h"

enum bool { FALSE, TRUE };

int openfile(FILE *file, char *fname)
{
  char filename[strlen(fname)+4];
  char ex[] = ".as";

  strcat(filename, fname);
  strcat(filename, ex);
  if (file = fopen(filename, "r"))
    return TRUE;
  else
    return FALSE;
}

int get_line(char *line, int max, FILE *file)
{
  if (fgets(line, max, file) == NULL)
    return EOF;
  else
    return strlen(line);
}

int count_line_words(char *line, int line_limit)
{
  int i = 0;
  int words = 0;
  while (line[i] != EOF && line[i] != '\n' && line[i] != '\0' && line_limit > 0)
  {
    while (isspace(line[i]) && line_limit--)
      i++;

    if (line[i] == '\0' || line[i] == EOF || line[i] == '\n' || line_limit <= 0)
      return words;

    while ((isalnum(line[i]) || ispunct(line[i])) && line_limit--)
      i++;

    if ((line[i] == '\0' || line[i] == EOF || line[i] == '\n') &&  (isalnum(line[i - 1]) || ispunct(line[i - 1])) || isspace(line[i]))
      ++words;

    if (line[i] == '\0' || line[i] == EOF || line[i] == '\n' || line_limit <= 0)
      return words;

    if (!isspace(line[i]))
      return -1; /* checking that we stopped because of a space, not because of a non-alphanumeric character */
  }

  return words;
}

int get_line_words(char *line, int line_limit, char *buffer[])
{
  int i = 0;
  int words = 0;
  while (line[i] != EOF && line[i] != '\n' && line[i] != '\0' && line_limit > 0)
  {
    while (isspace(line[i]) && line_limit--)
      i++;

    if (line[i] == '\0' || line[i] == EOF || line[i] == '\n' || line_limit <= 0)
      return words;

    if ((isalnum(line[i]) || ispunct(line[i])) && line_limit--)
    {
      buffer[words] = &line[i];
      i++;
    }

    while ((isalnum(line[i]) || ispunct(line[i])) && line_limit--)
      i++;

    char backup = line[i];
    line[i] = '\0';
    char *newword = (char *) malloc(strlen(buffer[words])+1);
    strcpy(newword, buffer[words]);
    buffer[words] = newword;
    line[i] = backup;

    if ((line[i] == '\0' || line[i] == EOF || line[i] == '\n') && (isalnum(line[i - 1]) || ispunct(line[i - 1])) || isspace(line[i]))
      ++words;

    if (line[i] == '\0' || line[i] == EOF || line[i] == '\n' || line_limit <= 0)
      return words;

    if (!isspace(line[i]))
      return -1; /* checking that we stopped because of a space, not because of a non-alphanumeric character */
  }

  return words;
}
