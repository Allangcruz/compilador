/**
 * Vetor com palavras reservadas.
 */
char palavrasReservadas[NU_PALAVRA_RESERVADAS][10] = {"programa", "leia", "escreva", "se", "senao", "para", "inteiro", "caractere", "real", "fim"};

/**
 * Vetor com palavras reservadas para tipo de variaveis.
 */
char tiposVariaveis[NU_TIPO_VARIAVEL][10] = {"inteiro", "caractere", "real"};

/**
 * Imprime o vetor com todas as palavras reservadas
 */
void imprimirPalavrasReservadas() {
	int i;
	memoriaConsumida(sizeof(i), 1);
	
	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		printf("%iº => %s \n",i ,palavrasReservadas[i]);
	}
}

/**
 * Imprime o vetor com todas as palavras reservadas
 */
void imprimirTiposVariaveis() {
	int i;
	memoriaConsumida(sizeof(i), 1);
	
	for (i = 0; i < NU_TIPO_VARIAVEL; i++) {
		printf("%iº => %s \n",i ,tiposVariaveis[i]);
	}
}

