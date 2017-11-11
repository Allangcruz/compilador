/**
Alunos:
Allan Gon�alves da Cruz
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
		case 0: 
			printf("Erro: � necessario iniciar com a palavra reservada 'programa'.\n");
		break;
		
		case 1:
			printf("Erro: � necessario finalizar com a palavra reservada 'fim'.\n");
		break;
		
		case 2:
			printf("O sistema deve possuir a palavra reserva 'programa' no inicio (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 3:
			printf("O sistema deve possuir a palavra reserva 'fim' no fechamento (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		default:
			// TODO definir .... ou remover caso nao seja necessario
		break;
	}
	exit(1);
}