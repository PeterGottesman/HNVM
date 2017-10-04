#ifndef __VM_INSTR_H
#define __VM_INSTR_H

typedef enum
{
    NOP = 0x00, // NOP
    ADD = 0x01, // Add 
    SUB = 0x02, // Subtract
    JEZ = 0x03, // Jump if zero
    JNZ = 0x04, // jump if not zero
    LDA = 0x05, // load A
    LDB = 0x06, // load B
    LDC = 0x07, // load C
    LDM = 0x08, // load into memory a value
    HCF = 0xFF, // exit
} VM_Instruction;

#endif
