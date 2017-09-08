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

int main (int argc, char *argv[])
{
	int a,b,fd;
	char str[3];
	
	printf("Digite o primeiro valor de soma:");
	scanf("%d",&a);
	printf("Digite o segundo valor de soma:");
	scanf("%d",&b);
	
	sprintf(str, "%d", a+b);
	
	fd = open("com", O_WRONLY | O_NDELAY);
	if (fd < 0 )
	{
		perror(argv[0]);
		exit (EXIT_FAILURE);
	}
	write(fd,str,sizeof(str));
	close(fd);
	
	exit (EXIT_SUCCESS);
}
