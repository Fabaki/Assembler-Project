#include <stdlib.h>
#include <string.h>
#include "assembler.h"

static struct int24 *first_code;
static struct int24 *first_data;

struct int24 *add_word(unsigned char msb, unsigned char mb, unsigned char lsb, int cd) /* all bytes, and code (0) or data (everthing else) */
{
  struct int24 *np;
  unsigned result;

  np = (struct int24 *) malloc(sizeof(struct int24));
  if (np == NULL)
    return NULL;

  struct int24 *first_func;
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
  np->data = msb;
  np->data = (np->data << 8) | mb;
  np->data = (np->data << 8) | lsb;
}

struct int24 *find_word_at(unsigned int ic, int cd)
{
  struct int24 *p = (cd == 0 ? first_code : first_data);
  for (; ic > 0; ic--)
    p = p->next;

  return p;
}
