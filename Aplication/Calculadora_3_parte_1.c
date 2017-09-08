#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
	pid_t pid, pid_ret;
	int a, b, status, fd;
	char str2[3];
	
	mknod("com", S_IFIFO|0666, 0);
	
	pid = fork();
	if( pid < 0 ) //processo com valor menor que zero mostra um erro ao criar o processo
	{
		printf( "O processo filho não pode ser criado \n");
 		perror( argv[0] );
		exit( errno );
	}
	else if (pid==0){
		execl("Calculadora_3_parte_2","Calculadora_3_parte_2", NULL);
	}
	fd = open("com", O_RDONLY);
	if (fd < 0)
	{
		perror(argv[0]);
		exit (EXIT_FAILURE);
	}
	//Aguardando fim dos processos filhos			
	while((pid_ret = wait(&status)) != -1)
	{
		
	}	
	read(fd,str2, 3);
	close(fd);
		
	a = atoi(str2);
	
	printf("Digite o valor para subtrair: ");
	scanf("%d",&b);
	
	printf("%d - %d = %d\n",a,b,a-b);
		
	exit(EXIT_SUCCESS);
}
