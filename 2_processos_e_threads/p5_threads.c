#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define BUFFER 9

void mostrar_vetor(int []);
void bubble_sort(int []);

void *thread1();
void *thread2();

int main(int argc, char * argv[])
{
    pthread_t td1,td2;

    pthread_create(&td1, 0,thread1, 0);
    pthread_create(&td2, 0,thread2, 0);
    return 0;
}
void * thread1()
{   


}
void *thread2()
{


}
