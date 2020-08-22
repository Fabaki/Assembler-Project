#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

/*
  ROY: while we don't have a normal input method, this will be here for all of the other testing
*/
char code[] = \
"MAIN: add r3, LIST\n"
"LOOP: prn #48\n"
"      lea STR, r6\n"
"      inc r6\n"
"      mov r3, K\n"
"      sub r1, r4\n"
"      bne END\n"
"      cmp K, #-6\n"
"      bne &END\n"
"      dec K\n"
"      jmp &LOOP\n"
"END:  stop\n"
"STR:  .string \"abcd\"\n"
"LIST: .data 6, -9\n"
"      .data -100\n"
"K:    .data 31\n";

int openfile(FILE *file, char *fname)
{
  char filename[strlen(fname)+3];
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
