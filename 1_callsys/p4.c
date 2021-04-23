#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>
#include <shadow.h>

#define MAX_LEN 200
// Procedimento que realiza a criptografia das senhas //

void write_hash(char *);

int main() {
	
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
	if (*password != *confirm_pass) {
		printf("\x1b[31mSenhas diferentes, o processo será finalizado\n");
		exit(1);
	} else {
		salt = crypt_gensalt("$6$", 15, NULL, 0);
		encrypt = crypt(password, salt);
		write_hash(encrypt);
	}

void write_hash(char *hash) {


}
