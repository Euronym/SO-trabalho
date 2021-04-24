#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>

/*
    definindo funções que as threads irão executar para imprimir A, B e C
	adicionem -lpthread ao final para compilar.
	ex: gcc p4.c -o p4 -lpthread
*/
sem_t condA, condB; // cria uma variável para sincronizar as threads.
pthread_mutex_t o_mutex; // cria uma variável mutex para controlar o acesso.
int cont = 0;
void* printA()
{
	pthread_mutex_lock(&o_mutex); // requisita o acesso.
    if(cont != 0)
    {
        pthread_mutex_unlock(&o_mutex);
        sched_yield();
    }
    else
    {
 	     printf("A\n");
         cont++;
         sem_post(&condA); // emite um comando para o thread B.
         pthread_mutex_unlock(&o_mutex); // libera o acesso.
	     pthread_exit(0); //para finalizar a thread
   }
}

void* printB()
{
    pthread_mutex_trylock(&o_mutex); // tenta utilizar o recurso.
    sem_wait(&condA); // aguarda o sinal de A.
    cont = 0;
	printf("B\n");
    sem_post(&condB); // emite um comando para o thread C.
	pthread_mutex_unlock(&o_mutex); // libera o recurso.
	pthread_exit(0);

}

void* printC()
{
    while(1)
    {
        pthread_mutex_trylock(&o_mutex); // tenta utilizar o recurso.
        if(cont != 0)
        {
            sched_yield();
            pthread_mutex_unlock(&o_mutex);
        }
        else
        {
            sem_wait(&condB);// aguarda o sinal de B.
	        printf("C\n");
	        pthread_mutex_unlock(&o_mutex); // libera o acesso.
 	        break;
        }
    }
    pthread_exit(0);
}

int main()
{
    //definindo as variáveis que armazenarão as ids das threads
	pthread_t tA, tB, tC;

	pthread_mutex_init(&o_mutex,0); // inicializa o mutex.
    sem_init(&condA, 0, 0);
    sem_init(&condB, 0, 0);

   	pthread_create(&tA,0,printA,0);

    pthread_create(&tB,0,printB,0);

    pthread_create(&tC,0,printC,0);

    pthread_join(tA, 0); //espera execução da thread com id = tA (que imprime A)
	pthread_join(tB, 0); // espera a execução da thread com id = TB
	pthread_join(tC, 0); // espera a execução da thread com id = TC

	sem_destroy(&condA); // destroi a variavel de condicao A.
    sem_destroy(&condB); // destroi a variavel de condicao B.
    pthread_mutex_destroy(&o_mutex); // destroi o mutex.

    	return 0;
}
