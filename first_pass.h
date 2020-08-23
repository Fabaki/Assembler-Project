#ifndef FIRST_PASS_H
#define FIRST_PASS_H

void free_memory(char *pointers[], int len);
int parse_symbol(char *s);
int parse_symbol_noend(char *s);
void error_clean(char *words[], int len, int line, char *error, int *rtn);

int first_pass(FILE *file);
int icf, idf;

#endif
