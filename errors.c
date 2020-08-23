#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errors.h"

static int error_count = 0;

/* struct representing an error string as a part of a node making a linked list */
struct error
{
  struct error *next;
  char *error;
  int line;
};

struct error *error_list;

struct error *add_error(char *error, int line)
{
  struct error *np;
  char *error_copy;

  ++error_count;

  np = (struct error *) calloc(1, sizeof(struct error));
  if (np == NULL)
    return NULL;

  if (error_list == NULL)
    error_list = np;

  if (error_list != np)
  {
    struct error *p = error_list;
    while (p->next != NULL)
      p = p->next;
    p->next = np;
  }

  np->next = NULL;
  np->line = line;
  error_copy = (char *) calloc(strlen(error) + 1, sizeof(char));
  strcpy(error_copy, error);
  np->error = error_copy;

  return np;
}

void print_errors()
{
  struct error *p = error_list;

  for (; p != NULL; p = p->next)
    printf("Error on line %d: %s.\n", p->line, p->error);
}

int get_error_count()
{
  return error_count;
}
