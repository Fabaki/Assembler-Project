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
       continue;
      }
      if (strcmp(words[startSymbol], ".entry") == 0)
        {
        anyEntries = TRUE;

            struct nlist *np;
            np = lookup(words[startSymbol+1]);
            if (np != NULL)
            {
              np->has_type = 1;
              np->type = 0; /* set it to entry */
            }
            /*TODO: there should be an error trigger here */
        }
      }
      /* reaching this line means doing completion of kidud binary part

      lolllll imagine knowing how to do this lololololol
      what even is binary? some kind of a kosher pork suplement?
      */
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
