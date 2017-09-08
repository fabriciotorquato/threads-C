#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
	pid_t pid;
	int a,b;

	pid = fork();
	if( pid < 0 ) //processo com valor menor que zero mostra um erro ao criar o processo
	{
		printf( "O processo filho não pode ser criado \n");
 		perror( argv[0] );
		exit( errno );
	}
	
	else if ( pid > 0) // processo positivo e o processo pai
	{
		sleep(20);
		printf("SOMA\ndigite o primeiro valor ");
		scanf("%d",&a);
		printf("digite o segundo valor ");
		scanf("%d",&b);
		printf("Soma = %d\n",a+b);
		system("read b");
	}

	else// processo igual a zero é o processo filho
	{
		printf("SUBTRACAO\ndigite o primeiro valor ");
		scanf("%d",&a);
		printf("digite o segundo valor ");
		scanf("%d",&b);
		printf("Subtracao = %d\n",a-b);
	}
	
	
	
	exit(EXIT_SUCCESS);
}





