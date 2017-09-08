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

#define MAX 500

int main (int argc, char *argv[]) 
{ 
	int fd;
	int status;
	pid_t pid;
	
	char buff[MAX] ="Oi Sou Ze";
	
	//Cria o PIPE
	mknod("com", S_IFIFO|0666, 0);
	
	if((pid=fork())<0){
		exit(errno);
	}
	if(pid==0){
		
		//Abre o PIPE para escrita e leitura
		if((fd = open("com", O_WRONLY | O_NDELAY))<0){
			exit (EXIT_FAILURE);
		}
		
		//Escreve no PIPE
		write(fd,buff,sizeof(buff));
		printf("Escrevendo no PIPE...\n");
		
		//Fecha o PIPE
		close(fd);
	}
	else{		
		//Abre o PIPE para leitura
		if((fd = open("com", O_RDONLY))<0){
			exit (EXIT_FAILURE);
		}
		
		//Aguardando fim dos processos filhos           
		while(wait(&status) != -1)
		{	 
		}  
		
		//Ler o PIPE
		memset(buff,'\0',sizeof(buff));
		read(fd,buff,MAX);
		printf("Lendo o PIPE: %s\n",buff);		
		
		//Fecha o PIPE
		close(fd);
	}
	
	//Destruindo PIPE
	unlink("com");
	
	exit(EXIT_SUCCESS); 
} 
