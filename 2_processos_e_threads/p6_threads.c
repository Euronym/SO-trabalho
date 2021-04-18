#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Quantidade de números no array //
#define BUFFER 9

#define NUMBER_THREADS 2

// Algoritmo de ordenação bubble_sort //
void *bubble_sort();
// Procedimento que mostra os vetores ordenados na saída padrão //
void *mostrar_vetor();

// Mutex para a sincronização das threads //
pthread_mutex_t mutex;
// Condição para a sincronização //
pthread_cond_t sort_condition;

// Arrays de inteiros para ordenação //
int numeros[BUFFER] = {9, 3, 2, 5, 1, 0, 4, 7, 6};

int main() {
	long sort_thread, printer_thread, t;
	pthread_t threads[2];
	pthread_mutex_init(&mutex, 0);
	pthread_cond_init(&sort_condition, 0);
	for (int i = 0; i < NUMBER_THREADS; i++) {
		if (i == 0) {
			printf("\x1b[31mCriando uma thread para ordenação..\x1b[0m\n");
	sort_thread = pthread_create(&threads[i], NULL, bubble_sort, (void *) t);
		if ( sort_thread ) {
			perror("pthread_create\n");
			exit(-1);
	
		}

		} else if (i == 1) {
			printer_thread = pthread_create(&threads[i], NULL, mostrar_vetor, (void *) t);
			if ( printer_thread ) {
				perror("pthread_create\n");
				exit(-1);
			}
		}
	}
	for (int i = 0; i < NUMBER_THREADS; i++)
		pthread_join(threads[i], NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&sort_condition);
	return 0;
}

void *bubble_sort() {
	pthread_mutex_lock(&mutex);
	int aux = 0;
	for (int i = 0 ; i < BUFFER - 1; i++ ) {
		for (int j = 0; j < BUFFER - 1; j++) {
			if ( numeros[j] > numeros[j+1] ) {
				aux = numeros[j];
				numeros[j] = numeros[j+1];	
				numeros[j+1] = aux;
			}			
		}
	}
	// Emite um sinal para a thread que realizará o mostrar_vetor() //
	pthread_cond_signal(&sort_condition);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

void *mostrar_vetor() {
	pthread_mutex_trylock(&mutex);
	pthread_cond_wait(&sort_condition, &mutex);
	printf("=== Vetor ordenado! ===\n");
	for (int k = 0; k < BUFFER; k++) 
		printf("|%d|", numeros[k]);
	printf("\n");
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

