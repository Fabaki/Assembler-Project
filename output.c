#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "output.h"
#include "symb_table.h"
#include "externals.h"

int add_error(int line, char *e)
{

}

void create_output(char fname[], int anyEntries, int anyExterns)
{
  int len = strlen(fname);

  create_ob(fname, len);
  if (anyEntries)
    create_ent(fname, len);
  if (anyExterns)
    create_ext(fname, len);
}

void create_ent(char fname[], int len)
{
    char entname[strlen(fname) + 4];
    char ent[] = ".ent";

    strcat(entname, fname);
    strcat(entname, ent);

   FILE *entfile;
   entfile = fopen(entname, "w");

   int i;
   for (i = 0; i < HASHSIZE; i++) /* go through all 4 "cells" in symb table */
   {
     np = symbol_table[i];
     for (; np != NULL; np = np->next) /* for each cell check each symbol */
     {
       if (np.has_type)
        if (np.type == 0)
          fprintf(extfile, "%s %07d", pairs[i].name, pairs[i].value);
     }
   }

   fclose(extfile);
}

void create_ext(char fname[], int len)
{
    char extname[strlen(fname) + 4];
    char ext[] = ".ext";

    strcat(extname, fname);
    strcat(extname, ext);

   FILE *extfile;
   extfile = fopen(extname, "w");

   for(el = first_extern; el != null; el = el->next)
     fprintf(extfile, "%s %07d", el.name, el.value);

   fclose(extfile);
}

void create_ob(char fname[], int len)
{
  char obname[strlen(fname) + 3];
  char ob[] = ".ob";

  strcat(obname, fname);
  strcat(obname, ob);

 FILE *obfile;
 obfile = fopen(obname, "w");
}
