#ifndef PASSES_H
#define PASSES_H

#define LINE_LEN 82

char *two_oprands[] = {
  "mov",
  "cmp",
  "add",
  "sub",
  "lea"
};
const int two_oprands_len = 5;

char *one_oprand[] = {
  "clr",
  "not",
  "inc",
  "dec",
  "jmp",
  "bne",
  "jsr",
  "red",
  "prn"
};
const int one_oprand_len = 9;

char *no_oprand[] = {
  "rts",
  "stop"
};
const int no_oprand_len = 2;

char *registers[] = {
  "r0",
  "r1",
  "r2",
  "r3",
  "r4",
  "r5",
  "r6",
  "r7"
};
const int registers_len = 8;

void free_memory(char *pointers[], int len);
int parse_symbol(char *s);
void error_clean(char *words[], int len, int line, char *error, int *rtn);

int first_pass(FILE *file);
int icf, dcf;

int second_pass(FILE *file);

#endif
