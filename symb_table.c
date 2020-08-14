#include <stdlib.h>
#include <string.h>
#include "assembler.h"

#define HASHSIZE 4

static struct nlist *symbol_table[HASHSIZE];

unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = symbol_table[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->next) == 0)
      return np;
  return NULL;
}

struct nlist *install(char *name, int value, int loc, int type)
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
    np->value = np->loc = np->type = 0;
  np->value = value;
  np->loc = loc;
  np->type = type;
  return np;
}
