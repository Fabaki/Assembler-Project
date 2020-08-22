#ifndef SYMB_TABLE_H
#define SYMB_TABLE_H

#define HASHSIZE 4

enum symbl_loc { DATA, CODE };
enum symbl_type { ENTRY, EXTERN };

struct nlist
{
  struct nlist *next;
  char *name;
  int value;
  unsigned int loc : 1; /* Location: Code (1) or data (0) */
  unsigned int has_type : 1; /* Is there a type? */
  unsigned int type : 1; /* Entry (0) or External (1) */
};

static struct nlist *symbol_table[HASHSIZE];
unsigned hash(char *s);
struct nlist *lookup(char *name);
struct nlist *install(char *name, int value, int loc, int has_type, int type);

#endif
