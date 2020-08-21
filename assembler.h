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

char *registers[] = {
  "r0",
  "r1",
  "r2",
  "r3",
  "r4",
  "r5",
  "r6",
  "r7"
};
const int registers_len = 8;

struct nlist
{
  struct nlist *next;
  char *name;
  int value;
  unsigned int loc : 1; /* Location: Code (1) or data (0) */
  unsigned int has_type : 1; /* Is there a type? */
  unsigned int type : 1; /* Entry (0) or External (1) */
};

struct nlist *lookup(char *name);
struct nlist *install(char *name, int value, int loc, int has_type, int type);

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
int *stoi(char s[]);

int add_error(int line, char *e);

int first_pass(FILE *file);

void checkfile(char f[]);

unsigned char *get_opcode_funct(char *cmd);
long long decimal_to_binary(int n);

#endif
