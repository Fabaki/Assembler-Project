#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

int second_pass(FILE *file)
{
  int anyEntries = FALSE; /* for entries file - changes to 1 if there are any */
  int anyExterns = FALSE; /* for externs file - changes to 1 if there are any */
  char line[LINE_LEN];
  int startSymbol; //yes/no boolean to indicate if starts with symbol
  char *words[];
  while ((line = get_line(line, LINE_LEN, file)) != EOF)
  {
    get_line_words(line, LINE_LEN, words);
    if (*(words[0] + strlen(words[0]) - 1) == ':') //if starts with symbol
      startSymbol = TRUE;
    else
      startSymbol = FALSE;

      if (strcmp(words[startSymbol], ".data") == 0)
      continue;
      if (strcmp(words[startSymbol], ".string") == 0)
      continue;
      if (strcmp(words[startSymbol], ".extern") == 0)
      {
       anyExterns = TRUE;
      }
      if (strcmp(words[startSymbol], ".entry") == 0)
      {
        anyEntries = TRUE;
        /* do entry thing - unless I am DAPAR 30 I'm pretty certain
        that it asks for you to edit an existing value in the symb table,
        and from what Iv'e seen it can't do that yet */
        continue
      }
      /* reaching this line means doing completion of kidud binary part */
  }
}

void create_output(char fname[], int anyEntries, int anyExterns)
{
  int len = strlen(fname);

  if(anyEntries)
    {
      char entname[strlen(fname) + 4];
      char ent[] = ".ent";

      strcat(entname, fname);
      strcat(entname, ent);

     FILE *entfile;
     entfile = fopen(entname, "w");


    }

  if (anyExterns)
    {
      char extname[strlen(fname) + 4];
      char ext[] = ".ext";

      strcat(extname, fname);
      strcat(extname, ext);

     FILE *extfile;
     extfile = fopen(extname, "w");
    }

    char obname[strlen(fname) + 3];
    char ob[] = ".ob";

    strcat(obname, fname);
    strcat(obname, ob);

   FILE *obfile;
   obfile = fopen(obname, "w");
  /* create actual obj */
}
