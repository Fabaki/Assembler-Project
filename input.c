#include <stdlib.h>
#include <string.h>
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

int getline(char s[], int lim)
{
  int c, i;

  i = 0;
  while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}