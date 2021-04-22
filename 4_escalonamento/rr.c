#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

#define TIME_SLICE 3
#define MAX_PROCESS 10

// Cálculo das médias de escalonamento //
void rr_avgtime(Process[], int[], int[], int[]);
// Definição do tempo de vida de cada processo //
int rr_turnaroundtime(Process[], int[], int tat[]);
// Definição do tempo de espera de cada process //
int rr_waitingtime(int[], int[]);

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

	rr_avgtime(processes, wait_time, tat, remaind_time);
	return 0;
}

void rr_avgtime(Process processes[], int wait_time[], int tat[], int remaind_time[]) {
	float total_wt, total_tat = 0;
	rr_waitingtime(remaind_time, wait_time);
	rr_turnaroundtime(processes, wait_time, tat);
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


int rr_turnaroundtime(Process processes[], int wait_time[], int tat[]) {
	for (int i = 0; i < MAX_PROCESS; i++) {
		tat[i] = wait_time[i] + processes[i].burst_time;
	}
	return 0;
}
int rr_waitingtime(int remaind_time[], int wait_time[]) {

	struct Node_process {
		int value;
		int preview;
		int next;
	};

	Node_process all_bursts[MAX_PROCESS];

	// TODO Certamente uma lista a rigor terá de ser implementada //
	
	/* FIXME a pseudo-lista não funcionou devido ao problema de referências
	 * Pois, parti do pressuposto que poderia ser efetuado com algumas característica
	 * desejáveis, ocultando outras.
	 * Basicamente, o problema reside na retirada de uma nodo da lista,
	 * traduzindo para a situação um processo já finalizado
	 */
 	
	// Inicializa as devidas referências para uma pseudo-lista //
	for (int i = 1 ; i < MAX_PROCESS-1; i ++) {
		if ( i == 0) {
			all_bursts[0].value = remaind_time[0];
			all_bursts[0].preview = remaind_time[MAX_PROCESS - 1];
			all_bursts[0].next = remaind_time[1];
		} if ( i == MAX_PROCESS - 1) {
			all_bursts[MAX_PROCESS - 1].atual = remaind_time[MAX_PROCESS - 1];
			all_bursts[MAX_PROCESS - 1].preview = remaind_time[MAX_PROCESS -2];
			all_bursts[MAX_PROCESS - 1].next = remaind_time[0];
		}
		all_bursts[i].atual = remaind_time[i];
		all_bursts[i].next = remaind_time[i+1];
		all_bursts[i].preview = remaind_time[i-1];
	}
	
	// Inicializa o wait time do primeiro processo //
	wait_time[0] = 0;
	int done_condition = 0;
	while (done_condition < MAX_PROCESS);
		for (int i = 0; i < MAX_PROCESS; i++) {
			// verifica se todos os processos foram concluídos //
			if (all_bursts[i].atual == 0) {
				done_condition++;
				continue;
			}

			/* Verifica se o time slice é maior do que o tempo restante de burst 
			* se for, o processo será concluido nesse ciclo.
			*/
			if (TIME_SLICE >= all_bursts[i].atual.value) {
				wait_time[i+1] = all_bursts[i].atual;
				all_bursts[i].preview = all_burst[i].next;
				all_bursts[i].next = all_burst[i].preview;
				all_bursts[i].value = 0;
			/* se não for, o tempo de burst é decrementado na quantidade de um 
			* time slice
			*/
			} else {
				all_bursts[i].value -= TIME_SLICE;
				wait_time[i+1] = TIME_SLICE;
			}
		done_condition--;
	}

	
	return 0;
}
