#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

int inarray(char *word, char *array[], int array_length)
{
  int i;
  for (i = 0; i < array_length; i++)
  {
    if (strcmp(word, array[i]) == 0)
      return TRUE;
  }

  return FALSE;
}

int instring(char c, char *word, int word_length)
{
  while (*word != '\0' && word_length--)
  {
    if (c == *word++)
      return TRUE;
  }

  return FALSE;
}

int strsplit(char word[], int len, char splitter, char word1[], char word2[])
{
  int i;
  for (i = 0; i < len; i++)
  {
    if (word[i] == splitter)
    {
      strncpy(word1, word, i);
      word1[i] = '\0';
      while (isspace(word[i+1]))
        ++i;
      strcpy(word2, &word[i+1]);
      return 1;
    }
  }

  return 0;
}
