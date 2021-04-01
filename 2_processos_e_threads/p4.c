#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
        
/*definindo funções que as threads irão executar para imprimir A, B e C
	adicionem -lpthread ao final para compilar.
	ex: gcc p4.c -o p4 -lpthread
*/
pthread_cond_t condA, condB; // cria uma variável para sincronizar as threads.
pthread_mutex_t o_mutex; // cria uma variável mutex para controlar o acesso.


void* printA()
{
	pthread_mutex_lock(&o_mutex); // requisita o acesso.
 	printf("A");
	pthread_cond_signal(&condA); // emite um comando para o thread B.
	pthread_mutex_unlock(&o_mutex); // libera o acesso.
	pthread_exit(0); //para finalizar a thread
        
}

void* printB()
{	
	pthread_mutex_trylock(&o_mutex); // tenta utilizar o recurso.
	pthread_cond_wait(&condA,&o_mutex); // aguarda o sinal de A.
	printf("B");
	pthread_cond_signal(&condB); // emite um comando para o thread C.
	pthread_mutex_unlock(&o_mutex); // libera o recurso.
	pthread_exit(0);
       
}

void* printC()
{
	pthread_mutex_trylock(&o_mutex); // tenta utilizar o recurso.
	pthread_cond_wait(&condB,&o_mutex);	// aguarda o sinal de B.
	printf("C\n");
	pthread_mutex_unlock(&o_mutex); // libera o acesso.
 	pthread_exit(0);
}

int main()
{
    //definindo as variáveis que armazenarão as ids das threads
	pthread_t tA, tB, tC; 
	
	pthread_mutex_init(&o_mutex,0); // inicializa o mutex.
	pthread_cond_init(&condA,0); // inicializa a variavel de condicao A.
	pthread_cond_init(&condB,0); // inicializa a variavel de condicao B.
    //criando as threads
   	pthread_create(&tA,0,printA,0); //guarda-se a id em tA e chama a função printA
    	pthread_create(&tB,0,printB,0); // guarda-se a id em tB e chama a funcao printB
    	pthread_create(&tC,0,printC,0); // guarda-se a id em tC e chama a funcao printC
    
    	pthread_join(tA, 0); //espera execução da thread com id = tA (que imprime A)
    	pthread_join(tB, 0); // espera a execução da thread com id = TB
    	pthread_join(tC, 0); // espera a execução da thread com id = TC
    	pthread_cond_destroy(&condA); // destroi a variavel de condicao A.
    	pthread_cond_destroy(&condB); // destroi a variavel de condicao B.
    	pthread_mutex_destroy(&o_mutex); // destroi o mutex.
    
    	return 0;
}

