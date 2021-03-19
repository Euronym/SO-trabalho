#include <stdlib.h>

#include <sys/types.h>	//biblioteca necessária para o uso de dirent.h
#include <time.h> // biblioteca para formatação da data.
#include <langinfo.h>//biblioteca para formatação da data.
#include <limits.h> // especifica a macro para leitura de caminho.
#include <unistd.h> // biblioteca que inclui algumas chamadas de sistema.
#include <sys/stat.h> // inclui a biblioteca necessária para os horários.
#include <dirent.h> // inclui a biblioteca necessária para leitura.

int main(int argc, char *argv[])//parâmetros para leitura de terminal.
{
	struct dirent *sd;
	struct stat buf;//cria a estrutura necessária para os horários.
	struct tm *tm;//cria a estrutura necessária para exibir os horários.
	DIR *dir; // cria um tipo especifico para armazenar o diretorio.
	char data[256]; // string para armazenar o horário.
	char dirAtual[PATH_MAX];
	//abre o diretório atual e o passa como  parâmetro para dir
	dir = opendir(getcwd(dirAtual, sizeof(dirAtual)));     
	if(dir == NULL)
	{
		printf("Não foi possível abrir o diretório.\n");
		exit(1);//encerra o programa se não for possível abrir.
	}
	int cont = 0;
	while((sd=readdir(dir)) != NULL)
	{
		/* realiza a leitura do diretório até o último arquivo.
		   "d_name" representa o nome da entrada que está sendo 
		   acessada no diretório, começando do primeiro arquivo
		   até o último.
		*/
		cont++;
		printf("Arquivo %d: %s\n", cont,sd->d_name);
		stat(sd->d_name,&buf);//obtém os dados do arquivo.
		tm = localtime(&buf.st_atime);//obtém a data do arquivo.
		//formata a data do arquivo.
		strftime(data, sizeof(data),nl_langinfo(D_T_FMT),tm);
		printf("Último acesso: %s\n", data); // exibe a string.
		
	}
	closedir(dir); // fecha o diretório ao final do programa.
	
	return 0;
}
