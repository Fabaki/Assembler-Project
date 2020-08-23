#ifndef OPCODES_H
#define OPCODES_H

/**
 * receives a string representing an assembly command and returns its its opcode value
 * @param cmd that it opcode should be found
 * @return opcode value
 */
unsigned char *get_opcode_funct(char *cmd);

#endif
