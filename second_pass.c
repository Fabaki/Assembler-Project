#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

int second_pass(FILE *file)
{
  int anyEntries = FALSE; /* for entries file - changes to 1 if there are any */
  int anyExterns = FALSE; /* for externs file - changes to 1 if there are any */

  int ic = 100;
  char line[LINE_LEN];
  int startSymbol; /*yes/no boolean to indicate if starts with startSymbol*/
  char *words[];
  while ((line = get_line(line, LINE_LEN, file)) != EOF)
  {
    get_line_words(line, LINE_LEN, words);
    if (*(words[0] + strlen(words[0]) - 1) == ':') //if starts with startSymbol
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

  if (inarray(words[startSymbol], two_oprands, two_oprands_len))
   {
     char arg1[32];
     char arg2[32];
     if (words_in_line == 4 + startSymbol)
     {
       strcpy(arg1, words[1 + startSymbol]);
       strcpy(arg2, words[3 + startSymbol]);
     }
     else if (words_in_line == 3 + startSymbol)
     {
       /* Meaning there is (hopefully) a space between the arguments e.g "LABEL: mov r1, r2" */
         if (*(words[1 + startSymbol] + strlen(words[1 + startSymbol] - 1)) == ',') /* is the last char ',' */
         {
           strncpy(arg1, words[1 + startSymbol], strlen(words[1 + startSymbol]) - 1);
           strcpy(arg2, words[2 + startSymbol]);
         }
         else if (*(words[2 + startSymbol]) == ',') /* is the first char of second arg ',' */
         {
           strcpy(arg1, words[1 + startSymbol]);
           strcpy(arg1, words[2 + startSymbol] + 1);
         }
       }
     }

     if (inarray(arg1, registers, registers_len))
      {
        src_reg = (unsigned char) (arg1[1] - '0'); /* if the arg1 is in the registers, its format is for sure rX */
        src_type = 3;
        --l;
      }
      else if (arg1[0] == '#')
      {
        src_type = 0;
        value1 = atoi(&(arg1[1]));
        are2 = 4;
      }
  }
}
