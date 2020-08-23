#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

unsigned char *get_opcode_funct(char *cmd)
{
  unsigned char *opcode_func = (unsigned char *) calloc(2, sizeof(char));
  if (strcmp(cmd, "mov"))
  {
    *opcode_func = 0;
    *(opcode_func + 1) = 0;
  }
  else if (strcmp(cmd, "cmp"))
  {
    *opcode_func = 1;
    *(opcode_func + 1) = 0;
  }
  else if (strcmp(cmd, "add"))
  {
    *opcode_func = 2;
    *(opcode_func + 1) = 1;
  }
  else if (strcmp(cmd, "sub"))
  {
    *opcode_func = 2;
    *(opcode_func + 1) = 2;
  }
  else if (strcmp(cmd, "lea"))
  {
    *opcode_func = 4;
    *(opcode_func + 1) = 0;
  }
  else if (strcmp(cmd, "clr"))
  {
    *opcode_func = 5;
    *(opcode_func + 1) = 1;
  }
  else if (strcmp(cmd, "not"))
  {
    *opcode_func = 5;
    *(opcode_func + 1) = 2;
  }
  else if (strcmp(cmd, "inc"))
  {
    *opcode_func = 5;
    *(opcode_func + 1) = 3;
  }
  else if (strcmp(cmd, "dec"))
  {
    *opcode_func = 5;
    *(opcode_func + 1) = 4;
  }
  else if (strcmp(cmd, "jmp"))
  {
    *opcode_func = 9;
    *(opcode_func + 1) = 1;
  }
  else if (strcmp(cmd, "bne"))
  {
    *opcode_func = 9;
    *(opcode_func + 1) = 2;
  }
  else if (strcmp(cmd, "jsr"))
  {
    *opcode_func = 9;
    *(opcode_func + 1) = 3;
  }
  else if (strcmp(cmd, "red"))
  {
    *opcode_func = 12;
    *(opcode_func + 1) = 0;
  }
  else if (strcmp(cmd, "prn"))
  {
    *opcode_func = 13;
    *(opcode_func + 1) = 0;
  }
  else if (strcmp(cmd, "rts"))
  {
    *opcode_func = 14;
    *(opcode_func + 1) = 0;
  }
  else if (strcmp(cmd, "stop"))
  {
    *opcode_func = 15;
    *(opcode_func + 1) = 0;
  }

  return opcode_func;
}
