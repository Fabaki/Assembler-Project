#ifndef ERRORS_H
#define ERRORS_H

static int error_count = 0;

/* struct representing an error string as a part of a node making a linked list */
struct error
{
  struct error *next;
  char *error;
  int line;
};

struct error *error_list;

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
