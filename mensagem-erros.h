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
			printf("Erro: é necessario iniciar com a palavra reservada 'programa'.");
		break;
		
		case 1:
			printf("Erro: é necessario finalizar com a palavra reservada 'fim'.");
		break;
		
		default:
			// TODO definir .... ou remover caso nao seja necessario
		break;
	}
}
