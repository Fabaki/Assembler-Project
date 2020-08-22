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
            /*TODO: there should be an error trigger here but idk how to phrase it */
        }
      }
      /* reaching this line means doing completion of kidud binary part
      (part 6 of second pass)
      lolllll imagine knowing how to do this lololololol
      what even is binary? some kind of a kosher pork suplement?
      */      
  }
}
