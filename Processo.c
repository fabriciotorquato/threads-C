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

int main (int argc, char *argv[]) 
{ 
	pid_t pid;
	int status;
	
	//Cria um novo processo
	if((pid = fork())<0){
		exit( errno );
	}
	
	//Processo Filho
	if(pid == 0){
		printf("processo filho\n");
		execl("Thread","Thread", NULL);
	}
	
	//Processo Pai
	else{
		printf("processo pai\n");	
	}
	
	//Aguardando fim dos processos filhos           
    while(wait(&status) != -1)
    {
         
    }   
	exit(EXIT_SUCCESS); 
} 
