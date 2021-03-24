#include <stdio.h>
#include <pthread.h>
        
//definindo funções que as threads irão executar para imprimir A, B e C
void* printA()
{
        printf("A");
        pthread_exit(NULL); //para finalizar a thread
}

void* printB()
{
        printf("B");
        pthread_exit(NULL);
}

void* printC()
{
        printf("C\n");
        pthread_exit(NULL);
}

int main()
{
    //definindo as variáveis que armazenarão as ids das threads
    pthread_t tA, tB, tC; 

    //criando as threads
    pthread_create(&tC,NULL,printC,NULL); //guarda-se a id em tC e chama a função printC
    pthread_create(&tB,NULL,printB,NULL);
    pthread_create(&tA,NULL,printA,NULL);
    
    pthread_join(tA, NULL); //espera execução da thread com id = tA (que imprime A)
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);
    
    return 0;
}

/*
OBS: não tenho certeza, mas ,pelo que vi, a execução das threads começa pela última thread difinida, 
nesse caso, a A, então poderia deixar apenas o último comando pthread_join(tC, NULL) e, mesmo assim,
a saída seria ABC, pois esperaria a execução da thread C, o qual é a última a ser executada para, 
assim, parar o programa
*/