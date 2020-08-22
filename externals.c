#include <stdlib.h>
#include <string.h>
#include "externals.h"

struct extern_symbols *add_external(char *name, int value)
{
  struct extern_symbols *np;
  char *copyname;

  if (find_extern(name) != NULL)
    return NULL;

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
  copyname = (char *) malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(copyname, name);
  np->name = copyname;
  np->value = value;

  return np;
}

struct extern_symbols *find_extern(char *name)
{
  struct extern_symbols *np = first_extern;
  for (; np != NULL && strcmp(np->name, name) != 0; np = np->next)
    ;
  return np;
}
