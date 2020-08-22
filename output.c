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
  int len = strlen(fname);

  create_ob(fname, len);
  create_ent(fname, len);
  create_ext(fname, len);
}

void create_ent(char *fname, int len)
{
  char* entname = (char*)malloc((strlen(fname) + 5)*sizeof(char*));
  char ent[] = ".ent";
  int file_exists = FALSE;

  strcat(entname, fname);
  strcat(entname, ent);

  FILE *entfile;


  int i;
  for (i = 0; i < HASHSIZE; i++) /* go through all 4 "cells" in symb table */
  {
    struct nlist *np = symbol_table[i];
    for (; np != NULL; np = np->next) /* for each cell check each symbol */
    {
      if (np->has_type)
        if (np->type == ENTRY)
        {
          if (!file_exists)
          {
            entfile = fopen(entname, "w");
            file_exists = TRUE;
          }
          fprintf(entfile, "%s %07d", np->name, np->value);
        }
    }
  }

  if (file_exists)
    fclose(entfile);
}

void create_ext(char *fname, int len)
{
  char* extname = (char*)malloc((strlen(fname) + 5)*sizeof(char*));
  char ext[] = ".ext";
  struct extern_symbols *el;
  if (first_extern == NULL)
    return;

  strcat(extname, fname);
  strcat(extname, ext);

  FILE *extfile;
  extfile = fopen(extname, "w");

  for(el = first_extern; el != NULL; el = el->next)
    fprintf(extfile, "%s %07d", el->name, el->value);

  fclose(extfile);
}

void create_ob(char *fname, int len)
{
  char* obname = (char*)malloc((strlen(fname) + 4)*sizeof(char*));
  char ob[] = ".ob";
  static struct int24 *p;
  int i;

  strcat(obname, fname);
  strcat(obname, ob);

  FILE *obfile;
  obfile = fopen(obname, "w");

  fprintf(obfile, "%d %d", icf - 100, idf);
  for (p = first_code, i = 100; p != NULL; p = p->next, i++)
    fprintf(obfile, "%07d %06x", i, p->data);
  for (p = first_data; p != NULL; p = p->next, i++)
    fprintf(obfile, "%07d %06x", i, p->data);

  fclose(obfile);
}
