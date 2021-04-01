#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // biblioteca para a criação da árvore de processos.
#include <sys/types.h> // biblioteca que contém os tipos necessários.

int main(int argc, char * argv[])
{
	pid_t filho_pid = fork(); // cria um processo filho.
	if(filho_pid < 0) // retorna um valor negativo se a criação falha. 
	{
		printf("Erro durante a criação do processo filho!");
		exit(1); // finaliza o programa caso ocorra um erro.
	}
	else if(filho_pid == 0)
	{
		/* para o processo filho, um valor nulo é retornado
			quando realizada a chamada fork().   */
		printf("PID do processo pai: %d\n",getpid());
		printf("PID do processo avo: %d\n",getppid());
		
		pid_t neto_pid = fork();
		if(neto_pid < 0)
		{
			printf("Erro durante a criação do processo filho!");
			exit(1); // finaliza o programa caso ocorra um erro.
		}
		else if(neto_pid == 0)
		{
			printf("PID do processo neto: %d\n",getpid());
			printf("PID do processo pai: %d\n",getppid());
		}
		else
		{	
			wait(NULL); // espera a execução do processo neto.
			printf("PID do processo pai:%d\n",getpid());	
		}
	}
	else
	{
		wait(NULL); // espera a execução do processo filho.
		
		/*  para o processo pai, o valor retornado é um
		identificador do processo filho  no processo pai, 
		sendo esse um número maior do que zero. */
		printf("PID do processo avo: %d\n",getpid());	
	}
	return 0;
}
