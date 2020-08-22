#include <stdlib.h>
#include <string.h>
#include "externals.h"

struct extern_symbols *add_external(char *name, int value)
{
  struct extern_symbols *np;
  unsigned result;

  np = (struct extern_symbols *) malloc(sizeof(struct extern_symbols));
  if (np == NULL)
    return NULL;

  if (first_extern == NULL)
    first_extern = np;
  else
  {
    struct extern_symbols *p = first_extern;
    while (p->next != NULL)
      p = p->next;
    p->next = np;
  }

  np->next = NULL;
  char *copyname = (char *) malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(copyname, name);
  np->name = copyname;
  np->value = value;

  return np;
}
