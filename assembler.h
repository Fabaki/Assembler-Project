#ifndef ASSEMBLER_H
#define ASSEMBLER_H

/*
  External variables
*/
enum symbl_loc { DATA, CODE };
enum symbl_type { ENTRY, EXTERNAL };
enum bool { FALSE, TRUE };

struct nlist
{
  struct nlist *next;
  char *name;
  int value;
  unsigned int loc : 1;
  unsigned int type : 1;
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, int value, int loc, int type);

void openfile(FILE *file, char *fname);

int get_line(char c[], int index);
int next_word(char *word, int word_len, char *line, int word_index)

int add_error(int line, char *e);

int first_pass();

void checkfile(char f[]);

#endif
