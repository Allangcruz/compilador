/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
*/

/**
 * Exibe o erro encontra ao validar as linhas do arquivo.
 * 
 * @param int nuLinha
 * @param int tipoErro
 */
void error(int nuLinha, int tipoErro, char *palavra) {
	switch(tipoErro) {
		case 1:
			printf("1 - Erro => Programa deve possuir a palavra reserva 'programa' no inicio (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 2:
			printf("2 - Erro => Programa deve possuir a palavra reserva 'fim' no fechamento (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 3:
			printf("3 - Erro => A palavra (%s) não é uma variavel valida. [linha - %d].\n", palavra, nuLinha);
		break;

		case 4:
			printf("4 - Erro => A palavra (%s) não é palavra reserva. [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 5:
			printf("5 - Erro => A palavra (%s) não é uma palavra reserva e nem variavel, não consta no escopo. [linha - %d].\n", palavra, nuLinha);
		break;
		
		default:
			// TODO definir .... ou remover caso nao seja necessario
		break;
	}
	exit(1);
}
