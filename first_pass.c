#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "passes.h"
#include "input_manipulator.h"
#include "string_manipulation.h"
#include "memory_structure.h"
#include "opcodes.h"
#include "symb_table.h"
#include "errors.h"

int ic = 100, dc = 0;
enum bool { FALSE, TRUE };

int first_pass(FILE *file)
{
  char line[LINE_LEN];
  int symbol = FALSE;
  int rtn = TRUE;
  int line_num = 0;
  int i;
  struct nlist *p;

  printf("Started first pass!\n");
  while (get_line(line, LINE_LEN, file) != EOF)
  {
    int words_in_line = count_line_words(line, LINE_LEN);
    char **words = (char **) calloc(words_in_line, sizeof(char *));
    char *label_name;
    int l, value1, value2, first_word_len;
    unsigned char are, funct, dest_reg, dest_type, src_reg, src_type, opcode, are2, are3;
    unsigned char msb, mb, lsb;

    ++line_num;

    if (words_in_line == 0)
      continue;

    /* symbol is used both as a way of knowing if the statement begins with a symbol, and as a way to increment to the
     * first argument in the words var */
    symbol = FALSE;
    get_line_words(line, LINE_LEN, words);

    first_word_len = strlen(*(words));
    if (parse_symbol(*(words)))
      symbol = TRUE;

    label_name = (char*) calloc(first_word_len, sizeof(char));
    strncpy(label_name, *(words), first_word_len - 1);

    if (symbol && lookup(label_name) != NULL)
      error_clean(words, words_in_line, line_num, "Label already exists", &rtn);

    if (strcmp(*(words + symbol), ".data") == 0)
    {
      int comma = TRUE; /* comma is to avoid double comma or no comma */
      int value;
      if (symbol)
        install(label_name, dc, DATA, FALSE, 0);

      for (i = 1 + symbol; i < words_in_line; i++)
      {
        if (strcmp(*(words + i), ",") == 0)
        {
          if (comma != FALSE)
          {
            error_clean(words, words_in_line, line_num, "Too many commans", &rtn);
            break;
          }
          continue;
        }

        if (instring(',', *(words + i), strlen(*(words + i))))
        {
          if (*(*(words + i) + strlen(*(words + i)) - 1) == ',') /* is the last char ',' */
          {
            if (comma == FALSE)
            {
              error_clean(words, words_in_line, line_num, "Not enough commas", &rtn);
              break;
            }
            *(*(words + i) + strlen(*(words + i)) - 1) = '\0';
            if (stoi(*(words + i)) != NULL)
              value = *(stoi(*(words + i)));
            else
            {
              error_clean(words, words_in_line, line_num, "Non numeric character found", &rtn);
              break;
            }
            comma = TRUE;
          }
          else if (*(*(words + i)) == ',') /* is ',' the first char */
          {
            if (comma != FALSE)
            {
              error_clean(words, words_in_line, line_num, "Too many commas", &rtn);
              break;
            }
            if (stoi(*(words + i) + 1) != NULL)
              value = *(stoi(*(words + i) + 1));
            else
            {
              error_clean(words, words_in_line, line_num, "Non numeric character found", &rtn);
              break;
            }
            comma = FALSE;
          }
          else if ((*(*(words + i) + strlen(*(words + i)) - 1) == ',') && (*(*(words + i)) == ',')) /* for example, ".data 1 ,2, 3" */
          {
            if (comma != FALSE)
            {
              error_clean(words, words_in_line, line_num, "Too many commas", &rtn);
              break;
            }

            *(*(words + i) + strlen(*(words + i)) - 1) = '\0';
            if (stoi(*(words + i) + 1) != NULL)
              value = *(stoi(*(words + i) + 1));
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
            for (dest_i = source_i = 0; dest_i < strlen(*(words + i)); dest_i++)
            {
              if (*(*(words + i) + dest_i) == ',')
              {
                *(*(words + i) + dest_i) = '\0';
                if (stoi(*(words + i) + source_i) != NULL)
                {
                  lsb = value = *(stoi(*(words + i) + source_i));
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
    else if (strcmp(*(words + symbol), ".string") == 0)
    {
      int k;

      if (symbol)
        install(label_name, dc, DATA, FALSE, 0);

      if (**(words + 1 + symbol) != '"')
      {
        error_clean(words, words_in_line, line_num, "String not starting with \"", &rtn);
        continue;
      }
      if (*(*(words + words_in_line - 1) + strlen(*(words + words_in_line - 1) - 1)) != '"')
      {
        error_clean(words, words_in_line, line_num, "String not ending with \"", &rtn);
        *(*(words + words_in_line - 1)) = '\0';
        continue;
      }

      for (k = 1; k < strlen(*(words + 1 + symbol)) && *(*(words + 1 + symbol) + k) != '"'; k++) /* first word start from index 1 */
      {
        add_word(0, 0, *(*(words + 1 + symbol) + k), 1);
        ++dc;
      }
      for (i = 2 + symbol; i < words_in_line; i++)
      {
        for (k = 0; k < strlen(*(words + i)) && *(*(words + i) + k) != '"'; k++)
        {
          add_word(0, 0, *(*(words + i) + k), 1);
          ++dc;
        }
      }
      add_word(0, 0, 0, 1); /* add \0 */
      ++dc;
      continue;
    }
    else if (strcmp(*(words + symbol), ".entry") == 0)
      continue;
    else if (strcmp(*(words + symbol), ".extern") == 0)
    {
      if (words_in_line != 2 + symbol)
      {
        error_clean(words, words_in_line, line_num, "Too many oprands", &rtn);
        continue;
      }

      install(*(words + symbol + 1), 0, CODE, TRUE, EXTERN); /* Was set to code so that it won't be incremented by ICF */
      continue;
    }

    if (symbol)
      install(label_name, ic, CODE, FALSE, 0);

    if (inarray(*(words + symbol), two_oprands, two_oprands_len))
    {
      char arg1[32];
      char arg2[32];
      unsigned char *opcode_funct;

      if (words_in_line == 4 + symbol)
      {
        /* The line is hopefully something like "LABEL: mov r1 , r2" */
        if (strcmp(*(words + 2 + symbol), ",") == 0)
        {
          strcpy(arg1, *(words + 1 + symbol));
          strcpy(arg2, *(words + 3 + symbol));
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
        if (instring(',', *(words + 1 + symbol), strlen(*(words + 1 + symbol))))
        {
          if (*(*(words + 1 + symbol) + strlen(*(words + 1 + symbol)) - 1) == ',') /* is the last char ',' */
          {
            strncpy(arg1, *(words + 1 + symbol), strlen(*(words + 1 + symbol)) - 1);
            strcpy(arg2, *(words + 2 + symbol));
          }
          else if (*(*(words + 2 + symbol)) == ',') /* is the first char of second arg ',' */
          {
            strcpy(arg1, *(words + 1 + symbol));
            strcpy(arg1, *(words + 2 + symbol) + 1);
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
        if (strcmp(*(words + symbol), "lea") == 0)
        {
          error_clean(words, words_in_line, line_num, "\"lea\" command's source oprand can only be using direct addressing", &rtn);
          continue;
        }
        src_reg = (unsigned char) (arg1[1] - '0'); /* if the arg1 is in the registers, its format is for sure rX */
        src_type = 3;
        --l;
      }
      else if (arg1[0] == '#')
      {
        if (strcmp(*(words + symbol), "lea") == 0)
        {
          error_clean(words, words_in_line, line_num, "\"lea\" command's source oprand can only be using direct addressing", &rtn);
          continue;
        }
        src_type = 0;
        value1 = atoi(&(arg1[1]));
        are2 = 4;
      }
      else if (arg1[0] == '&')
      {
        error_clean(words, words_in_line, line_num, "Can use \"&\" only on \"jmp\",\"bne\",\"jsr\"", &rtn); /* those commands aren't 2 oprands */
        continue;
      }
      else
      {
        src_type = 1;
        are2 = 0; /* we don't know if it is R or E */
      }

      if (inarray(arg2, registers, registers_len))
      {
        dest_reg = (unsigned char) (arg2[1] - '0');
        dest_type = 3;
        --l;
      }
      else if (arg2[0] == '#')
      {
        if (strcmp(*(words + symbol), "cmp") != 0)
        {
          error_clean(words, words_in_line, line_num, "Immediate addressing as destination oprand is legal only for \"cmp\",\"prn\"", &rtn);
          continue;
        }
        dest_type = 0;
        value2 = atoi(&(arg2[1]));
        are3 = 4;
      }
      else if (arg2[0] == '&')
      {
        error_clean(words, words_in_line, line_num, "Relative addressing is available only on \"jmp\",\"bne\",\"jsr\"", &rtn);
        continue;
      }
      else
      {
        dest_type = 1;
        are2 = 0;
      }

      opcode_funct = get_opcode_funct(*(words + symbol));
      opcode = *opcode_funct;
      funct = *(opcode_funct + 1);

      lsb = (funct << 3) | are;
      mb = (src_reg << 5) | (dest_type << 3) | (dest_reg);
      msb = (opcode << 2) | src_type;

      add_word(msb, mb, lsb, 0);
      if (src_type == 0)
      {
        lsb = (value1 << 3) | are2;
        mb = (value1 >> 5);
        msb = (value1 >> 13);
        add_word(msb, mb, lsb, 0);
      }
      else
      {
        lsb = 0 | are2; /* add a word with the correct are */
        add_word(0, 0, lsb, 0);
      }

      if (dest_type == 0)
      {
        lsb = (value2 << 3) | are3;
        mb = (value2 >> 5);
        msb = (value2 >> 13);
        add_word(msb, mb, lsb, 0);
      }
      else
      {
        lsb = 0 | are3; /* add a word with the correct are */
        add_word(0, 0, lsb, 0);
      }

      ic += l;
      printf("IC was %d and is now %d\n", ic - l, ic);
    }
    else if (inarray(*(words + symbol), one_oprand, one_oprand_len))
    {
      char arg[32];
      unsigned char *opcode_funct;

      if (words_in_line == 2 + symbol)
        strcpy(arg, *(words + 1 + symbol));
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
        if (strcmp(*(words + symbol), "jmp") == 0 || strcmp(*(words + symbol), "bne") == 0 || strcmp(*(words + symbol), "jsr") == 0)
        {
          error_clean(words, words_in_line, line_num, "Register addressing is not available on \"jmp\",\"bne\",\"jsr\"", &rtn);
          continue;
        }
        dest_reg = (unsigned char) (arg[1] - '0'); /* if the arg1 is in the registers, its format is for sure rX */
        dest_type = 3;
        --l;
      }
      else if (arg[0] == '#')
      {
        if (strcmp(*(words + symbol), "prn") != 0)
        {
          error_clean(words, words_in_line, line_num, "Immediate addressing as destination oprand is legal only for \"cmp\",\"prn\"", &rtn);
          continue;
        }
        dest_type = 0;
        value2 = atoi(&(arg[1]));
        are2 = 4;
      }
      else if (arg[0] == '&')
      {
        if (strcmp(*(words + symbol), "jmp") != 0 && strcmp(*(words + symbol), "bne") != 0 && strcmp(*(words + symbol), "jsr") != 0)
        {
          error_clean(words, words_in_line, line_num, "Relative addressing is available only on \"jmp\",\"bne\",\"jsr\"", &rtn);
          continue;
        }
        if (parse_symbol_noend(arg + 1) == 0)
        {
          error_clean(words, words_in_line, line_num, "Illegal label", &rtn);
          continue;
        }

        dest_type = 2;
        are2 = 4;
      }
      else
      {
        dest_type = 1;
        are2 = 1;
      }

      opcode_funct = get_opcode_funct(*(words + symbol));
      opcode = *opcode_funct;
      funct = *(opcode_funct + 1);

      lsb = (funct << 3) | are;
      mb = (src_reg << 5) | (dest_type << 3) | (dest_reg);
      msb = (opcode << 2) | src_type;

      add_word(msb, mb, lsb, 0);
      if (dest_type == 0)
      {
        lsb = (value1 << 3) | are2;
        mb = (value1 >> 5);
        msb = (value1 >> 13);
        add_word(msb, mb, lsb, 0);
      }
      else
      {
        lsb = 0 | are2;
        add_word(0, 0, lsb, 0);
      }

      ic += l;
      printf("IC was %d and is now %d\n", ic - l, ic);
    }
    else if (inarray(*(words + symbol), no_oprand, no_oprand_len))
    {
      unsigned char *opcode_funct;

      if (words_in_line != 1 + symbol)
      {
        error_clean(words, words_in_line, line_num, "Oprand count not met", &rtn);
        continue;
      }

      l = 1;
      are = 4;
      dest_reg = 0;
      dest_type = 0;
      src_reg = 0;
      src_type = 0;

      opcode_funct = get_opcode_funct(*(words + symbol));
      opcode = *opcode_funct;
      funct = *(opcode_funct + 1);

      lsb = (funct << 3) | are;
      mb = (src_reg << 5) | (dest_type << 3) | (dest_reg);
      msb = (opcode << 2) | src_type;

      add_word(msb, mb, lsb, 0);

      ic += l;
      printf("IC was %d and is now %d\n", ic - l, ic);
    }
    else
    {
      error_clean(words, words_in_line, line_num, "Command isn't recognized", &rtn);
      continue;
    }
  }


  icf = ic;
  idf = dc;

  struct nlist **table = get_symbol_table();
  for (i = 0; i < HASHSIZE; i++)
  {
      struct nlist *np = *(table + i);
    for (; np != NULL; np = np->next)
    {
      if (np->loc == DATA)
        np->value += icf;
    }
  }

  printf("Got ICF: %d, IDF: %d\n", icf, idf);
  printf("Returning from first pass\n");
  return rtn;
}

int parse_symbol(char *s)
{
  int i;

  if (!isalpha(s[0]))
    return 0;
  for (i = 1; isalnum(s[i]); i++)
    if (i > 31)
      return 0;
  if (s[i] != ':') /* checking if all label chars are alphanumeric */
    return 0;
  return 1;
}

int parse_symbol_noend(char *s)
{
  int i;

  if (!isalpha(s[0]))
    return 0;
  for (i = 1; isalnum(s[i]); i++)
    if (i > 31)
      return 0;
  return 1;
}

void free_memory(char **pointers, int len)
{
  int i;
  for (i = 0; i < len; i++)
    free(*(pointers + i));
}

void error_clean(char **words, int len, int line, char *error, int *rtn)
{
  add_error(error, line);
  free_memory(words, len);
  *rtn = FALSE;
}
