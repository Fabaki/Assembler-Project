#ifndef OUTPUT_H
#define OUTPUT_H

int add_error(int line, char *e);
void create_output(char fname[], int anyEntries, int anyExterns);
void create_ent(char fname[], int len);
void create_ext(char fname[], int len);
void create_ob(char fname[], int len);

#endif
