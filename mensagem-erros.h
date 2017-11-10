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
void error(int nuLinha, int tipoErro) {
	switch(tipoErro) {
		case 0: 
			printf("Erro: é necessario iniciar com a palavra reservada 'programa'.\n");
		break;
		
		case 1:
			printf("Erro: é necessario finalizar com a palavra reservada 'fim'.\n");
		break;
		
		case 2:
			printf("O sistema deve possuir a palavra reserva 'programa' no inicio. [linha - %d].\n", nuLinha);
		break;
		
		case 3:
			printf("O sistema deve possuir a palavra reserva 'fim' no fechamento. [linha - %d].\n", nuLinha);
		break;
		
		default:
			// TODO definir .... ou remover caso nao seja necessario
		break;
	}
}
