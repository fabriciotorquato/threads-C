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
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

void* a (void* arg){
	
	//Executa a Thread
	printf("Inicio a thread");
	
	pthread_exit(NULL);
}

int main (int argc, char *argv[]) 
{ 
	pthread_t t;
	
	//Cria uma nova Thread
	if((pthread_create(&t,NULL,a,NULL))<0){
		exit(errno);
	}
	
	//Inicia a nova Thread
	pthread_join(t,NULL);
	
	exit(EXIT_SUCCESS); 
} 
