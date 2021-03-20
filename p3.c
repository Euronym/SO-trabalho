#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h> // biblioteca para concatenação de arquivos.
#include <dirent.h>


int main(int argc, char *argv[])//parâmetros para leitura de linha.
{
	struct dirent *sd;
	DIR *diretorio;
	char dirAtual[PATH_MAX];
	// abre o diretório atual e o passa para diretório.
	diretorio = opendir(getcwd(dirAtual, sizeof(dirAtual)));     
	if(diretorio == NULL){
	// verifica se o diretório buscado não é vazio.
		printf("Não foi possível realizar a leitura.");
		exit(1);
	}
	int cont = 0;
	while( (sd=readdir(diretorio)) != NULL)
	{	
		cont++;
		/*
			acrescenta L ao final de cada arquivo dentro do 				diretório, utilizando para isso a função 				rename que recebe como parâmetros o antigo nome do 				arquivo e substitui pela concatenação do 
			arquivo com o char "L".	
		*/
		int teste = rename(sd->d_name, strcat(sd->d_name, "L"));
		printf("Novo nome de arquivo[%d]: %s\n", cont,sd->d_name);
		printf("%d\n",teste);
	}	
	closedir(diretorio);// fecha o diretório ao final do programa.
	return 0;
}
