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

int v1,v2;
sem_t semafaro; 

void* a (void* arg){
	
	v1=2;
	v2=3;
	
	//Sinal verde
    sem_post(&semafaro);
    
	pthread_exit(NULL);
}

void* b (void* arg){
	
	//Sinal vermelho
    sem_wait(&semafaro);
	printf("Valor = %d\n",v1+v2);
	
	pthread_exit(NULL);
}
int main (int argc, char *argv[]) 
{ 
	pthread_t t[2];
	
	//Inicializa o semafaro
	sem_init(&semafaro,0,0);
	
	if((pthread_create(&t[0],NULL,a,NULL))<0){
		exit(errno);
	}
	if((pthread_create(&t[1],NULL,b,NULL))<0){
		exit(errno);
	}
	
	for(int i=0;i<2;i++)
		pthread_join(t[i],NULL);
		
	sem_destroy(&semaforo);
	exit(EXIT_SUCCESS); 
} 
