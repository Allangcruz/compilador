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
			printf("1 - Erro => Deve possuir a palavra reserva 'programa' no inicio, foi encontrado: (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 2:
			printf("2 - Erro => Deve possuir a palavra reserva 'fim' no fechamento, foi encontrado: (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 3:
			printf("3 - Erro => A palavra (%s) não é uma variavel valida. [linha - %d].\n", palavra, nuLinha);
		break;

		case 4:
			printf("4 - Erro => A palavra (%s) não é palavra reserva. [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 5:
			printf("5 - Erro => A palavra (%s) não é uma palavra reservada e nem variavel, não consta no escopo. [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 6:
			printf("6 - Erro => A variavel informada (%s) esta invalida. [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 7:
			printf("7 - Erro => A variavel (%s) não está declara. [linha - %d].\n", palavra, nuLinha);
		break;	
		
		case 8:
			printf("8 - Erro => É obrigatorio um valor de tamanho para variavel, (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 9:
			printf("9 - Erro => Há ausência do caracter '[' ou ']', (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 10:
			printf("10 - Erro => O '%c' precisa ter duplo balanceamento, (%s). [linha - %d].\n", (char) 34, palavra, nuLinha);
		break;

		
		default:
			// TODO definir .... ou remover caso nao seja necessario
		break;
	}
	exit(1);
}
