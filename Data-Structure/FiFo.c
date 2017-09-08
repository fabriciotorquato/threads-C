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

typedef struct msgbuf
{
    long mtype;
    int mv1;
    int mv2;
    int mresp;
} msg;

int main (int argc, char *argv[]) 
{ 
	int status;
	pid_t pid;
	
	if((pid=fork())<0){
		exit(errno);
	}
	
	if(pid==0){
		
		msg buf;
		int msqid;
		buf.mtype = 1;
		buf.mv1 = 2;
		buf.mv2 = 3;
		
		key_t key = 1234;
		//Acessando fila de mensagens
		if ((msqid = msgget(key, 0666 )) < 0) 
		{
			exit(errno);
		}
		
		//Enviando menssagens
		if (msgsnd(msqid, &buf, sizeof(buf), IPC_NOWAIT) < 0) 
		{
			exit(errno);
		}

	}
	else{
		msg buf;
		int msqid;
		
		//Criando fila de menssagens
		key_t key = 1234;
		if ((msqid = msgget(key, IPC_CREAT | O_EXCL | 0666)) < 0) 
		{
			exit(errno);
		}
		
		//Aguardando fim dos processos filhos			
		while(wait(&status) != -1)
		{
		}
	
		//Recenendo menssagens	
		if (msgrcv(msqid, &buf, sizeof(buf), 1, IPC_NOWAIT) < 0) {
			exit(errno);
		}
		
		printf("RESPOTA = %d",buf.mv1+buf.mv2);
		
		//Finalizando fila de menssagens 	
		if (msgctl(msqid, IPC_RMID, NULL) <0)
		{
			exit(errno);
		}
	}
	
	
	exit(EXIT_SUCCESS); 
} 
