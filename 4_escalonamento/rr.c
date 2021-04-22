#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

#define TIME_SLICE 3
#define MAX_PROCESS 10

// Cálculo das médias de escalonamento //
void rr_avgtime(Process[], int[], int[]);
// Definição do tempo de vida de cada processo //
int rr_turnaroundtime(Process[], int[], int [], int[], int[]);
// Definição do tempo de espera de cada processo //
int rr_waitingtime(Process[], int[], int[], int[], int[]);

int main () {
	// Todos os processos no sistema operacional //
	Process processes[MAX_PROCESS];
	// Tempo de chegado do process //
	int arrival_time[MAX_PROCESS];	
	// Array de bursts times //
	int remaind_time[MAX_PROCESS];

	// Define aleatoriamente Burst Time, e incrementa um PID //
	for (int i = 0; i < MAX_PROCESS; i++) {
		processes[i].burst_time = (rand()+1) % 20;
		processes[i].proc_id = i;
	}

	for (int i = 0; i < MAX_PROCESS; i++) {
		arrival_time[i] = i;
	}

	// Inicializa um array de burst times //
	for (int i = 0; i < MAX_PROCESS; i++) {
		remaind_time[i] = processes[i].burst_time;
	}

	rr_avgtime(processes, remaind_time, arrival_time);
	return 0;
}

void rr_avgtime(Process processes[], int remaind_time[], int arrival_time[]) {
	// Tempo total de um processo no escalonador //
	int turn_time[MAX_PROCESS];
	// Tempo de espera para cada process //
	int wait_time[MAX_PROCESS];
	// Tempo de vida de cada process //
	int tat[MAX_PROCESS];
	// Resultado total de algumas métricas //
	float total_wt, total_tat = 0;

	rr_waitingtime(processes, remaind_time, wait_time, arrival_time, turn_time);
	rr_turnaroundtime(processes, wait_time, tat, arrival_time, turn_time);

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


int rr_turnaroundtime(Process processes[], int wait_time[], int tat[], int arrival_time[], int turn_time[]) {	
	/*Realiza o cálculo do turnAT tendo como parâmetro o tempo total de cada
	* processo e o tempo de chegado do processo 
	*/
	for (int i = 0; i < MAX_PROCESS; i++) {
		tat[i] = turn_time[i] - arrival_time[i];
	}
	return 0;
}

int rr_waitingtime(Process processes[], int remaind_time[], int wait_time[], int arrival_time[], int turn_time[]) {
	// Variável contadora e uma variável sentinela //
	int i, done_condition;
	// Número de processos no escalonador //
	int buffer_process = MAX_PROCESS;
	int total_time;

	for (total_time = 0, i = 0; buffer_process != 0; ) {
		/* Se o tempo restante de execução é menor que que o TIME_SLICE
		* então o processo será finalizado nesse ciclo
		*/
		if (remaind_time[i] <= TIME_SLICE && remaind_time[i] > 0) {
			total_time += remaind_time[i];
			remaind_time[i] = 0;
			done_condition = 1;
		// Senão tempo restante é decrementado em um TIME_SLICE //
		} else if (remaind_time[i] > 0) {
			remaind_time[i] -= TIME_SLICE;
			total_time += TIME_SLICE;
		}
		// Verifica se o processo foi finalizado //
		if (remaind_time[i] == 0 && done_condition == 1) {
			buffer_process--;
			turn_time[i] = total_time; 
			wait_time[i] = total_time - processes[i].burst_time - arrival_time[i];
			done_condition = 0;
		// Se i é igual ao número de processos-1, então o ciclo de exucução finaliza //
		}
		
		if ( i == MAX_PROCESS - 1) {
			i = 0;	
		/* Se o tempo de chegada do próximo processo é menor que o tempo de execução do
		*  atual, então aquele processo será escalonado 
		*/
		} else if ( arrival_time[i + 1] <= total_time ) {
			i++;
		} else {
			i = 0;
		}
	}

	return 0;
}
