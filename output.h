#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * call all functions that are responsible for the output files, namely .ob .ent and .ext
 * @param fname the name of the input file as received, used to name the output files
 */
void create_output(char *fname);
/**
 * loops through the symbol table and finds all "entry flagged" values, write them all to ent file
 * @param fname name of original input file
 */
void create_ent(char *fname);

/**
 * loops through the extern symbol linked list and write to the .ext file every extern symbol value
 * @param fname name of original input file
 */
void create_ext(char *fname);

/**
 * @param fname name of original input file
 */
void create_ob(char *fname);

#endif
