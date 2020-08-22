#ifndef MEMORY_STRUCTURE_H
#define MEMORY_STRUCTURE_H

struct int24
{
  struct int24 *next;
  unsigned int data : 24;
};

static struct int24 *first_code;
static struct int24 *first_data;

struct int24 *add_word(unsigned char msb, unsigned char mb, unsigned char lsb, int cd); /* all bytes, and code (0) or data (everthing else) */
void change_word(struct int24 *p, unsigned char msb, unsigned char mb, unsigned char lsb, int cd);
struct int24 *find_word_at(unsigned int ic, int cd);

#endif
