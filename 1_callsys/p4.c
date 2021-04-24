#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>
#include <shadow.h>

#define MAX_LEN 200

// Realiza a escrita da hash gerada no arquivo /etc/shadow //
void write_hash(char *);

int main(int argc, char **argv) {
	
	char *salt, *encrypt, *password, *confirm_pass;
	password = malloc(MAX_LEN);
	confirm_pass = malloc(MAX_LEN);
	printf("Digite a nova senha: ");
	if (fgets(password, MAX_LEN, stdin) == NULL)
		exit(EXIT_FAILURE);
	printf("Digite novamente para confirmar: ");
	if (fgets(confirm_pass, MAX_LEN, stdin) == NULL)
		exit(EXIT_FAILURE);
	// Verifica se as senhas digitas são diferentes //
	if (strcmp(password, confirm_pass) != 0) {
		printf("\x1b[31mSenhas diferentes, o processo será finalizado\n");
		exit(1);
	// Se iguais inicia a geração da hash //
	} else {
		salt = crypt_gensalt("$6$", 0, NULL, 0); // Gera o sal da hash
		encrypt = crypt(password, salt); // Gera a hash a partir da senha e o sal //
		printf("%s", password);
		write_hash(encrypt);	// Escreve a hash em /etc/shadow
	}
}

void write_hash(char *encrypted) {
	struct spwd password_info;
	FILE *fake_shadow;

	memset(&password_info, 0, sizeof(password_info));

	// Informações relacionadas a senha //
	password_info.sp_namp = "claudio"; // nome do usuário //
	password_info.sp_lstchg = 18730; // Dada da última modificação //
	password_info.sp_pwdp = encrypted; // hash da senha //
	password_info.sp_max = 99999; 
	password_info.sp_min = 0;
	password_info.sp_warn = 7; // Dias antes do aviso de expiração //
	password_info.sp_expire = -1; // dias para expiração da senha //
	password_info.sp_inact = -1; // dias para inatividade de uma senha //
	password_info.sp_flag = -1; // Reservado para uso futuro //

	// Comando que realiza a remoção da antiga hash do usuário //
	char comand[200] = "sed -i \'s/";
	strcat(comand, password_info.sp_namp);
	strcat(comand, ".*//g ; /^$/d\' /etc/shadow");
	system(comand);

	if ( (fake_shadow = fopen("/etc/shadow", "a+")) == NULL ) {
		printf("Não foi possível abrir o arquivo\n");
		exit(1);
	}
	putspent(&password_info, fake_shadow);
	fclose(fake_shadow);
}
