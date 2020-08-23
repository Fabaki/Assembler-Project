#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input_manipulator.h"

enum bool { FALSE, TRUE };

FILE *openfile(FILE *file, char *fname)
{
    /* creating string with .as extension */
  char *filename = (char*) calloc(strlen(fname) + 4, sizeof(char));
  char ex[] = ".as";

  strcat(filename, fname);
  strcat(filename, ex);

  file = fopen(filename, "r");

  return file;
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
    /* ignore multiple whitespaces in a row */
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

int get_line_words(char *line, int line_limit, char **buffer)
{
  int i = 0, words = 0;
  char backup, *newword;


  while (line[i] != EOF && line[i] != '\n' && line[i] != '\0' && line_limit > 0)
  {
    while (isspace(line[i]) && line_limit--)
      i++;

    if (line[i] == '\0' || line[i] == EOF || line[i] == '\n' || line_limit <= 0)
      return words;

    if ((isalnum(line[i]) || ispunct(line[i])) && line_limit--)
    {
      *(buffer + words) = &line[i];
      i++;
    }

    while ((isalnum(line[i]) || ispunct(line[i])) && line_limit--)
      i++;

    backup = line[i];
    line[i] = '\0';
    newword = (char *) calloc(strlen(*(buffer + words)) + 1, sizeof(char));
    strcpy(newword, *(buffer + words));
    *(buffer + words) = newword;
    line[i] = backup;

    if ((line[i] == '\0' || line[i] == EOF || line[i] == '\n') &&  (isalnum(line[i - 1]) || ispunct(line[i - 1])) || isspace(line[i]))
      ++words;

    if (line[i] == '\0' || line[i] == EOF || line[i] == '\n' || line_limit <= 0)
      return words;

    if (!isspace(line[i]))
      return -1; /* checking that we stopped because of a space, not because of a non-alphanumeric character */
  }

  return words;
}
