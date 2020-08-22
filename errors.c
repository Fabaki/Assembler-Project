#include <stdlib.h>
#include "errors.h"

struct error *add_error(char *error, int line)
{
  ++error_count;
  struct error *np;

  np = (struct error *) malloc(sizeof(struct error));
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
  char *error_copy = (char *) malloc(sizeof(char) * (strlen(error) + 1));
  np->error = error_copy;

  return np;
}

void print_errors()
{
  struct error *p = error_list;

  for (; p != NULL; p = p->next)
    printf("Error on line %d: %s.\n", p->line, p->error);
}
