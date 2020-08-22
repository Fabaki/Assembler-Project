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

   
}

void create_ext(char fname[], int len)
{
    char extname[strlen(fname) + 4];
    char ext[] = ".ext";

    strcat(extname, fname);
    strcat(extname, ext);

   FILE *extfile;
   extfile = fopen(extname, "w");
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
