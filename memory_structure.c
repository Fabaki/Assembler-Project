#include <stdlib.h>
#include <string.h>
#include "assembler.h"

static struct int24 *first_code;
static struct int24 *first_data;

struct int24 *add_word(unsigned char msb, unsigned char mb, unsigned char lsb, int cd) /* all bytes, and code (0) or data (everthing else) */
{
  struct int24 *np;
  unsigned result;

  np = (struct int24 *) malloc(sizeof(*np));
  if (np == NULL)
    return NULL;

  struct int24 *first_func = cd == 0 ? first_code : first_data;
  if (first_func == NULL)
    first_func = np;
  else
  {
    struct int24 *p = first_func;
    for (; p->next != NULL; p++)
      p = p->next;
    p->next = np;
  }


  np->next = NULL;

  np->data = msb;
  np->data = (np->data << 8) | mb;
  np->data = (np->data << 8) | lsb;

  return np;
}

struct int24 *find_word_at(int ic, int cd)
{
  if (ic > 100)
    ic -= 100;
  struct int24 *p = cd == 0 ? first_code : first_data;
  for (; ic > 0; ic--)
    p++;
  return p;
}
