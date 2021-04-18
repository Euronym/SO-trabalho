#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tempoMedioSorteio(Process processes[], int n);
int tempoEsperaSorteio(Process processes[], Process shuffled_array[], int n, int wait_time[]);
int turnaroundSorteio(Process shuffled_array[], int n , int wait_time[], int tat[]);
void swap(Process *a, Process *b);

int tempoMedioSorteio(Process processes[], int n)
{
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
    // cria uma array para armazenar os elementos sorteados.
    Process shuffled_array[n];
    int i;
    tempoEsperaSorteio(processes,shuffled_array, n, wait_time);
    //função para achar o tempo de turn around para cada processo.
    turnaroundSorteio(shuffled_array, n, wait_time, tat);
    //exibe os detalhes de cada processo.
    printf("PID  Burst   Waiting Turn around \n");
    // realiza as somas para calcular as médias do tempo de espera e de turn around.
    for(i = 0; i < n; i++)
    {
       total_wt = total_wt + wait_time[i];
       total_tat = total_tat + tat[i];
       printf(" %d\t  %d\t\t %d \t%d\n", shuffled_array[i].proc_id, shuffled_array[i].burst_time, wait_time[i], tat[i]);
    }
    printf("Average waiting time = %f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %f\n", (float)total_tat / (float)n);
    return 0;
}
// função para trocar dois processos de lugar na fila (funciona de maneira aleatória).
void swap(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}
int tempoEsperaSorteio(Process processes[], Process shuffled_array[], int n, int wait_time[])
{
    //define a semente necessária para gerar números aleatórios.
    srandom(time(NULL));
    // o primeiro processo não precisa esperar.
    wait_time[0] = 0;
    // passa os elementos da array de processos para a array a ser reorganizada.
    for(int i = 0;i < n;i++)
    {
        shuffled_array[i] = processes[i];
    }
    // reorganiza aleatoriamente os processos na fila de execução.
    for(int i = n - 1; i > 0;i--)
    {
        int j = random() % (i + 1);
        swap(&shuffled_array[i], &shuffled_array[j]);
    }
    // calcula o tempo de espera de cada processo, que depende do tempo de espera do processo anterior
    // e de sua execução.
    for(int i = 1;i < n;i++)
    {
        wait_time[i] = shuffled_array[i - 1].burst_time + wait_time[i - 1];
    }
    return 0;
}
int turnaroundSorteio(Process shuffled_array[],int n, int wait_time[], int tat[])
{
    // calcula o tempo de turn around para cada processo somando o tempo de burst com o tempo de espera.
    for(int i = 0;i < n;i++)
    {
        tat[i] = shuffled_array[i].burst_time + wait_time[i];
    }
    return 0;
}
