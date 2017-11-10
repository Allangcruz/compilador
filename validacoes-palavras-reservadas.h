/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
=================================================================================================================================
	Validações:
	1 - O arquivo começa com a palavra reservada "programa" e termina com a palavra reservada "fim".
	2 - As palavras reservadas validas são apenas as que estão definidas na variavel global "palavrasReservadas", case sensitive.
==================================================================================================================================
*/

/**
 * Aplica validacoes referente a analise lexica.
 */
void analiseLexica() {
	validarAberturaFechamentoPrograma();
}


/**
 * Valida palavras reservadas, utilizar como boleando, apos passar a palavra. validar separadamente.
 */
void validarPalavrasReservadas() {
	
}

/**
 * Valida palavras duplo balanceamento
 */
void validarDuploBalanceamento() {
	
} 

/**
 * Valida declaracoes de variaveis.
 */
void validarDeclaracaoVariaveis() {
	
}

/**
 * Limpa o lixo contido no vetor.
 *
 * @param char vetor
 */
void limparLixoVetor(char vetor[]) {
	int i = 0;

	while (i < UCHAR_MAX) {
		vetor[i] = '\0';
		i ++;
	}
}

/**
 * Valida se o programa inicializa com a palavra reservada 'programa' e finaliza com a palavra reservada 'fim'.
 *
 * @param Lista* lista 
 */
void validarAberturaFechamentoPrograma(Lista* lista) {
	if (lista == NULL) {
        return;
    }

    Elem* no = *lista;
    char inicio[UCHAR_MAX];
    char final[UCHAR_MAX];
    
    strcpy(inicio, no->dados.conteudo);
    int i;
    int nuLinha = no->dados.linha;
    int count = 0;
    int valorAscii;
    char palavraAux[UCHAR_MAX];
    
    limparLixoVetor(palavraAux);
    
    for (i = 0; i < strlen(inicio); i++) {
		valorAscii = (int) inicio[i]; 
		
		// desconsiderar palavras Maiusculas, alguns caracteres desnecessarios
		if ((valorAscii >= 97 && valorAscii <= 122) || (valorAscii >= 48 && valorAscii <= 57)) {
			palavraAux[count] = (char) valorAscii;
			count++;
		}
		// printf("%c - %i - %s \n", inicio[i], valorAscii, palavraAux);
	}
	
	if (strcasecmp(palavraAux, palavrasReservadas[0]) != 0) {
		error(nuLinha, 2);
	}
	
	// valida a palavra fim na ultima linha 
	limparLixoVetor(palavraAux);
	count = 0;

	while (no != NULL) {
		if (no->prox == NULL) {
			strcpy(final, no->dados.conteudo);		
			nuLinha = no->dados.linha;
		}
        no = no->prox;
    }

    for (i = 0; i < strlen(inicio); i++) {
		valorAscii = (int) final[i]; 
		
		// desconsiderar palavras Maiusculas, alguns caracteres desnecessarios
		if (valorAscii >= 97 && valorAscii <= 122) {
			palavraAux[count] = (char) valorAscii;
			count++;
		}
		// printf("%c - %i - %s \n", final[i], valorAscii, palavraAux);
	}

	if (strcasecmp(palavraAux, palavrasReservadas[9]) != 0) {
		error(nuLinha, 3);
	}

	// printf("%s", inicio);
    // delimitadores com condição de paradas, ponto e virgula
    // programa allan teste
}
 
