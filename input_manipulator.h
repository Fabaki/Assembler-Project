#ifndef INPUT_MANIPULATOR_H
#define INPUT_MANIPULATOR_H

/**
 * @param file variable the file will be inserted into
 * @param fname name of the file as given as an argument
 * @return the file var
 */
FILE *openfile(FILE *file, char *fname);

/**
 * reads the next line from the given file and puts it into line var
 * @param line char the next line should be put into
 * @param max maximum line length
 * @param file - file to be read
 * @return the length of the read line
 */
int get_line(char *line, int max, FILE *file);

/**
 * counts how many space separated words are in the line
 * @param line
 * @param line_limit - maximum line length
 * @return count of words
 */
int count_line_words(char *line, int line_limit);

/**
 * separate the a line into an array of strings separated from the original line by spaces
 * @param line original line
 * @param line_limit max line length
 * @param buffer array of strings
 * @return how many words
 */
int get_line_words(char *line, int line_limit, char *buffer[]);

#endif
