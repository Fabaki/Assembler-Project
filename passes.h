#ifndef PASSES_H
#define PASSES_H

#define LINE_LEN 82

void free_memory(char *pointers[], int len);
int parse_symbol(char *s);
void error_clean(char *words[], int len, int line, char *error, int *rtn);

int first_pass(FILE *file);
int icf, dcf;

int second_pass(FILE *file);

#endif
