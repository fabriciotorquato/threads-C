#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define LIMIT 1024

 int lerParenteses(char texto[]){
	int tam = strlen(texto);
	int cont=0;
	for(int i=0;i<tam;i++){
		if(texto[i]=='(')
			cont++;
	}
	return cont+1;
}

 int resolver(char texto[]){
	int v1=0,v2=0;
	char op;
	
	v1=texto[0]-'0';
	op=texto[1];
	v2=texto[2]-'0';
	
	if(op=='+')
		v1+= v2;
	else if(op=='-')
		v1-= v2;
	else if(op=='*')
		v1*= v2;
	else if(op=='/')
		v1/= v2;
	return v1;
}

void* thrCalcular(void *arg){ 
  
	int k=0;
	int tam;
	int fd = (intptr_t) arg;
	
	char texto[LIMIT];
	char novo[LIMIT];
	char expressao[LIMIT];
	char aux[LIMIT];
	char resolucao[LIMIT];
	
	lseek (fd, 0 , SEEK_SET);
	read(fd,texto,sizeof(texto));
	printf("leu aqui %s\n",texto);
	
    pthread_t thread;

	tam=strlen(texto);
	
	for(int i=0;i<tam;i++,k++){
		if(texto[i]=='('){
			int cont = 1;
			int j=0;
			i++;
			
			while(cont>0){
				expressao[j++]=texto[i++];
				if(texto[i]=='(')
					cont++;
				if(texto[i]==')')
					cont--;
			}
			
			expressao[j]='\0';
			novo[k]='\0';
			
			lseek (fd, 0 , SEEK_SET);
			write(fd,expressao,LIMIT);
			
			if ((pthread_create(&thread, NULL, thrCalcular, (void *) (intptr_t) fd)) < 0)
			{
				printf("Erro na criação do thread \n");
				exit(errno);
			}
			 
			pthread_join(thread, NULL);
			
			lseek (fd, 0 , SEEK_SET);
			read(fd,aux,sizeof(aux));	
			
			strcat(novo,aux);
			
		}else if(texto[i]!=')'){
			novo[k]=texto[i];	
		}
	}
	novo[k]='\0';
	printf("expressao: %s\n",novo);	
	int resolvido = resolver(novo);
	
	sprintf(resolucao, "%d",resolvido);
	
	lseek (fd, 0 , SEEK_SET);
	write(fd,resolucao,LIMIT);

	pthread_exit((int *)syscall(SYS_gettid));
} 
int main (int argc, char *argv[]) 
{ 
    int fd;
	char texto[1024];
	
	scanf(" %s",texto);
	
    pthread_t thread;
	
	fd = open("arq.txt",O_RDWR|O_CREAT|O_EXCL, 0666);
	
	lseek (fd, 0 , SEEK_SET);
	write(fd,texto,LIMIT);
	
	if ((pthread_create(&thread, NULL, thrCalcular, (void *) (intptr_t) fd)) < 0)
	{
		printf("Erro na criação do thread \n");
		exit(errno);
	}
	pthread_join(thread, NULL);
	
	lseek (fd, 0 , SEEK_SET);
	read(fd,texto,sizeof(texto));	
	close(fd);
	
	printf("%s\n",texto);
	
	unlink("arq.txt");
	
	exit(EXIT_SUCCESS); 
} 
