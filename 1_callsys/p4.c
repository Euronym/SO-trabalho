#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>
#include <shadow.h>

#define MAX_LEN 200

// Realiza a escrita da hash gerada no arquivo /etc/shadow //
void write_hash(char *, char * );

int main(int argc, char **argv) {
	
	if ( argc < 2) {
		printf("Não foi informado um usuário, tente novamente\n");
		exit(EXIT_FAILURE);
	}

	char *salt, *encrypt, *password, *confirm_pass;
	password = malloc(MAX_LEN);
	confirm_pass = malloc(MAX_LEN);
	// Solicita a nova senha //
	printf("Digite a nova senha: ");
	if (fgets(password, MAX_LEN, stdin) == NULL)
		exit(EXIT_FAILURE);
	// Solicita a confirmação da nova senha //
	printf("Digite novamente para confirmar: ");
	if (fgets(confirm_pass, MAX_LEN, stdin) == NULL)
		exit(EXIT_FAILURE);
	// Verifica se as senhas digitas são diferentes //
	if (strcmp(password, confirm_pass) != 0) {
		printf("\x1b[31mSenhas diferentes, o processo será finalizado\n");
		exit(1);
	// Se iguais inicia a geração da hash //
	} else {
		salt = crypt_gensalt("$6$", 8, NULL, 0); // Gera o sal da hash
		encrypt = crypt(password, salt); // Gera a hash a partir da senha e o sal //
		write_hash(encrypt, argv[1]);	// Escreve a hash em /etc/shadow
	}
}

void write_hash(char *encrypted, char *argv) {
	struct spwd password_info;
	FILE *shadow;

	// Aloca um espaço na memória para a struct que conterá as informações do usuário //
	memset(&password_info, 0, sizeof(password_info));

	// Informações relacionadas a senha //
	password_info.sp_namp = argv; // nome do usuário //
	password_info.sp_lstchg = 18730; // Dada da última modificação //
	password_info.sp_pwdp = encrypted; // hash da senha //
	password_info.sp_max = 99999; // Num. máximo de dias para troca de senhas // 
	password_info.sp_min = 0;  // Num. minímo de dias para troca de senhas //
	password_info.sp_warn = 7; // Dias antes do aviso de expiração //
	password_info.sp_expire = -1; // dias para expiração da senha //
	password_info.sp_inact = -1; // dias para inatividade de uma senha //
	password_info.sp_flag = -1; // Reservado para uso futuro //

	// Comando que realiza a remoção da antiga hash do usuário //
	char comand[200] = "sed -i \'s/";
	strcat(comand, password_info.sp_namp);
	strcat(comand, ".*//g ; /^$/d\' /etc/shadow");
	system(comand);

	// Tentativa para a leitura do arquivo shadow //
	if ( (shadow = fopen("/etc/shadow", "a+")) == NULL ) {
		printf("Não foi possível abrir o arquivo\n");
		exit(1);
	}

	// Escrita das novas informações no arquivo /etc/shadow  //
	putspent(&password_info, shadow);
	fclose(shadow);
	printf("\x1b[32mSenha modificada com sucesso\n");
}
