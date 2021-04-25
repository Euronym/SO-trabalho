#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Quantidade de números no array //
#define BUFFER 9

#define NUMBER_THREADS 2

// procedimento que implementa o algoritmo de ordenação bubble_sort //
void *bubble_sort();
// Procedimento que mostra os vetores ordenados na saída padrão //
void *mostrar_vetor();

// Mutex para a sincronização das threads //
pthread_mutex_t mutex;
// Condição, utilizando semáforo, para a sincronização das threads //
sem_t sort_condition;

// cria uma flag para a sincronização das threads.
int cont = 0;

int numeros[BUFFER] = {9, 3, 2, 5, 1, 0, 4, 7, 6}; // Arrays de inteiros para ordenação //

int main() {
	pthread_t sort_thread, printer_thread;
	pthread_mutex_init(&mutex, 0);
	sem_init(&sort_condition, 0,0);
	printf("\x1b[31mCriando uma thread para ordenação.\x1b[0m\n");
	pthread_create(&sort_thread,0, bubble_sort,0); // Cria uma thread para ordenação //
	pthread_create(&printer_thread,0, mostrar_vetor,0); //Cria uma thread para mostrar o vetor ordenado //
	pthread_join(sort_thread, 0); // Espera a execução da thread de ordenação //
	pthread_join(printer_thread, 0); // Espera a execução da thread que mostra o vetor ordenado //
	pthread_mutex_destroy(&mutex);
	sem_destroy(&sort_condition);
	return 0;
}

void *bubble_sort() 
{
	pthread_mutex_lock(&mutex);
	int aux = 0;
	for (int i = 0 ; i < BUFFER - 1; i++ ) 
	{
		for (int j = 0; j < BUFFER - 1; j++) 
		{
			if ( numeros[j] > numeros[j+1] ) 
			{
				aux = numeros[j];
				numeros[j] = numeros[j+1];
				numeros[j+1] = aux;
			}
		}
	}
	cont++;
	sem_post(&sort_condition); // Emite um sinal para a thread mostrar_vetor() //
	pthread_mutex_unlock(&mutex); // libera o recurso //
	pthread_exit(0);
}

void *mostrar_vetor() 
{
	while(1)
	{
		pthread_mutex_trylock(&mutex); // Tenta o acesso ao recurso //
		if(cont == 0)
		{
			pthread_mutex_unlock(&mutex);
			sched_yield();
		}
		else
		{
			sem_wait(&sort_condition); // Espera o sinal da thread de ordenação //
			printf("=== Vetor ordenado! ===\n");
			for (int k = 0; k < BUFFER; k++)
				printf("|%d|", numeros[k]);
			printf("\n");
			pthread_mutex_unlock(&mutex); // libera o recurso //
			break;
		}
	}
	pthread_exit(0);
}


