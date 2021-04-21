#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "bubble_sort.h"

#define MAX_PROCESS 10

// Cálculo da média das métricas de escalonamento //
void sjf_avgtime(Process[], int);
// Definição do tempo de espera de cada processo //
int sjf_waitingtime(int[], int, int[]);
// Definição do tempo de vida de cada processo //
int sjf_turnaroundtime(int[], int, int[], int[]);

int sjf_waitingtime(int burst_time_array[],int n_processes, int wait_time[]) {
	bubble_sort(burst_time_array, n_processes);
	wait_time[0] = 0;
	for (int i = 1; i < n_processes; i++)
		wait_time[i] = burst_time_array[i-1] + wait_time[i-1];
	return 0;
}

int sjf_turnaroundtime(int burst_time_array[], int n_processes, int tat[], int wait_time[]) {
	for (int i = 0; i < n_processes; i++)
		tat[i] = burst_time_array[i] + wait_time[i];
	return 0;
}

void sjf_avgtime(Process processes[], int n_processes) {
	// Array de burst time //
	int burst_time_array[n_processes];
	// alocação dos burst_times em um array //
	for (int i = 0; i < n_processes; i++)
	{
		burst_time_array[i] = processes[i].burst_time;
	}
	float total_wt = 0, total_tat = 0;
	// Tempo de espera para execução de do processo //
	int wait_time[n_processes];
	// Tempo de vida de um processo //
	int tat[n_processes];
	sjf_waitingtime(burst_time_array, n_processes, wait_time);
	sjf_turnaroundtime(burst_time_array, n_processes, tat, wait_time);
	printf("PID\tBurst Time\tWaiting time\tTurn around time\n");

	// Calcula o tempo total das respectivas métricas de escalonamento //
	for (int i = 0; i < n_processes; i++) {
		total_wt += wait_time[i];
		total_tat += tat[i];
	}

	// Mostra a média das métricas na saída padrão //
	for (int i = 0; i < n_processes; i++) {
		printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].proc_id, burst_time_array[i], wait_time[i], tat[i]);
	}
	printf("\x1b[31mAverage wait time: %.3f\n\x1b[33mAverage turn around time: %.3f\x1b[0m\n",
		total_wt/(float)n_processes, total_tat/(float)n_processes);
}
