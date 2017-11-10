/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
*/

/**
 * Vetor com palavras reservadas.
 */
char palavrasReservadas[NU_PALAVRA_RESERVADAS][9] = {"programa", "leia", "escreva", "se", "senao", "para", "inteiro", "caractere", "real", "fim" };
 
/**
 * Imprime o vetor com todas as palavras reservadas
 */
void imprimirPalavrasReservadas() {
	int i = 0;
	
	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		printf("%iº => %s \n",i ,palavrasReservadas[i]);
	}
} 

