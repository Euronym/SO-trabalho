#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "FIFO.h"
#include "sjf.h"
#include "sorteio.h"

// define como 10 o número máximo de processos que podem existir.
#define MAX_PROCESSES 10
#define TRUE 1

// main function
int main(int argc, char * argv[])
{
    // armazena o número de processos informado pelo usuário.
    int n_processes;
    // ponteiro do tipo Process.
    Process *processes = NULL;
    do
    {
        printf("\rDigite o número inteiro de processos no sistema(ou 0 para finalizar):");
        //coleta o número de processos do usuário.
        scanf("%d", &n_processes);
        // verifica se o número de processos a ser alocado excede a capacidade máxima.
        if(n_processes > MAX_PROCESSES)
        {
            printf("O número de processos informado excedeu a capacidade permitida, "
            "digite um número menor ou igual à 10.\n");
        }
        // verifica se o número de processos informado é válido.
        else if(n_processes < 0)
        {
            printf("O número digitado é inválido, tente novamente.\n");
        }
        else if(n_processes == 0)
        {
            printf("Obrigado\n");
            return 0;
        }
        // caso tudo esteja ok, é possível prosseguir no código.
        else
        {
            int burst_time;
            // aloca dinamicamente a memória necessária para os processos informados.
            processes = malloc(n_processes * sizeof(double));
            printf("Abaixo, digite o tempo de execução(burst) para cada processo.\n");
            for(int i = 0;i < n_processes; i++)
            {
                printf("\rprocesso[%d] = ", i);
                // verifica se o número informado é um inteiro.
                scanf("%d", &burst_time);
                // verifica a validade do número de burst informado.
                if(burst_time > 0)
                {
                    // define o PID automaticamente em ordem crescente.
                    processes[i].proc_id = i;
                    // verifica se o tempo de burst informado pelo usuário é válido e atribui ao processo.
                    processes[i].burst_time = burst_time;
                }
                // se o dado informado pelo usuário é inválido, uma outra iteração é possível.
                else
                {
                    printf("Tempo informado inválido, tente novamente.\n");
                    i--;
                }
            }
            int option = 1;
            // cria um menu exibindo as opções de escalonamento ofertadas pelo sistema.
            printf("Por fim, precisamos saber qual algoritmo você gostaria de simular.\n");
            do
            {
                printf("==========================================\n"
                "Shortest job first(SJB): digite 1\n"
                "First in first out(FIFO): digite 2\n"
                "Lottery scheduling: digite 3\n"
                "Round Robin: digite 4\n"
                "Sair: digite 0\n"
                "==========================================\n");
                scanf("%d", &option);
                switch(option)
                {
                    case 1:
                        sjf_avgtime(processes, n_processes);
                        break;
                    case 2:
                        fifo_avgtime(processes, n_processes);
                        break;
                    case 3:
                        lottery_avgtime(processes, n_processes);
                        break;
                    case 4:
                        break;
                    case 0:
                        printf("Obrigado!\n");
                        free(processes);
                        return 0;
                    default:
                        printf("Opção inválida, tente novamente.\n");
                }
            }while (option != 0);
        }
    }while(TRUE);

    return 0;
}
