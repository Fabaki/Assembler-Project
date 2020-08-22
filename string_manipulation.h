#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

int inarray(char *word, char *array[], int array_length);
int instring(char c, char *word, int word_length);
int strsplit(char word[], int len, char splitter, char word1[], char word2[]);
int *stoi(char s[]);

#endif
