#ifndef INPUT_MANIPULATOR_H
#define INPUT_MANIPULATOR_H

FILE *openfile(FILE *file, char *fname);
int get_line(char *line, int max, FILE *file);
int count_line_words(char *line, int line_limit);
int get_line_words(char *line, int line_limit, char *buffer[]);

#endif
