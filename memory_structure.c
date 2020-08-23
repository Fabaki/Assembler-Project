#include <stdlib.h>
#include "memory_structure.h"

struct int24 *add_word(unsigned char msb, unsigned char mb, unsigned char lsb, int cd)
{
  struct int24 *np, *first_func;

  np = (struct int24 *) calloc(1, sizeof(struct int24));
  if (np == NULL)
    return NULL;

  if (cd == 0)
  {
    if (first_code == NULL)
      first_code = np;
    first_func = first_code;
  }
  else
  {
    if (first_data == NULL)
      first_data = np;
    first_func = first_data;
  }

  if (first_func != np)
  {
    struct int24 *p = first_func;
    while (p->next != NULL)
      p = p->next;
    p->next = np;
  }

  np->next = NULL;

  np->data = msb;
  np->data = (np->data << 8) | mb;
  np->data = (np->data << 8) | lsb;

  return np;
}

void change_word(struct int24 *p, unsigned char msb, unsigned char mb, unsigned char lsb, int cd)
{
  p->data = msb;
  p->data = (p->data << 8) | mb;
  p->data = (p->data << 8) | lsb;
}

struct int24 *find_word_at(unsigned int ic, int cd)
{
  struct int24 *p = (cd == 0 ? first_code : first_data);
  for (; ic > 0; ic--)
    p = p->next;

  return p;
}

struct int24 *get_first(int cd)
{
  return (cd == 0) ? first_code : first_data;
}
