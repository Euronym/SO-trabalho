#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "FIFO.h"
#include "sorteio.h"

// define como 10 o número máximo de processos que podem existir.
#define MAX_PROCESSES 10

// main function
int main(int argc, char * argv[])
{
    int burst_time[] = {5, 8, 12, 14 , 16 , 19, 4 ,3 ,2, 1};
    Process processes[MAX_PROCESSES];
    for(int i = 0;i < MAX_PROCESSES;i++)
    {
        processes[i].proc_id = i + 1;
        processes[i].burst_time = burst_time[i];
    }
    int n = sizeof(processes) / sizeof(processes[0]);
    avgtime(processes, n);
    tempoMedioSorteio(processes, n);
    return 0;
}
