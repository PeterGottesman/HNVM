#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

int initialize_vm(vm_type *vm)
{
    if (allocate_memory(vm))
    {
	printf("Error allocating memory\n");
	exit(1);
    }
    loop(vm);
    free_vm(vm);
    return 0;
}

int allocate_memory(vm_type *vm)
{
    vm->memory = &vm->registers + sizeof(vm->registers);
    if (vm->memory == NULL) return 1;
    return 0;
}

int loop(vm_type *vm)
{
    uint8_t prog[] = {LDM, 32, 100, LDM, 13, 34, ADD, 12, SUB, 13, HCF};
    for(int i = 0; i < sizeof(prog); i++)
    {
	vm->memory[i] = prog[i];
	printf("%#04x ", vm->memory[i]);
    }
    printf("\n");
    vm->running=1;
    while(vm->running)
    {
	eval_command(vm, vm->memory[vm->PC++%conf.memory]);
    }
    return 0;
}

int eval_command(vm_type *vm, VM_Instruction instr)
{
    switch(instr)
    {
        case NOP:
	    #ifdef DEBUG
	    printf("nop\n");
	    #endif
	    break;
	case ADD:
	    #ifdef DEBUG
	    printf("add\n");
	    #endif
	    vm_add(vm, vm->memory[vm->PC++]);
	    break;
	case SUB:
	    #ifdef DEBUG
	    printf("sub\n");
	    #endif
	    vm_sub(vm, vm->memory[vm->PC++]);
	    break;
	case JEZ:
	    #ifdef DEBUG
	    printf("jez\n");
	    #endif
	    vm_jez(vm, vm->memory[vm->PC++], vm->PC++);
	    break;
	case JNZ:
	    #ifdef DEBUG
	    printf("jnz\n");
	    #endif
	    vm_jnz(vm, vm->memory[vm->PC++], vm->PC++);
	    break;
        case LDA:
	    #ifdef DEBUG
	    printf("lda\n");
	    #endif
	    vm_lda(vm, vm->memory[vm->PC++]);
	    break;
        case LDB:
	    #ifdef DEBUG
	    printf("ldb\n");
	    #endif
	    vm_lda(vm, vm->memory[vm->PC++]);
	    break;
        case LDC:
	    #ifdef DEBUG
	    printf("ldc\n");
	    #endif
	    vm_lda(vm, vm->memory[vm->PC++]);
	    break;
        case LDM:
	    #ifdef DEBUG
	    printf("ldm\n");
	    #endif
            vm_ldm(vm, vm->memory[vm->PC++], vm->memory[vm->PC++]);
	    break;
	case HCF:
	    #ifdef DEBUG
	    printf("hcf\n");
	    #endif
	    vm->running = 0;
	    break;
        default:
	    printf("unknown instruction %#04x at PC: %d\n", instr, vm->PC);
	    break;
    }
    return 0;
}

int vm_add(vm_type *vm, uint8_t ref)
{
    vm->registers.regA += vm->memory[ref];
    return 0;
}

int vm_sub(vm_type *vm, uint8_t ref)
{
    vm->registers.regA -= vm->memory[ref];
    return 0;
}

int vm_jez(vm_type *vm, uint8_t ref, uint8_t dest)
{
    if (vm->memory[ref] == 0)
    {
	vm->PC = dest;
    }
    return 0;
}

int vm_jnz(vm_type *vm, uint8_t ref, uint8_t dest)
{
    if (vm->memory[ref] != 0)
    {
	vm->PC = dest;
    }
    return 0;
}

int vm_lda(vm_type *vm, uint8_t val)
{
    vm->registers.regA = val;
    return 0;
}

int vm_ldb(vm_type *vm, uint8_t val)
{
    vm->registers.regB = val;
    return 0;
}

int vm_ldc(vm_type *vm, uint8_t val)
{
    vm->registers.regC = val;
    return 0;
}

int vm_ldm(vm_type *vm, uint8_t dest, uint8_t val)
{
    vm->memory[dest] = val;
    return 0;
}

int free_vm(vm_type *vm)
{
    free(vm);
    return 0;
}
