#include "assembler.h"

unsigned char *get_opcode_funct(char *cmd)
{
  unsigned char opcode_func[2];
  if (strcmp(cmd, "mov"))
  {
    opcode_func[0] = 0;
    opcode_func[1] = 0;
  }
  else if (strcmp(cmd, "cmp"))
  {
    opcode_func[0] = 1;
    opcode_func[1] = 0;
  }
  else if (strcmp(cmd, "add"))
  {
    opcode_func[0] = 2;
    opcode_func[1] = 1;
  }
  else if (strcmp(cmd, "sub"))
  {
    opcode_func[0] = 2;
    opcode_func[1] = 2;
  }
  else if (strcmp(cmd, "lea"))
  {
    opcode_func[0] = 4;
    opcode_func[1] = 0;
  }
  else if (strcmp(cmd, "clr"))
  {
    opcode_func[0] = 5;
    opcode_func[1] = 1;
  }
  else if (strcmp(cmd, "not"))
  {
    opcode_func[0] = 5;
    opcode_func[1] = 2;
  }
  else if (strcmp(cmd, "inc"))
  {
    opcode_func[0] = 5;
    opcode_func[1] = 3;
  }
  else if (strcmp(cmd, "dec"))
  {
    opcode_func[0] = 5;
    opcode_func[1] = 4;
  }
  else if (strcmp(cmd, "jmp"))
  {
    opcode_func[0] = 9;
    opcode_func[1] = 1;
  }
  else if (strcmp(cmd, "bne"))
  {
    opcode_func[0] = 9;
    opcode_func[1] = 2;
  }
  else if (strcmp(cmd, "jsr"))
  {
    opcode_func[0] = 9;
    opcode_func[1] = 3;
  }
  else if (strcmp(cmd, "red"))
  {
    opcode_func[0] = 12;
    opcode_func[1] = 0;
  }
  else if (strcmp(cmd, "prn"))
  {
    opcode_func[0] = 13;
    opcode_func[1] = 0;
  }
  else if (strcmp(cmd, "rts"))
  {
    opcode_func[0] = 14;
    opcode_func[1] = 0;
  }
  else if (strcmp(cmd, "stop"))
  {
    opcode_func[0] = 15;
    opcode_func[1] = 0;
  }

  return opcode_func;
}

long long decimal_to_binary(int n)
{
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        ++step;
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}
