#ifndef ERRORS_H
#define ERRORS_H

static int error_count = 0;

struct error
{
  struct error *next;
  char *error;
  int line;
} error_list;

struct error *add_error(char *error, int line);
void print_errors();

#endif
