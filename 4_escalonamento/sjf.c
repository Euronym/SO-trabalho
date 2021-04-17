#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "bubble_sort.h"

#define MAX_PROCESS 10

// Cálculo do tempo médio de execução de cada processo //
void average_time(Process[], int[]);
// Definição do tempo de espera de cada processo //
int waiting_time(int[], int[]);
// Definição do tempo de vida de cada processo //
int turn_around_time(int[], int[], int[]);


int main(){
	// Todos os processos do sistema //
	Process processes[MAX_PROCESS];
	// Array de burst time //
	int burst_time_array[MAX_PROCESS];
	// Definição aleatória do PID e burst time //
	for (int i = 0; i < MAX_PROCESS; i++) {
		processes[i].proc_id = rand() % 15;
		processes[i].burst_time = (rand()+3) % 18;
		
	}
	// alocação dos burst_times em um array //
	for (int i = 0; i < MAX_PROCESS; i++)
		burst_time_array[i] = processes[i].burst_time;
	average_time(processes, burst_time_array);

	return 0;

}

int waiting_time(int burst_time_array[], int wait_time[]) {
	bubble_sort(burst_time_array, MAX_PROCESS);
	wait_time[0] = 0;
	for (int i = 1; i < MAX_PROCESS; i++)
		wait_time[i] = burst_time_array[i-1] + wait_time[i-1];	
	return 0;
}


int turn_around_time(int burst_time_array[], int tat[], int wait_time[]) {
	for (int i = 0; i < MAX_PROCESS; i++)
		tat[i] = burst_time_array[i] + wait_time[i];
	return 0;
}

void average_time(Process processes[], int burst_time_array[]) {
	float total_wt, total_tat = 0;
	// Tempo de espera para execução de do processo //
	int wait_time[MAX_PROCESS];
	// Tempo de vida de um processo //
	int tat[MAX_PROCESS];	
	waiting_time(burst_time_array, wait_time);
	turn_around_time(burst_time_array, tat, wait_time);
	printf("PID\tBurst Time\tWaiting time\tTurn around time\n");
	
	// Calcula o tempo total das respectivas métricas de escalonamento //
	for (int i = 0; i < MAX_PROCESS; i++) {
		total_wt += wait_time[i];
		total_tat += tat[i];
	}

	// Mostra a média das métricas na saída padrão //
	for (int i = 0; i < MAX_PROCESS; i++) {
		printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].proc_id, burst_time_array[i], wait_time[i], tat[i]);
	}
	printf("\x1b[31mAverage wait time: %.3f\n\x1b[33mAverage turn around time: %.3f\n",
		total_wt/MAX_PROCESS, total_tat/MAX_PROCESS);
}
