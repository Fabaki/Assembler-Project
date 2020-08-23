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

/**
 * finds an item in the symbol table based on its name
 * @param name -> the name that its looked for
 * @return pointer to the struct reperesnting the found item
 */
struct nlist *lookup(char *name);

/**
 * add a new item to the symbol table based on all of its values
 * @param name
 * @param value
 * @param loc
 * @param has_type set to TRUE if is ent or ext
 * @param type ent(0)/ext(1)
 * @return
 */
struct nlist *install(char *name, int value, int loc, int has_type, int type);

struct nlist **get_symbol_table();

#endif
