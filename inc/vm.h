#ifndef __VM_H
#define __VM_H

#include <stdint.h>
#include "vm_conf.h"
#include "vm_instructions.h"

struct registers_struct
{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;    
};

struct vm_struct
{
    uint8_t *memory;
    uint8_t PC;
    uint8_t running;
    struct registers_struct registers;
};

// Declarations
int initialize_vm(void);
int allocate_memory(void);
int loop(void);
int eval_command(VM_Instruction instr);
int vm_add(uint8_t ref);
int vm_sub(uint8_t ref);
int vm_jez(uint8_t ref, uint8_t dest);
int vm_jnz(uint8_t ref, uint8_t dest);
int vm_lda(uint8_t val);
int vm_ldb(uint8_t val);
int vm_ldc(uint8_t val);
int vm_ldm(uint8_t dest, uint8_t val);
int free_memory(void);
int destroy_vm(void);
#endif
