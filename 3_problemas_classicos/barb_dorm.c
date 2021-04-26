#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// o barbeiro tem 5 clientes.
#define MAX_CUSTOMERS 5
// há 3 cadeiras disponíveis para espera nesse estabelecimento.
#define MAX_SEATS 3

void * customer(void * pno);
void * barber(void * pno);

// controla o acesso aos assentos disponíveis.
pthread_mutex_t seats;
// semáforo para contar o número de clientes aguardando para serem atendidos.
sem_t customers;
// semaforo binario para verificar a disponibilidade de um barbeiro em atender um recurso.
sem_t barberReady;
// conta a quantidade de cadeiras disponíveis no estabelecimento.
int free_seats = MAX_SEATS;
// conta a quantidade de clientes não atendidos.
int no_served_custs = 0;

int main(int argc, char * argv[])
{
    // instancia as threads.
    pthread_t c[MAX_CUSTOMERS], b;
    // cria uma array para numerar os clientes.
    int a[MAX_CUSTOMERS];
    //inicializa o mutex.
    pthread_mutex_init(&seats, 0);
    // inicializa os semáforos.
    sem_init(&barberReady, 0, 0);
    sem_init(&customers, 0, 0);
    //inicializa as threads dos clientes.
    for(int i = 0;i < MAX_CUSTOMERS;i++)
    {
        a[i] = i;
        pthread_create(&c[i], 0, customer, (void*)&a[i]);
    }
    //inicializa a thread do barbeiro.
    pthread_create(&b, 0, barber, 0);
    for(int i = 0;i < MAX_CUSTOMERS;i++)
    {
        pthread_join(c[i], 0);
    }
    pthread_join(b, 0);

    sem_destroy(&customers);
    sem_destroy(&barberReady);
    pthread_mutex_destroy(&seats);
    return 0;
}
void *customer(void *pno)
{
    int numCostumer = *(int*)pno;
    // tenta obter acesso à região crítica.
    pthread_mutex_lock(&seats);
    // verifica se há cadeiras disponíveis no estabelecimento para atender o cliente.
    if(free_seats > 0)
    {
        printf("Customer %d is waiting in the room\n", numCostumer);
        // decrementa o número de assentos disponiveis.
        free_seats--;
        // notifica o barbeiro que há clientes esperando para serem atendidos.
        sem_post(&customers);
        // O cliente teve sucesso em obter uma cadeira, de modo que a trava não é mais necessária.
        pthread_mutex_unlock(&seats);
        // aguarda que o barbeiro esteja pronto para cortar.
        sem_wait(&barberReady);
    }
    else{
        // libera a trava ao sair do estabelecimento sem sucesso.
        pthread_mutex_unlock(&seats);
        // executa essa linha de código quando o cliente falha em conseguir um lugar vazio.
        printf("Costumer %d couldn't enter the room and had to go home :(\n", numCostumer);
        no_served_custs++;
    }
    pthread_exit(0);
}
void *barber(void *pno)
{
    int counter = 0;
    while(1)
    {
        // aguarda os clientes chegarem no estabelecimento para trabalhar.
        sem_wait(&customers);
        // bloqueia o acesso à região crítica e modifica o número de assentos.
        pthread_mutex_lock(&seats);
        // incrementa o número de assento vazios no estabelecimento(cliente prestes a ser atendido).
        free_seats++;
        // deixa a região crítica após alterar o valor.
        pthread_mutex_unlock(&seats);
        // sinaliza que o barbeiro está pronto para atender.
        sem_post(&barberReady);
        // o barbeiro terminou de servir um cliente.
        printf("The barber just gave an haircut!\n");
        // incrementa o contador.
        counter++;
        // quebra o laço quando o número determinado de clientes for atendido.
        if(counter == MAX_CUSTOMERS - no_served_custs)
            break;
    }
    pthread_exit(0);
}
