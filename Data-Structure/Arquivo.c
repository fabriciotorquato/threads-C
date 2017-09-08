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


int main (int argc, char *argv[]) 
{ 
	int fd;
	char buff[500];
	
	//Criar um arquivo
		if((fd=creat("file.txt",0666))<0){
			exit(errno);
		}
		
	//Abrir arquivo para escrita
		if((open("file.txt",O_RDWR))<0){
			exit(errno);
		}
		memset(buff,'\0',sizeof(buff));
		strcat(buff,"Oi sou ze");
		if(write(fd,buff,sizeof(buff))<0){
			exit(errno);
		}
		close(fd);
	
	
	//Abrir arquivo para leitura
		if((open("file.txt",O_RDONLY))<0){
			exit(errno);
		}
		memset(buff,'\0',sizeof(buff));
		if(read(fd,buff,sizeof(buff))<0){
			exit(errno);
		}
		close(fd);
		printf("Valor do buffer = %s\n",buff);
	
	
	//Destroi arquivo
		unlink("file.txt");
	exit(EXIT_SUCCESS); 
} 
