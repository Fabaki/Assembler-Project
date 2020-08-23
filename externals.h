#ifndef EXTERNALS_H
#define EXTERNALS_H

struct extern_symbols
{
  struct extern_symbols *next;
  char *name;
  int value;
};

static struct extern_symbols *first_extern;

/**
 * add a (name;value) pair to the list of external symbols used for the ext file
 * @param name -> name of of the symbol
 * @param value -> value of the symbol
 * @return pointer to external added
 */
struct extern_symbols *add_external(char *name, int value);
struct extern_symbols *get_first_ext();

#endif
