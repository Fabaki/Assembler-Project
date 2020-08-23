#ifndef PASSES_H
#define PASSES_H

#define LINE_LEN 82

static char *two_oprands[] = {
  "mov",
  "cmp",
  "add",
  "sub",
  "lea"
};
static const int two_oprands_len = 5;

static char *one_oprand[] = {
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
static const int one_oprand_len = 9;

static char *no_oprand[] = {
  "rts",
  "stop"
};
static const int no_oprand_len = 2;

static char *registers[] = {
  "r0",
  "r1",
  "r2",
  "r3",
  "r4",
  "r5",
  "r6",
  "r7"
};
static const int registers_len = 8;

void free_memory(char *pointers[], int len);
int parse_symbol(char *s);
int parse_symbol_noend(char *s);
void error_clean(char *words[], int len, int line, char *error, int *rtn);

int first_pass(FILE *file);
int icf, idf;

/**
 * does everything regarding the second pass of the assembler
 * @param file - input file the pass reads from
 * @return TRUE if no errors were found during the pass; FALSE if
 */
int second_pass(FILE *file);

#endif
