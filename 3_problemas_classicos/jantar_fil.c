#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> // biblioteca que permite a utilização de semáforos.
#include <pthread.h> // biblioteca que permite a utilização de threads.
#include <unistd.h> // biblioteca que contém algumas chamadas de sistema (só quero o sleep)

/*
    Implementação do jantar dos filósofos utilizando threads e semáforos.
    Resta saber se a implementação também deve ser feita utilizando processos.

    Obs: Somente dois filósofos comem por vez(para o caso de 5),
    cada filósofo solicitando acesso ao recurso utiliza dois garfos.
*/

#define N 5 // define o número de talheres e filósofos na mesa como 5.

sem_t room;  // semáforo para controlar o número de filósofos na mesa.
sem_t silverwares[N]; // define 5 semáforos binários, um por talher na mesa.

void eat(int philo_number) // somente indica quem está comendo em determinado momento.
{
  printf("philosopher %d is eating!\n", philo_number);
}

void *philosopher(void * pno)
{
  int philo_number = *(int *)pno; // passa o número associado ao filósofo à uma variável auxiliar.
  sem_wait(&room); // verifica se o recurso está disponível para uso, utilizando-o se estiver.
  printf("philosopher %d entered the room\n", philo_number);
  sem_wait(&silverwares[(philo_number)]); // pega o garfo na posição indicada.
  sem_wait(&silverwares[(philo_number + 1) % N]); // pega o garfo à direita.
  eat(philo_number);
  sleep(2); // gera uma pequena animação para mostrar que o filósofo está comendo.
  printf("philosopher %d has finished eating\n", philo_number);

  sem_post(&silverwares[(philo_number)]); // libera o acesso ao recurso.
  sem_post(&silverwares[(philo_number + 1) % N]); // libera o acesso ao recurso.
  sem_post(&room); // dá espaço para outro filósofo comer.

}

int main(int argc, char * argv[])
{
  pthread_t philosophers[N]; // cria 1 thread por filósofo.
  int a[N]; // um vetor para numerar os filósofos.
  sem_init(&room,0,N); // inicializa o semáforo room com o valor 5 (número de filósofos).

  for(int i = 0;i < 5;i++)
  {
    /*
      inicializa cada semáforo binário em 1, estando disponível para uso.
      Dada a implementação em threads, o segundo parâmetro do procedimento é
      definido como 0, devendo ser modificado para 1 em uma implementação com
      processos.
    */
    sem_init(&silverwares[i],0,1);
  }
  for(int i = 0;i < 5;i++)
  {
    /*
      inicializa cada thread correspondente, o último parâmetro somente é
      utilizado para numerar cada filósofo e facilitar o entendimento do
      código.
    */
    a[i] = i;
    pthread_create(&philosophers[i],0, philosopher, (void*)&a[i]);
  }
  for(int i = 0;i < 5;i++)
  {
    pthread_join(philosophers[i], 0); // espera a execução das threads indicadas.
  }
  for(int i = 0;i < 5;i++)
  {
    sem_destroy(&silverwares[i]);
  }
  sem_destroy(&room);

  return 0;
}
