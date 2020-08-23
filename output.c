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
  printf("Creating output for file %s\n", fname);

  create_ob(fname);
  create_ent(fname);
  create_ext(fname);
}

void create_ent(char *fname)
{
  char *entname = (char*) calloc(strlen(fname) + 5, sizeof(char));
  char ent[] = ".ent";
  int file_exists = FALSE;
  FILE *entfile;
  int i;

  strcat(entname, fname);
  strcat(entname, ent);

  struct nlist **table = get_symbol_table();

  for (i = 0; i < HASHSIZE; i++) /* go through all 4 "cells" in symb table */
  {
    struct nlist *np = *(table + i);
    for (; np != NULL; np = np->next) /* for each cell check each symbol */
    {
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

void create_ext(char *fname)
{
  char *extname = (char*) calloc(strlen(fname) + 5, sizeof(char));
  char ext[] = ".ext";
  FILE *extfile;

  struct extern_symbols *el = get_first_ext();
  if (el == NULL)
    return;

  strcat(extname, fname);
  strcat(extname, ext);

  extfile = fopen(extname, "w");

  for(;el != NULL; el = el->next)
    fprintf(extfile, "%s %07d\n", el->name, el->value);

  fclose(extfile);
}

void create_ob(char *fname)
{
  char *obname = (char *) calloc(strlen(fname) + 4, sizeof(char));
  char ob[] = ".ob";
  static struct int24 *p;
  int i;
  FILE *obfile;

  strcat(obname, fname);
  strcat(obname, ob);

  obfile = fopen(obname, "w");

  fprintf(obfile, "%d %d\n", icf - 100, idf);

  for (p = get_first(0), i = 100; p != NULL; p = p->next, i++)
    fprintf(obfile, "%07d %06x\n", i, p->data);
  for (p = get_first(1); p != NULL; p = p->next, i++)
    fprintf(obfile, "%07d %06x\n", i, p->data);

  fclose(obfile);
}
