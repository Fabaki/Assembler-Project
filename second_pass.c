#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "passes.h"
#include "input_manipulator.h"
#include "string_manipulator.h"
#include "memory_structure.h"
#include "output.h"
#include "symb_table.h"

enum bool { FALSE, TRUE };

int second_pass(FILE *file)
{
  int rtn = TRUE;

  int ic = 100;
  int l;
  unsigned char are2, are3;
  char line[LINE_LEN];
  int symbol; /* yes/no boolean to indicate if the line has a symbol */
  int line_num = 0;

  while (get_line(line, LINE_LEN, file) != EOF)
  {
    int words_in_line = count_line_words(line, LINE_LEN);
    char *words[words_in_line];
    get_line_words(line, LINE_LEN, words);
    ++line_num;

    if (parse_symbol(words[0])) /* if starts with has_symbol */
      symbol = TRUE;
    else
      symbol = FALSE;

    if (strcmp(words[symbol], ".data") == 0)
      continue;
    if (strcmp(words[symbol], ".string") == 0)
      continue;
    if (strcmp(words[symbol], ".extern") == 0)
      continue;
    if (strcmp(words[symbol], ".entry") == 0)
    {
      struct nlist *np;
      np = lookup(words[symbol+1]);
      if (np != NULL)
      {
        np->has_type = TRUE;
        np->type = ENTRY; /* set it to entry */
      }
      else
      {
        error_clean(words, words_in_line, line_num, "Label not found", &rtn);
        continue;
      }
    }
      /* reaching this line means doing completion of kidud binary part
      (part 6 of second pass)
      lolllll imagine knowing how to do this lololololol
      what even is binary? some kind of a kosher pork suplement?
      */

      if (inarray(words[symbol], two_oprands, two_oprands_len))
      {
        char arg1[32];
        char arg2[32];
        if (words_in_line == 4 + symbol)
        {
          /* The line is hopefully something like "LABEL: mov r1 , r2" */
          if (strcmp(words[2 + symbol], ",") == 0)
          {
            strcpy(arg1, words[1 + symbol]);
            strcpy(arg2, words[3 + symbol]);
          }
          else
          {
            error_clean(words, words_in_line, line_num, "Too many oprands", &rtn);
            continue;
          }
        }
        else if (words_in_line == 3 + symbol)
        {
          /* Meaning there is (hopefully) a space between the arguments e.g "LABEL: mov r1, r2" */
          if (instring(',', words[1 + symbol], strlen(words[1 + symbol])))
          {
            if (*(words[1 + symbol] + strlen(words[1 + symbol] - 1)) == ',') /* is the last char ',' */
            {
              strncpy(arg1, words[1 + symbol], strlen(words[1 + symbol]) - 1);
              strcpy(arg2, words[2 + symbol]);
            }
            else if (*(words[2 + symbol]) == ',') /* is the first char of second arg ',' */
            {
              strcpy(arg1, words[1 + symbol]);
              strcpy(arg1, words[2 + symbol] + 1);
            }
          }
        }

        l = 3;
        are2 = 0;
        are3 = 0;

        if (inarray(arg2, registers, registers_len))
          --l;
        else if (parse_symbol(arg1))
        {
          struct nlist *symb = lookup(arg1);
          if (symb == NULL)
          {
            error_clean(words, words_in_line, line_num, "Symbol isn't recognized", &rtn);
            continue;
          }

          int val;
          if (symb->has_type == TRUE && symb->type == EXTERN)
          {
            are2 = 1;
            val = 0;
            add_external(arg1, ic + 1);
          }
          else
          {
            are2 = 2;
            val = symb->value;
          }

          unsigned char lsb = (val << 3) | are2;
          unsigned char mb = (val >> 5);
          unsigned char msb = (val >> 13);
          change_word(find_word_at(ic + 1 - 100, 0), msb, mb, lsb, 0);
        }

        if (inarray(arg2, registers, registers_len))
          --l;
        else if (parse_symbol(arg2))
        {
          struct nlist *symb = lookup(arg2);
          if (symb == NULL)
          {
            error_clean(words, words_in_line, line_num, "Label isn't recognized", &rtn);
            continue;
          }

          int val;
          if (symb->has_type == TRUE && symb->type == EXTERN)
          {
            are3 = 1;
            val = 0;
            add_external(arg1, ic + l - 1);
          }
          else
          {
            are3 = 2;
            val = symb->value;
          }

          unsigned char lsb = (val << 3) | are3;
          unsigned char mb = (val >> 5);
          unsigned char msb = (val >> 13);
          change_word(find_word_at(ic + l - 101, 0), msb, mb, lsb, 0);
        }

        ic += l;
      }
      else if (inarray(words[symbol], one_oprand, one_oprand_len))
      {
        char arg[32];
        if (words_in_line == 2 + symbol)
          strcpy(arg, words[1 + symbol]);
        else
        {
          error_clean(words, words_in_line, line_num, "Oprand count not met", &rtn);
          continue;
        }

        l = 2;
        are2 = 0;

        if (inarray(arg, registers, registers_len))
          --l;
        else if (arg[0] == '&')
        {
          if (parse_symbol(arg + 1) == 0)
          {
            error_clean(words, words_in_line, line_num, "Illegal label", &rtn);
            continue;
          }
          struct nlist *p = lookup(arg + 1);
          if (p == NULL)
          {
            error_clean(words, words_in_line, line_num, "Label isn't recognized", &rtn);
            continue;
          }

          int val = p->value - ic;
          are2 = 4;
          unsigned char lsb = (val << 3) | are2;
          unsigned char mb = (val >> 5);
          unsigned char msb = (val >> 13);

          change_word(find_word_at(ic + 1 - 100, 0), msb, mb, lsb, 0);
        }
        else if (parse_symbol(arg))
        {
          struct nlist *symb = lookup(arg);
          if (symb == NULL)
          {
            error_clean(words, words_in_line, line_num, "Symbol isn't recognized", &rtn);
            continue;
          }

          int val;
          if (symb->has_type == TRUE && symb->type == EXTERN)
          {
            are2 = 1;
            val = 0;
            add_external(arg, ic + 1);
          }
          else
          {
            are2 = 2;
            val = symb->value;
          }

          unsigned char lsb = (val << 3) | are2;
          unsigned char mb = (val >> 5);
          unsigned char msb = (val >> 13);
          change_word(find_word_at(ic + 1 - 100, 0), msb, mb, lsb, 0);
        }

        ic += l;
      }
  }

  return rtn;
}
