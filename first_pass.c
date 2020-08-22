#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"
#define LINE_LEN 82

int ic = 100, dc = 0;

void free_memory(char *pointers[], int len);
int parse_symbol(char *s);
void error_clean(char *words[], int len, int line, char *error, int *rtn);

int first_pass(FILE *file)
{
  char line[LINE_LEN];
  int symbol = FALSE;
  int rtn = TRUE;
  int line_num = 0;

  while ((line = get_line(line, LINE_LEN, file)) != EOF)
  {
    int words_in_line = count_line_words(line, LINE_LEN);
    char *words[];
    int l, value1, value2;
    unsigned char are, funct, dest_reg, dest_type, src_reg, src_type, opcode, are2, are3;
    unsigned char msb, mb, lsb;

    ++line_num;
    get_line_words(line, LINE_LEN, words);

    int first_word_len = strlen(words[0]);
    if (parse_symbol(words[0]))
      symbol = TRUE;
    if (symbol && lookup(label_name) != NULL)
      error_clean(words, words_in_line, line_num, "Label already exists", &rtn);

    if (strcmp(words[symbol], ".data") == 0)
    {
      int i, comma = FALSE; /* comma is to avoid double comma or no comma */

      if (symbol)
      {
        char label_name[first_word_len];
        strncpy(label_name, words[0], first_word_len - 1);
        install(label_name, dc, DATA, FALSE, 0);
      }

      for (i = 1 + symbol; i < words_in_line; i++)
      {
        if (strcmp(words[i], ",") == 0)
        {
          if (comma != FALSE)
          {
            error_clean(words, words_in_line, line_num, "Too many commans", &rtn);
            break;
          }
          continue;
        }

        int value;
        if (instring(',', words[i], strlen(words[i])))
        {
          if (*(words[i] + strlen(words[i] - 1)) == ',') /* is the last char ',' */
          {
            if (comma == FALSE)
            {
              error_clean(words, words_in_line, line_num, "Not enough commas", &rtn);
              break;
            }
            *(words[i] + strlen(words[i]) - 1) = '\0';
            if (stoi(words[i]) != NULL)
              value = *(stoi(words[i]));
            else
            {
              error_clean(words, words_in_line, line_num, "Non numeric character found", &rtn);
              break;
            }
            comma = TRUE;
          }
          else if (*(words[i]) == ',') /* is ',' the first char */
          {
            if (comma != FALSE)
            {
              error_clean(words, words_in_line, line_num, "Too many commas", &rtn);
              break;
            }
            if (stoi(words[i] + 1) != NULL)
              value = *(stoi(words[i] + 1));
            else
            {
              error_clean(words, words_in_line, line_num, "Non numeric character found", &rtn);
              break;
            }
            comma = FALSE;
          }
          else if ((*(words[i] + strlen(words[i] - 1)) == ',') && (*(words[i]) == ',')) /* for example, ".data 1 ,2, 3" */
          {
            if (comma != FALSE)
            {
              error_clean(words, words_in_line, line_num, "Too many commas", &rtn);
              break;
            }

            *(words[i] + strlen(words[i]) - 1) = '\0';
            if (stoi(words[i] + 1) != NULL)
              value = *(stoi(words[i] + 1));
            else
            {
              error_clean(words, words_in_line, line_num, "Non numeric character found", &rtn);
              break;
            }
            comma = TRUE;
          }
          else /* in the case of ".data 1,2,3" */
          {
            int source_i, dest_i; /* k is the starting index, j is the finishing */
            for (dest_i = source_i = 0; dest_i < strlen(words[i]); dest_i++)
            {
              if (*(words[i] + dest_i) == ',')
              {
                *(words[i] + dest_i) = '\0';
                if (stoi(words[i] + source_i) != NULL)
                {
                  lsb = value = *(stoi(words[i] + source_i));
                  mb = value >> 8;
                  msb = value >> 16;
                  add_word(msb, mb, lsb, 1);
                  dc++;

                  source_i = dest_i;
                }
                else
                {
                  error_clean(words, words_in_line, line_num, "Non numeric character found", &rtn);
                  break;
                }
              }
            }
          }
        }
        else if (comma == FALSE)
        {
          error_clean(words, words_in_line, line_num, "Not enough commas", &rtn);
          break;
        }

        lsb = value;
        mb = value >> 8;
        msb = value >> 16;
        add_word(msb, mb, lsb, 1);
        dc++;
      }
      continue;
    }
    else if (strcmp(words[symbol], ".string") == 0)
    {
      int i, k;

      if (symbol)
      {
        char label_name[first_word_len];
        strncpy(label_name, words[0], first_word_len - 1);
        install(label_name, dc, DATA, FALSE, 0);
      }

      if (*words[1 + symbol] != '"')
      {
        error_clean(words, words_in_line, line_num, "String not starting with \"", &rtn);
        continue;
      }
      if (*(words[words_in_line - 1] + strlen(words[words_in_line - 1] - 1)) != '"')
      {
        error_clean(words, words_in_line, line_num, "String not ending with \"", &rtn);
        *(words[words_in_line - 1]) = '\0';
        continue;
      }

      for (k = 1; k < strlen(words[1 + symbol]); k++)
      {
        add_word(0, 0, *(words[1 + symbol] + k), 1);
        ++dc;
      }
      for (i = 2 + symbol; i < words_in_line; i++)
      {
        for (k = 0; k < strlen(words[i]); k++)
        {
          add_word(0, 0, *(words[i] + k), 1);
          ++dc;
        }
      }
      add_word(0, 0, 0, 1); /* add \0 */
      ++dc;
      continue;
    }
    else if (strcmp(words[symbol], ".entry") == 0)
      continue;
    else if (strcmp(words[symbol], ".extern") == 0)
    {
      if (words_in_line != 2 + symbol)
      {
        error_clean(words, words_in_line, line_num, "Too many oprands", &rtn);
        continue;
      }

      install(words[symbol + 1], 0, CODE, TRUE, EXTERN); /* Was set to code so that it won't be incremented by ICF */
      continue;
    }

    if (symbol)
    {
      char label_name[first_word_len];
      strncpy(label_name, words[0], first_word_len - 1);
      install(label_name, ic, CODE, FALSE, 0);
    }

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
          else if (*(words[2 + symbol]) == ',')
          {
            strcpy(arg1, words[1 + symbol]);
            strcpy(arg1, words[2 + symbol] + 1);
          }
          else
          {
            error_clean(words, words_in_line, line_num, "Oprand containing \",\"", &rtn);
            continue;
          }
        }
        else
        {
          error_clean(words, words_in_line, line_num, "No \",\" between oprands", &rtn);
          continue;
        }
      }
      else
      {
        error_clean(words, words_in_line, line_num, "Oprand count not met", &rtn);
        continue;
      }

      l = 3;
      are = 4;
      are2 = 0;
      are3 = 0;

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

      if (inarray(arg2, registers, registers_len))
      {
        dest_reg = (unsigned char) (arg2[1] - '0'); /* if the arg1 is in the registers, its format is for sure rX */
        dest_type = 3;
        --l;
      }
      else if (arg2[0] == '#')
      {
        src_type = 0;
        value2 = atoi(&(arg2[1]));
        are3 = 4;
      }

      unsigned char *opcode_funct = get_opcode_funct(words[symbol]);
      opcode = *opcode_funct;
      funct = *(opcode_funct + 1);

      lsb = (funct << 3) | are;
      mb = (src_reg << 5) | (dest_type << 3) | (dest_reg);
      msb = (opcode << 2) | src_type;

      add_word(msb, mb, lsb, 0);
      if (are2)
      {
        lsb = (value1 << 2) | are2;
        mb = (value1 >> 8);
        msb = (value1 >> 16);
        add_word(msb, mb, lsb, 0);
      }
      else /* Add an empty word (which can't exist in the code part since one of ARE is always on) for second pass */
        add_word(0, 0, 0, 0);

      if (are3)
      {
        lsb = (value2 << 2) | are3;
        mb = (value2 >> 8);
        msb = (value2 >> 16);
        add_word(msb, mb, lsb, 0);
      }
      else
        add_word(0, 0, 0, 0);

      ic += l;
    }
    else if (inarray(words[symbol], one_oprand, one_oprand_len))
    {
      char arg[32];
      if (words_in_line == 2 + symbol)
        strcpy(arg1, words[1 + symbol]);
      else
      {
        error_clean(words, words_in_line, line_num, "Oprand count not met", &rtn);
        continue;
      }

      l = 2;
      are = 4;
      src_reg = 0;
      src_type = 0;
      are2 = 0;

      if (inarray(arg, registers, registers_len))
      {
        dest_reg = (unsigned char) (arg[1] - '0'); /* if the arg1 is in the registers, its format is for sure rX */
        dest_type = 3;
        --l;
      }
      else if (arg[0] == '#')
      {
        src_type = 0;
        value2 = atoi(&(arg[1]));
        are2 = 4;
      }

      unsigned char *opcode_funct = get_opcode_funct(words[symbol]);
      opcode = *opcode_funct;
      funct = *(opcode_funct + 1);

      lsb = (funct << 3) | are;
      mb = (src_reg << 5) | (dest_type << 3) | (dest_reg);
      msb = (opcode << 2) | src_type;

      add_word(msb, mb, lsb, 0);
      if (are2)
      {
        lsb = (value1 << 2) | are2;
        mb = (value1 >> 8);
        msb = (value1 >> 16);
        add_word(msb, mb, lsb, 0);
      }
      else
        add_word(0, 0, 0, 0);

      ic += l;
    }
    else if (inarray(words[symbol], no_oprand, no_oprand_len))
    {
      if (words_in_line != 1 + symbol)
      {
        error_clean(words, words_in_line, line_num, "Oprand count not met", &rtn);
        continue;
      }

      l = 1;
      are = 4;
      est_reg = 0;
      dest_type = 0;
      src_reg = 0;
      src_type = 0;

      unsigned char *opcode_funct = get_opcode_funct(words[symbol]);
      opcode = *opcode_funct;
      funct = *(opcode_funct + 1);

      lsb = (funct << 3) | are;
      mb = (src_reg << 5) | (dest_type << 3) | (dest_reg);
      msb = (opcode << 2) | src_type;

      add_word(msb, mb, lsb, 0);

      ic += l;
    }
    else
    {
      error_clean(words, words_in_line, line_num, "Command isn't recognized", &rtn);
      continue;
    }
  }

  icf = ic;
  dcf = dc;

  int i;
  for (i = 0; i < HASHSIZE; i++)
  {
    struct nlist *p = symbol_table[i];
    while (p->next != NULL)
    {
      if (p->loc == DATA)
        p->value += icf;
      p = p->next;
    }
  }

  return rtn;
}

int parse_symbol(char *s)
{
  int i;

  if (!isalpha(s[0]))
    return 0;
  for (i = 1; isalnum(s[i]); i++)
    ;
  if (s[i] != ':') /* checking if all label chars are alphanumeric */
    return 0;
  return 1;
}

void free_memory(char *pointers[], int len)
{
  int i;
  for (i = 0; i < len; i++)
    free(pointers[i]);
}

void error_clean(char *words[], int len, int line, char *error, int *rtn)
{
  add_error(line, error);
  free_memory(words, len);
  *rtn = FALSE;
}
