#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

#define TIME_SLICE 3
#define MAX_PROCESS 10

// Cálculo das médias de escalonamento //
void average_time(Process[], int[], int[], int[]);
// Definição do tempo de vida de cada processo //
int turn_around_time(Process[], int[], int tat[]);
// Definição do tempo de espera de cada process //
int waiting_time(int[], int[]);

int main () {
	// Todos os processos no sistema operacional //
	Process processes[MAX_PROCESS];
	// Quantidade de processos no buffer //
	int wait_time[MAX_PROCESS], tat[MAX_PROCESS];
	// Array de Burst_times //
	int remaind_time[MAX_PROCESS];

	// Define aleatoriamente Burst Time, e incrementa um PID //
	for (int i = 0; i < MAX_PROCESS; i++) {
		processes[i].burst_time = (rand()+1) % 20;
		processes[i].proc_id = i;
	}

	// Inicializa um array de burst times //
	for (int i = 0; i < MAX_PROCESS; i++) {
		remaind_time[i] = processes[i].burst_time;
	}
	
	average_time(processes, wait_time, tat, remaind_time);
	return 0;
}

void average_time(Process processes[], int wait_time[], int tat[], int remaind_time[]) {
	float total_wt, total_tat = 0;
	waiting_time(remaind_time, wait_time);
	turn_around_time(processes, wait_time, tat);
	for (int i = 0; i < MAX_PROCESS; i++) {
		total_wt += wait_time[i];
		total_tat += tat[i];	
	}
	printf("PID\t Burst Time\tWait Time\tTurn Around Time\n");
	for (int i = 0; i < MAX_PROCESS; i++) {
		printf("%d  \t  %d   \t\t%d \t\t\t %d\n", processes[i].proc_id, processes[i].burst_time,
			       	wait_time[i], tat[i]);
	}
	printf("\x1b[33mAverage waiting time: %.3f \n\x1b[31mAverage turn around time: %.3f\x1b[0m\n",
			total_wt/MAX_PROCESS, total_tat/MAX_PROCESS);
	
}


int turn_around_time(Process processes[], int wait_time[], int tat[]) {
	for (int i = 0; i < MAX_PROCESS; i++) {
		tat[i] = wait_time[i] + processes[i].burst_time;
	}
	return 0;
}
int waiting_time(int remaind_time[], int wait_time[]) {
	// Variável contadora de processos concluídos //
	int done_condition;
	wait_time[MAX_PROCESS - 1] = 0;
	// Se a done_conditon atingir 10, todos os processos foram concluídos //
	while (done_condition < MAX_PROCESS) {
		for (int i = 0; i < MAX_PROCESS; i++) {
			// Verifica se o processo na posição i do array foi concluído //
			if ( remaind_time[i] == 0 ) {
				done_condition++;
				continue;
			// Do contrário é decrementado 1 da variável contadora //
			}  else if ( done_condition > 0 ) {
				done_condition--;
			}

			/* Como se trata de um escalonamento em círculo,
			 * é necessário levar em consideração o wait_time
			 * do último processo no estado de execução.
			*/
			if ( i == 0 )
				wait_time[i] = wait_time[MAX_PROCESS-1];
			else
				wait_time[i] = wait_time[i-1] + TIME_SLICE;

			// Se o burst time restante é maior que o TIME_SLICE, 
			// o burst time atual é decrementado
			if ( remaind_time[i] >= TIME_SLICE ) { 
				remaind_time[i] -= TIME_SLICE;
			// Senão o burst time restante será 0, ou seja, o processo,
			// conseguirá ser finalizado neste ciclo
			} else { 
				if ( i == 0 )
				wait_time[i] = wait_time[i-1] + remaind_time[i];
				remaind_time[i] = 0;
			}
		}
	}
	return 0;
}


