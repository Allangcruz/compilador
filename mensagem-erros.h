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
	
	removerQuebraLinha(palavra);
	
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
			printf("7 - Erro => A variavel (%s) não foi declarada porque precisa de tipo. [linha - %d].\n", palavra, nuLinha);
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

		case 11:
			printf("11 - Erro => A linha é uma declaração de variavel e a mesma deve conter ';' no final da linha (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 12:
			printf("12 - Erro => A memória usada foi de %d bytes, ultrapassando o limite de %d bytes de memória.\n", TOTAL_CONSUMO_MEMORIA, MAX_TOTAL_CONSUMO_MEMORIA);
		break;
		
		case 13:
			printf("13 - Erro => Uma variavel com o nome (%s) já foi declarada. [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 14:
			printf("14 - Erro => A declaração de variaveis do tipo inteiro, não requer tamanho (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 15:
			printf("15 - Erro => Declaração incorreta de variavel (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 16:
			printf("16 - Erro => Linha que possui comando 'leia' não pode ter declaração de variavel (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 17:
			printf("17 - Erro => Há ausência do caracter '(' ou ')', (%s). [linha - %d].\n", palavra, nuLinha);
		break;
		
		case 18:
			printf("18 - Erro => A linha não finalizou com ';' em (%s), favor verificar. [linha - %d].\n", palavra, nuLinha);
		break;
		
		default:
			printf("Foi selecionando um tipo de erro não definido no case.\n");
		break;
	}
	exit(1);
}

/**
 * Remove a quebra de linha da palavra informada
 *
 * @param char * palavra
 */
void removerQuebraLinha(char* palavra) {
	int i, valorAscii, count = 0;
	char palavraAux[UCHAR_MAX];
	
	limparLixoVetor(palavraAux);
	
	for (i = 0; i < strlen(palavra); i++) {
		valorAscii = (int) palavra[i]; 
		
		if (valorAscii != 10) {
			palavraAux[count] = palavra[i];
			count++;
		}
	}
	
	strcpy(palavra, palavraAux);
}

/**
 * Conta a quantidade de memoria consumida, incrementado e subtraindo da constante TOTAL_CONSUMO_MEMORIA
 *
 * http://www.cprogressivo.net/2013/03/A-funcao-sizeof-e-blocos-vizinhos-de-memoria-em-C.html
 *
 * @param int memoria
 * @param int situacao: 1 - incrementa, 2 - subtrai
 */
void memoriaConsumida(int memoria, int situacao) {
	char a[1] = "a";
	if (situacao == 1) {
		TOTAL_CONSUMO_MEMORIA = TOTAL_CONSUMO_MEMORIA + memoria;	
	} else {
		TOTAL_CONSUMO_MEMORIA = TOTAL_CONSUMO_MEMORIA - memoria;
	}
	
	if (TOTAL_CONSUMO_MEMORIA > MAX_TOTAL_CONSUMO_MEMORIA) {
		error(0, 12, a);
	}
}

