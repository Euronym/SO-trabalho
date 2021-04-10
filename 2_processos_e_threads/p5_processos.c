#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER 9

void mostrar_vetor(int []);
void bubble_sort(int []);

int main(int argc, char *argv[], char *envp[]) {
    int fd[2]; // file descriptor para o pipe //
    int pid;
   
    if (pipe(fd) < 0) {
        perror("erro ");
        exit(0);
    } 

    pid = fork();
    if ( pid < 0 ) { 
        perror("erro: ");
        exit(0);
    } else {
        if ( pid > 0 ) {
           // É necessário escrever o vetor no pipe, então é fechado a leitura //
            close(fd[0]); 
            int numeros[BUFFER] = {3, 1, 0, 19, 9, 4, 8, 13, 7}; // Vetor que integra o processo pai //
            // Escreve o vetor no pipe //
            write(fd[1], numeros, sizeof(numeros)); 
            exit(0);
        } else {
            // Vetor a ser ordenando //
            int numeros_filho[BUFFER]; 
            // É necessário ler o pipe, então a escrita é fechada //
            close(fd[1]);            
           // ler o vetor que foi escrito no pipe //
            read(fd[0], numeros_filho, sizeof(numeros_filho)); 
            // Ordena os elementos do vetor //
            bubble_sort(numeros_filho);  
        }
    }
    printf("\nG00dBye Fr1end\n");
    exit(0);
}

/*
*   Implementação da ordenação utilizando Bubble-sort //
*/
void bubble_sort(int numeros[]) {
    int aux;
    for (int i = 0; i < BUFFER-1; i++) {
       for (int j = 0; j < BUFFER-1; j++) {
            if (numeros[j] > numeros[j+1]) {
               aux =  numeros[j];
               numeros[j] = numeros[j+1];
               numeros[j+1] = aux;
            }
        } 
    }
    mostrar_vetor(numeros);
}

/*
* Mostra na saída padrão os elementos ordenados do vetor
*/
void mostrar_vetor(int numeros[]) {
    for (int i = 0; i < BUFFER; i++) {
        if ( i != 0 && i % 3 == 0 ) printf("\n");
        printf("[%d] = %d ", i, numeros[i]);
    }
    printf("\n");
}
  
