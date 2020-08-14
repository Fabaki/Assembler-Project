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

void openfile(FILE *file, char *fname)
{
  char filename[strlen(fname)+3];
  char ex[] = ".as";

  strcat(filename, fname);
  strcat(filename, ex);
  file = fopen(filename, "r");
}

int get_line(char *line, int max, FILE *file)
{
  if (fgets(line, max, stdin) == NULL)
    return 0;
  else
    return strlen(line);
}

int next_word(char *word, int word_len, char *line, int word_index)
{
  int index_backup = word_index;
  word_len--;
  while (isspace(line[word_index++]))
    ;
  if (line[word_index] != EOF)
    *word++ = line[word_index];
  if (!isalpha(line[word_index]))
  {
    *word = '\0';
    return -1;
  }
  for ( ; --word_len > 0; word++)
    if (!isalnum(*word = line[word_index++]))
      break;
  *word = '\0';
  return word_index - index_backup;
}
