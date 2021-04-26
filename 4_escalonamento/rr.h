#include <stdio.h>
#include <stdlib.h>

// Cálculo das médias de escalonamento //
void rr_avgtime(Process[], int, int);
// Definição do tempo de vida de cada processo //
int rr_turnaroundtime(Process[], int, int[], int [], int[]);
// Definição do tempo de espera de cada processo //
int rr_waitingtime(Process[], int, int[], int[], int[], int);

void rr_avgtime(Process processes[], int n_processes, int quantum) {
	// Array de bursts times //
	int remaind_time[n_processes];
	// Inicializa um array de burst times //
	for (int i = 0; i < n_processes; i++) {
		remaind_time[i] = processes[i].burst_time;
	}
	// Tempo total de um processo no escalonador //
	int turn_time[n_processes];
	// Tempo de espera para cada process //
	int wait_time[n_processes];
	// Tempo de vida de cada process //
	int tat[n_processes];
	// Resultado total de algumas métricas //
	float total_wt, total_tat = 0;

	rr_waitingtime(processes, n_processes, remaind_time, wait_time, turn_time, quantum);
	rr_turnaroundtime(processes, n_processes, wait_time, tat, turn_time);

	for (int i = 0; i < n_processes; i++) {
		total_wt += wait_time[i];
		total_tat += tat[i];
	}
	printf("PID\t Burst Time\tWait Time\tTurn Around Time\n");
	for (int i = 0; i < n_processes; i++) {
		printf("%d  \t  %d   \t\t%d \t\t\t %d\n", processes[i].proc_id, processes[i].burst_time,
			       	wait_time[i], tat[i]);
	}
	printf("\x1b[33mAverage waiting time: %.3f \n\x1b[31mAverage turn around time: %.3f\x1b[0m\n",
			total_wt/(float)n_processes, total_tat/(float)n_processes);

}


int rr_turnaroundtime(Process processes[], int n_processes, int wait_time[], int tat[], int turn_time[]) {
	/*Realiza o cálculo do turnAT tendo como parâmetro o tempo total de cada
	* processo e o tempo de chegado do processo
	*/
	for (int i = 0; i < n_processes; i++) {
		tat[i] = turn_time[i];
	}
	return 0;
}

int rr_waitingtime(Process processes[], int n_processes, int remaind_time[], int wait_time[], int turn_time[], int quantum) {
	// Variável contadora e uma variável sentinela //
	int i, done_condition;
	// Número de processos no escalonador //
	int buffer_process = n_processes;
	// Tempo total para execução de todos os processos //
	int total_time;

	for (total_time = 0, i = 0; buffer_process != 0; ) {
		/* Se o tempo restante de execução é menor que que o TIME_SLICE
		* então o processo será finalizado nesse ciclo
		*/
		if ( remaind_time[i] <= quantum && remaind_time[i] > 0 ) {
			total_time += remaind_time[i];
			remaind_time[i] = 0;
			done_condition = 1;
		// Senão tempo restante é decrementado em um TIME_SLICE //
		} else if ( remaind_time[i] > 0 ) {
			remaind_time[i] -= quantum;
			total_time += quantum;
		}
		// Verifica se o processo foi finalizado //
		if ( remaind_time[i] == 0 && done_condition == 1 ) {
			buffer_process--;
			turn_time[i] = total_time;
			wait_time[i] = total_time - processes[i].burst_time;
			done_condition = 0;
		}

		// Se i é igual ao número de processos-1, então o ciclo de exucução finaliza //
		if ( i == n_processes - 1) {
			i = 0;
		// Se o tempo total for maior que zero, o processo processo é escalonado //
		} else if ( total_time >= 0 ) {
			i++;
		} else {
			i = 0;
		}
	}

	return 0;
}
