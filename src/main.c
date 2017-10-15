#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"
#include "vm_conf.h"

int main(int argc, char *argv[])
{
    while(*argv)
    {
	if (!strcmp(*argv, "-m") || !strcmp(*argv, "--memory"))
	{
	    **argv++;
	    conf.memory = atoi(*argv);
	}
	**argv++;
    }

    if (conf.memory == 0)
    {
	conf.memory = 255;
    }

    vm_type *vm = malloc(sizeof(vm_type) + conf.memory);
    initialize_vm(vm);
}
