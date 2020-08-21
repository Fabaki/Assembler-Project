#ifndef ASSEMBLER_H
#define ASSEMBLER_H

enum symbl_loc { DATA, CODE };
enum symbl_type { ENTRY, EXTERNAL };
enum bool { FALSE, TRUE };

char *two_oprands[] = {
  "mov",
  "cmp",
  "add",
  "sub",
  "lea"
};
const int two_oprands_len = 5;

char *one_oprand[] = {
  "clr",
  "not",
  "inc",
  "dec",
  "jmp",
  "bne",
  "jsr",
  "red",
  "prn"
};
const int one_oprand_len = 9;

char *no_oprand[] = {
  "rts",
  "stop"
};
const int no_oprand_len = 2;

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

struct int24
{
  struct int24 *next;
  unsigned int data : 24;
};

struct int24 *add_word(unsigned char msb, unsigned char mb, unsigned char lsb, int cd);

void openfile(FILE *file, char *fname);
int get_line(char *line, int max, FILE *file);
int count_line_words(char *line, int line_limit);
int get_line_words(char *line, int line_limit, char *buffer[]);

int inarray(char *word, char *array[], int array_length);
int instring(char c, char *word, int word_length);
int strsplit(char word[], int len, char splitter, char word1[], char word2[]);

int add_error(int line, char *e);

int first_pass(FILE *file);

void checkfile(char f[]);

#endif
