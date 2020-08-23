#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "output.h"
#include "symb_table.h"
#include "externals.h"
#include "memory_structure.h"
#include "errors.h"
#include "passes.h"

enum bool { FALSE, TRUE };

void create_output(char *fname)
{
  printf("Creating output for file |%s|!\n", fname);
  int len = strlen(fname);

  create_ob(fname, len);
  create_ent(fname, len);
  create_ext(fname, len);
}

void create_ent(char *fname, int len)
{
  char *entname = (char*) calloc(strlen(fname) + 5, sizeof(char));
  char ent[] = ".ent";
  int file_exists = FALSE;
  FILE *entfile;
  int i;

  strcat(entname, fname);
  strcat(entname, ent);

  printf("Final entry name |%s|\n", entname);

  struct nlist **table = get_symbol_table();

    printf("output.c ->   ************ Going through symbol table\n");
  for (i = 0; i < HASHSIZE; i++) /* go through all 4 "cells" in symb table */
  {
    struct nlist *np = *(table + i);
    for (; np != NULL; np = np->next) /* for each cell check each symbol */
    {
      printf("name: %s value: %d\n", np->name, np->value);
      if (np->has_type) {
          if (np->type == ENTRY) {
              if (!file_exists) {
                  entfile = fopen(entname, "w");
                  file_exists = TRUE;
              }
              fprintf(entfile, "%s %07d\n", np->name, np->value);
          }
      }
    }
  }

  if (file_exists)
    fclose(entfile);
}

void create_ext(char *fname, int len)
{
  char *extname = (char*) calloc(strlen(fname) + 5, sizeof(char));
  char ext[] = ".ext";
  FILE *extfile;

  struct extern_symbols *el = get_first_ext();
  if (el == NULL)
    return;

  strcat(extname, fname);
  strcat(extname, ext);

  printf("Final extern name |%s|\n", extname);

  extfile = fopen(extname, "w");

  for(;el != NULL; el = el->next)
  {
      printf("Print called in ext very cool\n");
    fprintf(extfile, "%s %07d\n", el->name, el->value);
  }

  fclose(extfile);
}

void create_ob(char *fname, int len)
{
  char *obname = (char *) calloc(strlen(fname) + 4, sizeof(char));
  char ob[] = ".ob";
  static struct int24 *p;
  int i;
  FILE *obfile;

  strcat(obname, fname);
  strcat(obname, ob);

  printf("Final name file: |%s|\n", obname);

  obfile = fopen(obname, "w");

  fprintf(obfile, "%d %d\n", icf - 100, idf);

  for (p = get_first(0), i = 100; p != NULL; p = p->next, i++)
    fprintf(obfile, "%07d %06x\n", i, p->data);
  for (p = get_first(1); p != NULL; p = p->next, i++)
  {
    fprintf(obfile, "%07d %06x\n", i, p->data);
  }

  fclose(obfile);
}
