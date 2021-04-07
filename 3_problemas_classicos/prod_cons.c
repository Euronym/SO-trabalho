#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h> // biblioteca para trabalhar com semáforos.
#include <pthread.h> // biblioteca para a utilização de threads.

#define N 100 // define o tamanho do buffer compartilhado como 100.
#define MAX_ITEMS 5 // define o tamanho máximo de itens que podem ser produzidos como 5.
#define MAX_THREADS 2  // define o número máximo de produtores e consumidores criados como 2.

int buffer = 0; // inicializa o buffer.

// define um mutex para realização da exclusão mútua.
pthread_mutex_t mutex;

/* esse semáforo será decrementado pelo
  sistema e o buffer estará vazio quando N = 0 */
sem_t empty;

// esse semáforo será incrementado quando os recursos forem utilizados
sem_t full;

void *producer(void *p)
{
    for(int i = 0;i < MAX_ITEMS;i++)
    {
      sem_wait(&empty); // decrementa o contador empty inicializado em N.
      pthread_mutex_lock(&mutex); // obtém acesso exclusivo ao recurso modificando mutex para 0.
      buffer++; // armazena um item no buffer.
      printf("1 item produzido pelo produtor %d, %d no buffer\n", *((int*)p),buffer);
      pthread_mutex_unlock(&mutex); // libera o acesso ao recurso após ter produzido o item.
      sem_post(&full); // incrementa o contador full, sinalizando que um item foi produzido.
    }
}
void *consumer(void *p)
{
      for(int i = 0;i < MAX_ITEMS;i++)
      {
        sem_wait(&full); // decrementa o contador, consumindo 1 item se o buffer não estiver vazio.
        pthread_mutex_lock(&mutex); // obtém acesso exclusivo ao buffer.
        buffer--; // consome um item do buffer.
        printf("1 item consumido pelo consumidor %d, %d no buffer\n", *((int*)p), buffer);
        pthread_mutex_unlock(&mutex); // libera o acesso ao recurso após ter consumido o item
        sem_post(&empty); // incrementa o contador empty, sinalizando que um item foi consumido.
    }
}


int main(int argc, char* argv[])
{
    pthread_t p[MAX_THREADS], c[MAX_THREADS]; // cria duas threads para cada um deles.
    int a[2] = {1, 2}; // a única utilidade desse vetor é o mapeamento das threads.

    pthread_mutex_init(&mutex, 0); // inicializa o mutex.
    sem_init(&empty, 0, N); // inicializa o semáforo empty.
    sem_init(&full, 0, 0); // inicializa o semáforo full.

    for(int i = 0;i < MAX_THREADS;i ++)
    {
      // inicializa dois produtores.
      pthread_create(&p[i],0, (void*)producer,(void*) &a[i]);
    }
    for(int i = 0;i < MAX_THREADS;i ++)
    {
      //inicializa dois consumidores.
      pthread_create(&c[i],0 ,(void*)consumer,(void*) &a[i]);
    }
    for(int i = 0;i < MAX_THREADS;i ++)
    {
      pthread_join(p[i], 0); // aguarda a execução da thread producer.
    }
    for(int i = 0;i < MAX_THREADS;i ++)
    {
      pthread_join(c[i], 0); // aguarda a execução da thread consumer.
    }

    pthread_mutex_destroy(&mutex); // destrói as variáveis criadas ao final do programa.
    sem_destroy(&empty);
    sem_destroy(&full);


    return 0;
}
