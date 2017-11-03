
/**
 * Constante com o total de palavras reservadas.
 */
int NU_PALAVRA_RESERVADAS = 10;

/**
 * Vetor com palavras reservadas.
 */
char palavrasReservadas[10][9] = {"programa", "leia", "escreva", "se", "senao", "para", "inteiro", "caractere", "real", "fim" };
 
/**
 * Imprime o vetor com todas as palavras reservadas
 */
void imprimirPalavrasReservadas() {
	int i = 0;
	
	printf("\n--------------------------------------------\n");
	printf("PALAVRAS RESERVADAS\n\n");
	 
	for (i = 0; i < 10; i++) {
		printf("%iº => %s \n",i ,palavrasReservadas[i]);
	}

	printf("\nFIM PALAVRAS RESERVADAS");
	printf("\n--------------------------------------------\n");
} 

