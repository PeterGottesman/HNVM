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
    printf("Memory allocated: %d\n", conf.memory);

    initialize_vm();
}
