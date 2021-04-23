#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>
#include <shadow.h>

#define MAX_LEN 200

// XXX Não é recomendado ainda a execução do binário
// código em desenvolvimento

void to_hash(char *, char *);

int main(int argc, char **argv) {
	char *salt, *password, *encrypt, *confirm_pass;
	size_t len;
	
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
	} else {
		salt = crypt_gensalt("$6$", 15, NULL, 0);
		encrypt = crypt(password, salt);
		to_hash(encrypt, argv[1]);
	}
}

void to_hash(char *encrypted, char argv[]) {
	struct spwd *password_info;
	
	password_info = malloc(1024 * sizeof(char));
	password_info = getspnam(argv);
	password_info.sp_pwdp = encrypted;	
}


