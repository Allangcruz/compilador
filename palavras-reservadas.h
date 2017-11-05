/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
*/

/**
 * Constante com o total de palavras reservadas.
 */
#define NU_PALAVRA_RESERVADAS 10 

/**
 * Vetor com palavras reservadas.
 */
char palavrasReservadas[NU_PALAVRA_RESERVADAS][9] = {"programa", "leia", "escreva", "se", "senao", "para", "inteiro", "caractere", "real", "fim" };
 
/**
 * Imprime o vetor com todas as palavras reservadas
 */
void imprimirPalavrasReservadas() {
	int i = 0;
	
	printf("\n--------------------------------------------\n");
	printf("PALAVRAS RESERVADAS\n\n");
	 
	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		printf("%iº => %s \n",i ,palavrasReservadas[i]);
	}

	printf("\nFIM PALAVRAS RESERVADAS");
	printf("\n--------------------------------------------\n");
} 

