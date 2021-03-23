#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // biblioteca para a criação da árvore de processos.
#include <sys/types.h> // biblioteca que contém os tipos necessários.

int main(int argc, char * argv[])
{
	pid_t filho1_pid; // cria o primeiro filho.
	pid_t filho2_pid; // cria o segundo filho.
	
	filho1_pid = fork();
	
	if(filho1_pid < 0) 
	{
		printf("Erro durante a criação do processo filho!");
		exit(1); // finaliza o programa caso ocorra um erro.
	}
	else if(filho1_pid == 0)
	{
		printf("PID do primeiro filho: %d\n",getpid());	
		printf("PID do pai no primeiro filho: %d\n",getppid());
	}
	else
	{
		/*  para o processo pai, o valor retornado é um
		identificador do processo filho  no processo pai, 
		sendo esse um número maior do que zero. */
		
		wait(NULL); // aguarda a execução do primeiro processo.
		filho2_pid = fork();
		if(filho2_pid < 0)
		{
			printf("Erro durante a criação do processo filho!");
			exit(1); // finaliza o programa caso ocorra um erro.
		}
		else if(filho2_pid == 0)
		{
			printf("PID do segundo filho: %d\n",getpid());	
			printf("PID do pai no segundo filho: %d\n",getppid());
		}
		else
		{
			wait(NULL); // aguarda a execução do segundo processo.
			printf("PID do pai: %d\n",getpid());	
		}
	}
	
	return 0;
}
