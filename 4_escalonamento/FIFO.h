#include <stdio.h>

// Function to find the waiting time for all processes
int waitingtime(Process processes[], int n, int wait_time[]) {
   // waiting time for first process is 0
   wait_time[0] = 0;
   // calculating waiting time
   for (int i = 1; i < n ; i++ )
   wait_time[i] = processes[i - 1].burst_time + wait_time[i-1] ;
   return 0;
}
// Function to calculate turn around time
int turnaroundtime(Process processes[], int n, int wait_time[], int tat[]) {
   // calculating turnaround time by adding
   // burst_time[i] + wait_time[i]
   int i;
   for ( i = 0; i < n ; i++)
   tat[i] = processes[i].burst_time + wait_time[i];
   return 0;
}
//Function to calculate average time
int avgtime(Process processes[], int n) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   int i;
   //Function to find waiting time of all processes
   waitingtime(processes, n , wait_time);
   //Function to find turn around time for all processes
   turnaroundtime(processes, n, wait_time, tat);
   //Display processes along with all details
   printf("Processes  Burst   Waiting Turn around \n");
   // Calculate total waiting time and total turn
   // around time
   for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t  %d\t\t %d \t%d\n", i+1, processes[i].burst_time, wait_time[i], tat[i]);
   }
   printf("Average waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);
   return 0;
}
