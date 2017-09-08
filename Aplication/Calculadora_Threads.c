#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/syscall.h>

int valor;

void *threadf (void *arg)
{
	int a = (intptr_t) arg;
	int b;
	
	printf("digite o valor de subtracao: ");
	scanf("%d",&b);

	printf("%d - %d = %d\n",a,b,a-b);
	
	pthread_exit((void *) syscall(SYS_gettid));
}

int main (int argc, char *argv[])
{
		pthread_t thread;
		void *status;
		int a,b;
		
		printf("Digite o primeiro valor de soma: ");
		scanf("%d",&a);
		printf("Digite o segundo valor de soma: ");
		scanf("%d",&b);

		//criacao da thread
		if ((pthread_create(&thread,NULL,&threadf,(void *) (intptr_t) (a+b))) < 0)
		{
			printf("Erro na criação do thread \n");
			exit(errno);
		}

		//Sincronizacao da thread com o processo principal
		pthread_join(thread,&status); 
		
		exit(EXIT_SUCCESS);
}
