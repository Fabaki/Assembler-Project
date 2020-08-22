#include <stdlib.h>
#include <string.h>
#include "symb_table.h"

unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *name)
{
  struct nlist *np;

  for (np = symbol_table[hash(name)]; np != NULL; np = np->next)
    if (strcmp(name, np->next) == 0)
      return np;
  return NULL;
}

struct nlist *install(char *name, int value, int loc, int has_type, int type)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL)
  {
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = symbol_table[hashval];
    symbol_table[hashval] = np;
  }
  else
    return NULL;

  np->value = value;
  np->loc = loc;
  np->has_type = has_type;
  np->type = type;
  return np;
}
