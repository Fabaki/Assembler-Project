#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"
#define LINE_LEN 82

int ic = 100, dc = 0;

void free_memory(char *pointers[], int len);

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
    {
      add_error(line_num, "Label already exists");
      free_memory(words, words_in_line);
    }

    if (strcmp(words[symbol], ".data") == 0)
    {
      int i, comma = FALSE; /* comma is to avoid double comma or no comma */
      for (i = 1 + symbol; i < words_in_line; i++)
      {
        if (strcmp(words[i], ",") == 0)
        {
          if (comma != FALSE)
          {
            add_error(line_num, "Too many commas");
            free_memory(words, words_in_line);
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
              add_error(line_num, "Not enough commas");
              free_memory(words, words_in_line);
              break;
            }
            *(words[i] + strlen(words[i]) - 1) = '\0';
            if (stoi(words[i]) != NULL)
              value = *(stoi(words[i]));
            else
            {
              add_error(line_num, "Non numeric character found");
              free_memory(words, words_in_line);
              break;
            }
            comma = TRUE;
          }
          else if (*(words[i]) == ',') /* is ',' the first char */
          {
            if (comma != FALSE)
            {
              add_error(line_num, "Too many commas");
              free_memory(words, words_in_line);
              break;
            }
            if (stoi(words[i] + 1) != NULL)
              value = *(stoi(words[i] + 1));
            else
            {
              add_error(line_num, "Non numeric character found");
              free_memory(words, words_in_line);
              break;
            }
            comma = FALSE;
          }
          else if ((*(words[i] + strlen(words[i] - 1)) == ',') && (*(words[i]) == ',')) /* for example, ".data 1 ,2, 3" */
          {
            if (comma != FALSE)
            {
              add_error(line_num, "Too many commas");
              free_memory(words, words_in_line);
              break;
            }

            *(words[i] + strlen(words[i]) - 1) = '\0';
            if (stoi(words[i] + 1) != NULL)
              value = *(stoi(words[i] + 1));
            else
            {
              add_error(line_num, "Non numeric character found");
              free_memory(words, words_in_line);
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
                  add_error(line_num, "Non numeric character found");
                  free_memory(words, words_in_line);
                  break;
                }
              }
            }
          }
        }
        else if (comma == FALSE)
        {
          add_error(line_num, "Not enough commas");
          free_memory(words, words_in_line);
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

      continue;
    }
    else if (strcmp(words[symbol], ".entry") == 0)
    {

      continue;
    }
    else if (strcmp(words[symbol], ".extern") == 0)
    {

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
          add_error(line_num, "Too many oprands");
          free_memory(words, words_in_line);
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
            add_error(line_num, "Oprand containing \",\"");
            free_memory(words, words_in_line);
            continue;
          }
        }
        else
        {
          add_error(line_num, "No \",\" between oprands");
          free_memory(words, words_in_line);
          continue;
        }
      }
      else
      {
        add_error(line_num, "Oprand count not met");
        free_memory(words, words_in_line);
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
        add_error(line_num, "Oprand count not met");
        free_memory(words, words_in_line);
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
        add_error(line_num, "Oprand count not met");
        free_memory(words, words_in_line);
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
      add_error(line_num, "Command isn't recognized");
      free_memory(words, words_in_line);
      continue;
    }
  }

  return rtn;
}

int parse_symbol(char *s);

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
