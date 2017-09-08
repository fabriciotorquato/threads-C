#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAXSIZE 128

typedef struct msgbuf
{
    long mtype;
    long mv1;
    long mv2;
    long mresp;
} msg;

int main (int argc, char *argv[])
{
	int msqid;
	long a,b;
    msg sndbuf;
    key_t key;
    
	key = 1234;
	//Acessando fila de mensagens
	if ((msqid = msgget(key, 0666 )) < 0) 
    {
        exit(errno);
    }
    
    printf("Digite o primeiro valor para somar:");
    scanf("%ld",&a);
    printf("Digite o segundo valor para somar:");
    scanf("%ld",&b);
    
    sndbuf.mtype = 2;
	sndbuf.mresp = a + b;
	
	//Enviando mensagens
    if (msgsnd(msqid, &sndbuf, sizeof(sndbuf), IPC_NOWAIT) < 0) 
    {
        exit(1);
    }
	
	exit (EXIT_SUCCESS);
}
