#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

#define BYTE 1024

int main (void)
{
	void *bloco = NULL;
	
	while(1)
	{
		//ALOCA memoria virtual
		bloco = (void *) malloc(BYTE);
		if(!bloco)
		{
			break;
		}
		printf("Alocado memoria\n");
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
