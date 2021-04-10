#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// número máximo de leitores.
#define MAX_READERS 5
// número máximo de escritores
#define MAX_WRITERS 5
// máximo de itens a serem atualizados.
#define MAX_ITEMS 5

void *reader(void *pno);
void *writer(void *pno);

// instancia um mutex para controlar o acesso à rc.
pthread_mutex_t rSem;
// instancia um semaforo para controlar o acesso à base de dados.
sem_t db;
// contador para o número de leitores tentando acessar o recurso.
int rc = 0;
// dados a serem atualizados pelo escritor.
int data = 0;

int main(int argc, char * argv[])
{
    pthread_t rd[MAX_READERS], wt[MAX_WRITERS]; // instancia as threads do leitor e do escritor.
    int a[MAX_READERS];
    sem_init(&db, 0, 1); // inicializa o semáforo para controle do banco em 1.
    pthread_mutex_init(&rSem, 0); // inicializa o mutex para controle do rc.
    for(int i = 0;i < MAX_READERS;i++)
    {
        a[i] = i;
        pthread_create(&rd[i], 0, (void*)reader, (void*)&a[i]);
    }
    for(int i = 0;i < MAX_WRITERS;i++)
    {
        a[i] = i;
        pthread_create(&wt[i], 0 , (void*)writer, (void*)&a[i]);
    }
    for(int i = 0;i < MAX_READERS;i++)
        pthread_join(rd[i], 0);
    for(int i = 0;i < MAX_WRITERS;i++)
        pthread_join(wt[i], 0);

    sem_destroy(&db);
    pthread_mutex_destroy(&rSem);

    return 0;
}
void *reader(void * pno)
{
    int numReader = *(int*)pno;
    pthread_mutex_lock(&rSem); // obtém o semáforo e incrementa o número de leitores acessando o recurso.
    rc++;
    printf("reader %d tried to use the database, %d readers currently\n", numReader,rc);
    if(rc == 1)
    {
        sem_wait(&db); // o primeiro leitor obtém acesso ao recurso e permite aos seguintes a utilização.
    }
    pthread_mutex_unlock(&rSem);
    printf("reader %d is using the database\n", numReader);
    printf("current value of data: %d\n", data);
    pthread_mutex_lock(&rSem);
    printf("reader %d left the database\n", numReader); // sinaliza que um dos leitores deixou a base de dados.
    rc--;
    if(rc == 0)
    {
        sem_post(&db);// fornece acesso ao escritor quando todos os leitores estão fora.
    }
    pthread_mutex_unlock(&rSem); // sai da zona crítica.
}
void *writer(void *pno)
{
        int numberWriter = *(int*)pno;
        sem_wait(&db); // aguarda a saída dos leitores para realizar à escrita.
        data++; // modifica o valor da base de dados.
        printf("Writer %d updated data to %d\n", numberWriter, data);
        sem_post(&db); // deixa a zona critica, atualizando a base de dados.
}
