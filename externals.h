#ifndef EXTERNALS_H
#define EXTERNALS_H

struct extern_symbols
{
  struct extern_symbols *next;
  char *name;
  int value;
};

static struct extern_symbols *first_extern;
struct extern_symbols *add_external(char *name, int value);
struct extern_symbols *find_extern(char *name);
struct extern_symbols *get_first_ext();

#endif