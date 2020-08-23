#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

/**
 * checks if a string is in a given array and returns a boolean answer
 * @param word the string to be checked
 * @param array the array of string
 * @param array_length
 * @return
 */
int inarray(char *word, char *array[], int array_length);

/**
 * checks if a given char is in a string, and returns a boolean answer
 * @param c the character
 * @param word the string
 * @param word_length
 * @return
 */
int instring(char c, char *word, int word_length);

/**
 * converts a given string to an int and returns the int
 * @param s the string
 * @return its corresponding int value
 */
int *stoi(char s[]);

#endif
