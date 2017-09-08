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
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>


#define SHM_KEY 1000
 
void* Threadf(void* arg)
{
	int shmid;
	char* ch;
	
	//Encontra a memoria compartilhada
	if((shmid = shmget(SHM_KEY, 1024, IPC_CREAT | 0666)) < 0)
    {
       pthread_exit((void *) (intptr_t) errno);
    }
    //Atribui o endereco da memoria ao ponteiro
	ch = (char*)shmat(shmid, 0, 0);
	
	strcpy(ch, "123");
	
	//desconhecta a memoria compartilhada com o ponteiro
	shmdt(ch);
   
	pthread_exit((void *) 0);
}

int main(int argc, char *argv[])
{
	char* ch;
	int shmid, ret=0;
	pthread_t t;
	
	//Cria a memoria compartilhada
	if( (shmid = shmget(SHM_KEY, 1024, IPC_CREAT | 0666)) < 0)
	{
	   exit(EXIT_FAILURE);
	}
	
	//Atribui o endereco da memoria ao ponteiro
	ch = (char*)shmat(shmid, 0, 0);
	if((long)ch == -1)
	{
	   shmctl(shmid, IPC_RMID, NULL);
	   exit(EXIT_FAILURE);
	}

	strcpy(ch, "abc");

	pthread_create(&t,NULL, &Threadf, NULL);
	pthread_join(t, (void*)(intptr_t)ret);

	ch = (char*)shmat(shmid, 0, 0);
	printf("Valor da variavel ch: %s \n", ch);

	//desconhecta a memoria compartilhada com o ponteiro
	shmdt(ch);
	
	//Destroi a memoria compartilhada
	shmctl(shmid, IPC_RMID, NULL);

	exit(EXIT_SUCCESS);
}
