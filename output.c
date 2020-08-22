#include <stdlib.h>
#include "assembler.h"

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

   /* assuming a list of ent is created, maybe done by by storing ent names
   but I still don't know how that's gonna turn out */

   int pairln = 0;
   entpair pairs[];
   for (int i = 0; i < pairln; i++)
   {
     fprintf(extfile, "%s %07d", pairs[i].name, pairs[i].value);
   }
   fclose(entfile);
}

void create_ext(char fname[], int len)
{
    char extname[strlen(fname) + 4];
    char ext[] = ".ext";

    strcat(extname, fname);
    strcat(extname, ext);

   FILE *extfile;
   extfile = fopen(extname, "w");

   /* assuming a list of ext - ic values is somehow recived: let them be this:*/
   int pairln = 0;
   extpair pairs[];
   for (int i = 0; i < pairln; i++)
   {
     fprintf(extfile, "%s %07d", pairs[i].name, pairs[i].value);
   }
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
