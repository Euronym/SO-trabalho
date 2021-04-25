#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

/*
    definindo funções que as threads irão executar para imprimir A, B e C
	adicionem -lpthread ao final para compilar.
	ex: gcc p4.c -o p4 -lpthread
*/
//cria dois semáforos para sincronizar as threads
sem_t condA, condB; 
// cria uma variável mutex para controlar o acesso.
pthread_mutex_t o_mutex; 

void* printA()
{
	// requisita o acesso.
	pthread_mutex_lock(&o_mutex); 
	// exibe a mensagem.
	printf("A");
 	// sinaliza que B pode executar.
	sem_post(&condA); 
	// deixa a zona crítica
	pthread_mutex_unlock(&o_mutex); 
	// finaliza
	pthread_exit(0); 
}

void* printB()
{
	// aguarda a thread A executar.
	sem_wait(&condA); 
	// requisita acesso à zona crítica.
	pthread_mutex_lock(&o_mutex); 

	printf("B");
	// sinaliza para o thread C.
	sem_post(&condB); 
	// libera o recurso.
	pthread_mutex_unlock(&o_mutex); 
	//	finaliza
	pthread_exit(0);
}

void* printC()
{

	// aguarda a thread B executar.
	sem_wait(&condB); 
	// tenta utilizar o recurso.
	pthread_mutex_lock(&o_mutex); 
	printf("C\n");
	// sai da zona crítica
	pthread_mutex_unlock(&o_mutex); 
	//finaliza
	pthread_exit(0);	

}

int main()
{
    //definindo as variáveis que armazenarão as ids das threads
	pthread_t tA, tB, tC;
	// inicializa o mutex.
	pthread_mutex_init(&o_mutex,0); 
	// inicializa os semáforos
    sem_init(&condA, 0, 0);
    sem_init(&condB, 0, 0);
	// cria as threads.
   	pthread_create(&tA,0,printA,0);
   	pthread_create(&tB,0,printB,0);
   	pthread_create(&tC,0,printC,0);
 	//espera execução da thread com id = tA (que imprime A)
    pthread_join(tA, 0);
    // espera a execução da thread com id = TB
	pthread_join(tB, 0);
	// espera a execução da thread com id = TC
	pthread_join(tC, 0); 
	// destroi o semáforo A.
	sem_destroy(&condA);
	// destroi o semáforo B. 
    sem_destroy(&condB); 
    // destroi o mutex.
    pthread_mutex_destroy(&o_mutex); 
    
    return 0;
}
