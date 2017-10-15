#ifndef __VM_H
#define __VM_H

#include <stdint.h>
#include "vm_conf.h"
#include "vm_instructions.h"

typedef struct
{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;    
} registers_type;

typedef struct
{
    uint8_t *memory;
    uint8_t PC;
    uint8_t running;
    registers_type registers;
} vm_type;

// Declarations
int initialize_vm(vm_type *vm);
int allocate_memory(vm_type *vm);
int loop(vm_type *vm);
int eval_command(vm_type *vm, VM_Instruction instr);
int vm_add(vm_type *vm, uint8_t ref);
int vm_sub(vm_type *vm, uint8_t ref);
int vm_jez(vm_type *vm, uint8_t ref, uint8_t dest);
int vm_jnz(vm_type *vm, uint8_t ref, uint8_t dest);
int vm_lda(vm_type *vm, uint8_t val);
int vm_ldb(vm_type *vm, uint8_t val);
int vm_ldc(vm_type *vm, uint8_t val);
int vm_ldm(vm_type *vm, uint8_t dest, uint8_t val);
int free_memory(vm_type *vm);
int destroy_vm(vm_type *vm);
#endif
