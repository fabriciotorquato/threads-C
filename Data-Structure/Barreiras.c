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
pthread_barrier_t barrier; 

void* a (void* arg){
	
	v1=2;
	
	//Barreira de sincronização
    pthread_barrier_wait(&barrier);
	pthread_exit(NULL);
}
void* b (void* arg){
	
	v2=3;
	
	//Barreira de sincronização
    pthread_barrier_wait(&barrier);
    
	pthread_exit(NULL);
}
void* c (void* arg){
	
	//Barreira de sincronização
    pthread_barrier_wait(&barrier);
	printf("Valor = %d\n",v1+v2);
	
	pthread_exit(NULL);
}
int main (int argc, char *argv[]) 
{ 
	pthread_t t[3];
	
	//Inicializa a barreira
	pthread_barrier_init(&barrier, NULL, 3);
	
	if((pthread_create(&t[0],NULL,a,NULL))<0){
		exit(errno);
	}
	if((pthread_create(&t[1],NULL,b,NULL))<0){
		exit(errno);
	}
	if((pthread_create(&t[2],NULL,c,NULL))<0){
		exit(errno);
	}
	
	for(int i=0;i<3;i++)
		pthread_join(t[i],NULL);
	
	exit(EXIT_SUCCESS); 
} 
