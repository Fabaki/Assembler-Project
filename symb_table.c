#include <stdlib.h>

struct nlist
{
  struct nlist *next;
  char *name;
  int value;
  unsigned int loc : 1;
  unsigned int type : 1;
};

#define HASHSIZE 4

static struct nlist *hashtab[HASHSIZE]

unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval += *s;
  return hashval % HASHSIZE;
}
