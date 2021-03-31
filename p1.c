#include <stdio.h> //biblioteca que contém várias funções de entrada e saída.
#include <fcntl.h> //biblioteca que contém funções para controle de arquivos. (ex: open())

/*
    Programa que concatena dois arquivos. 
    Entrada: o nome dos dois arquivos. 
    Saída: o arquivo concatenado
*/

void concatenar (FILE *destino,FILE *origem) //função que recebe o endereço de dois arquivos
{
    char leitor [1000]; 
    //variável para auxiliar na escrita de dados do arquivo origem ao arquivo destino

    while (fgets (leitor, sizeof leitor, origem) != NULL) 
    //lê o arquivo origem e coloca os dados no leitor
    {
        fputs (leitor, destino);
        //coloca os dados do leitor no arquivo destino
    }
}

void main(){
    FILE *arquivo1; //definindo as variáveis que irão guardar os endereços dos arquivos
    FILE *arquivo2;
    FILE *arquivo3;
    char nome_arq1[300], nome_arq2[300]; 
    //var. que irão guardar os nomes dos arquivos que serão concatenados

    printf("Digite o nome do arquivo 1: "); //exibe mensagem na tela
    scanf("%s", &nome_arq1); //pega o que foi digitado e guarda na variável nome_arq1

    printf("Digite o nome do arquivo 2: ");
    scanf("%s", &nome_arq2);

    arquivo1 = fopen(nome_arq1, "r"); 
    /*
    função que retorna o endereço do arquivo de nome nome_arq1
    e guarda em arquivo1. Além disso, define que será 
    um arquivo para leitura: "r" de read
    */
    arquivo2 = fopen(nome_arq2, "r");
    arquivo3 = fopen("concatenado.txt", "a");
    /*
    função que retorna o endereço do arquivo de nome concatenado.txt
    e guarda em arquivo3, mas ,como não existirá previamente(definido no comando do problema),
    um arquivo será criado com esse nome. Além disso, define que será um arquivo para escrita
    em que o ponteiro se posicionará no final do arquivo para não sobrescrever os dados escritos, 
    mas concantená-los:
    "a" de append
    */

    concatenar(arquivo3, arquivo1); //chama a função concatenar
    concatenar(arquivo3, arquivo2);
    printf("O arquivo concatenado.txt foi criado ao concatenar os arquivos %s e %s\n",nome_arq1,nome_arq2);

    //Fechando os arquivos
    fclose (arquivo1);
    fclose (arquivo2);
    fclose (arquivo3);
}