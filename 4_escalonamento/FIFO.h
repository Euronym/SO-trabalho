#include <stdio.h>

// acha o tempo de espera de todos os processos.
int fifo_waitingtime(Process processes[], int n, int wait_time[]);
// função para calcular o tempo de resposta.
int fifo_turnaroundtime(Process processes[], int n, int wait_time[], int tat[]);
// função para calcular a média de tempo.
int fifo_avgtime(Process processes[], int n);

int fifo_waitingtime(Process processes[], int n, int wait_time[]) {
   // o primeiro processo não possui tempo de espera associado.
   wait_time[0] = 0;
   // calculating waiting time
   for(int i = 1; i < n ; i++)
   {
       wait_time[i] = processes[i - 1].burst_time + wait_time[i-1];
   }
   return 0;
}
int fifo_turnaroundtime(Process processes[], int n, int wait_time[], int tat[])
{
   // calcula o tempo de resposta somando o tempo de burst com o tempo de espera.
   // burst_time[i] + wait_time[i]
   for (int i = 0; i < n ; i++)
   {
       tat[i] = processes[i].burst_time + wait_time[i];
   }
   return 0;
}
int fifo_avgtime(Process processes[], int n)
{
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   //calcula o tempo de espera de todos os processos.
   fifo_waitingtime(processes, n , wait_time);
   //calcula o tempo de resposta de todos os processos.
   fifo_turnaroundtime(processes, n, wait_time, tat);
   //exibe as informações obtidas.
   printf("PID    Burst   Waiting   Turn around \n");
   //calcula o tempo total de espera e de resposta
   for (int i = 0; i < n;i++)
   {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t%d\t  %d\t\t%d\n", processes[i].proc_id, processes[i].burst_time, wait_time[i], tat[i]);
   }
   // exibe as médias dos tempos totais obtidos anteriormente.
   printf("\x1b[31mAverage wait time: %.3f\n\x1b[33mAverage turn around time: %.3f\x1b[0m\n",
   (float)total_wt / (float)n, (float)total_tat/(float)n);
   return 0;
}
