#include <stdlib.h>
#include <stdio.h> /* delete when removing prints */
#include <string.h>
#include "externals.h"

struct extern_symbols *add_external(char *name, int value)
{
  struct extern_symbols *np;
  char *copyname;

  np = (struct extern_symbols *) calloc(1, sizeof(struct extern_symbols));
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
  copyname = (char *) calloc(strlen(name) + 1, sizeof(char));
  strcpy(copyname, name);
  np->name = copyname;
  np->value = value;

  return np;
}

struct extern_symbols *get_first_ext()
{
  return first_extern;
}
