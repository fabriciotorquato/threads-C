#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgbuf
{
    long mtype;
    long mv1;
    long mv2;
    long mresp;
} msg;

int main (int argc, char *argv[])
{
	pid_t pid, pid_ret;
	int status;
	long a;
	msg rcvbuf;
	int msqid;
    key_t key;
		
	//Criando fila de menssagens
	key = 1234;
	if ((msqid = msgget(key, IPC_CREAT | O_EXCL | 0666)) < 0) 
	{
		exit(errno);
	}
	
	pid = fork();
	if( pid < 0 ) //processo com valor menor que zero mostra um erro ao criar o processo
	{
		printf( "O processo filho não pode ser criado \n");
 		perror( argv[0] );
		exit(errno);
	}
	else if (pid == 0) // processo igual a zero é o processo filho
	{
		execl("Calculadora_2_parte_2","Calculadora_2_parte_2", NULL);
	}
	
	//Aguardando fim dos processos filhos			
	while((pid_ret = wait(&status)) != -1)
	{
		
	}	
	//Recenendo menssagens	
	if (msgrcv(msqid, &rcvbuf, sizeof(rcvbuf), 2, IPC_NOWAIT) < 0) {
		perror("PAI: msgrcv");
		exit(errno);
	}
	
	printf("Digite o valor para subtrair:");
	scanf("%ld",&a);
	
	printf("%ld - %ld = %ld \n",rcvbuf.mresp,a,rcvbuf.mresp-a);
	
	//Finalizando fila de menssagens 	
	if (msgctl(msqid, IPC_RMID, NULL) <0)
	{
		perror("msgctl");
		exit(errno);
	}
	
	exit(EXIT_SUCCESS);
}
