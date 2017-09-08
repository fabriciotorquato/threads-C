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

int valor=0;
pthread_mutex_t mutex;

void* a (void* arg){	
	
	//Secao Critica protegida por mutex
	pthread_mutex_lock(&mutex);
		valor=5;
		printf("Valor = %d\n",valor);
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}
void* b (void* arg){	
	
	//Secao Critica protegida por mutex
	pthread_mutex_lock(&mutex);
		valor=2;
		printf("Valor = %d\n",valor);
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}
int main (int argc, char *argv[]) 
{ 
	pthread_t t[2];
	
	
	//Inizializa o mutex
	pthread_mutex_init(&mutex,NULL);
	
	if((pthread_create(&t[0],NULL,a,NULL))<0){
		exit(errno);
	}
	if((pthread_create(&t[1],NULL,b,NULL))<0){
		exit(errno);
	}
	
	pthread_join(t[0],NULL);
	pthread_join(t[1],NULL);
	
	//Destroi o mutex
	pthread_mutex_destroy(&mutex);
	
	exit(EXIT_SUCCESS); 
} 
