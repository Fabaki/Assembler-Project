#ifndef ERRORS_H
#define ERRORS_H

/**
 * add an error to the list of existing errors
 * @param error the error as a string
 * @param line in what line the error occurred
 * @return
 */
struct error *add_error(char *error, int line);

/**
 * loop through the list error and print each one individually
 */
void print_errors();
int get_error_count();

#endif
