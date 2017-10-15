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
    destroy_vm(vm);
    return 0;
}

int allocate_memory(vm_type *vm)
{
    vm->memory = calloc(sizeof(uint8_t), conf.memory);
    if (vm->memory == NULL) return 1;
    return 0;
}

int loop(vm_type *vm)
{
    uint8_t prog[] = {LDM, 12, 100, LDM, 13, 34, ADD, 12, SUB, 13, HCF};
    for(int i = 0; i < 11; i++)
    {
	vm->memory[i] = prog[i];
    }
    vm->running=1;
    while(vm->running)
    {
	/*
        for (int i = 0; i < conf.memory; i++)
        {
	    printf("%d: %d\n", i, vm->memory[i]);
        }
	printf("PC: %d, %d\n", vm->PC, vm->memory[vm->PC]);
	printf("regA: %d\n", vm->registers.regA);
	*/
	eval_command(vm, vm->memory[vm->PC++%conf.memory]);
    }
    return 0;
}

int eval_command(vm_type *vm, VM_Instruction instr)
{
    switch(instr)
    {
        case NOP:
	    printf("nop\n");
	    break;
	case ADD:
	    printf("add\n");
	    vm_add(vm, vm->memory[vm->PC++]);
	    break;
	case SUB:
	    printf("sub\n");
	    vm_sub(vm, vm->memory[vm->PC++]);
	    break;
	case JEZ:
	    printf("jez\n");
	    vm_jez(vm, vm->memory[vm->PC++], vm->PC++);
	    break;
	case JNZ:
	    printf("jnz\n");
	    vm_jnz(vm, vm->memory[vm->PC++], vm->PC++);
	    break;
        case LDA:
	    printf("lda\n");
	    vm_lda(vm, vm->memory[vm->PC++]);
	    break;
        case LDB:
	    printf("ldb\n");
	    vm_lda(vm, vm->memory[vm->PC++]);
	    break;
        case LDC:
	    printf("ldc\n");
	    vm_lda(vm, vm->memory[vm->PC++]);
	    break;
        case LDM:
	    printf("ldm\n");
            vm_ldm(vm, vm->memory[vm->PC++], vm->memory[vm->PC++]);
	    break;
	case HCF:
	    printf("hcf\n");
	    vm->running = 0;
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
    printf("dest: %d, val: %d\n", dest, val);
    vm->memory[dest] = val;
    return 0;
}

int destroy_vm(vm_type *vm)
{
    free_memory(vm);
    exit(0);
    return 0;
}

int free_memory(vm_type *vm)
{
    free(vm->memory);
    printf("freed memory\n");
    return 0;
}
