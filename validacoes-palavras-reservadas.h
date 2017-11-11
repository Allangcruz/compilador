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
void analiseLexica(Lista* lista) {
	validarAberturaFechamentoPrograma(lista);

	if (lista == NULL) {
        return false;
    }
    
    Elem* no = *lista;
    int i, nuLinha = 1;
    int count = 0;
    int valorAscii;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX];
    
	limparLixoVetor(palavraAux);
    limparLixoVetor(conteudoLinha);
    limparLixoVetor(palavraAuxVariavel);
    
    while (no != NULL) {
		strcpy(conteudoLinha, no->dados.conteudo);
		

		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i]; 
			
			// condicoes de parada para a analizar [espaco, ponto e virgula, (, \0]
			if ((valorAscii != 32) && (valorAscii != 59) && (valorAscii != 40) && (valorAscii != 10)) {
				//puts(palavraAux);
				palavraAux[count] = (char) valorAscii;
				count++;
			} else {
				bool isVariavel = validarDeclaracaoVariaveis(palavraAux);
				bool isPalavraReservada = 0;
				
				// exit(1);
				// validar a palavra reservada ou como variavel, se ele nao variavel, verificar se é palavra reservada
				if (!isVariavel) {
					isPalavraReservada = validarPalavrasReservadas(isPalavraReservada);
				}
				
				
				
				limparLixoVetor(palavraAux);
				count=0;
			}
		}
		
		no = no->prox;
    }
	
	// validarPalavrasReservadas(lista);
	// validarDeclaracaoVariaveis(lista);
	// validar tipo ...
}


/**
 * Valida palavras reservadas, utilizar como boleando, apos passar a palavra. validar separadamente.
 */
int validarPalavrasReservadas(char* palavra) {
	int retorno = 0;
	
	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		if (strcasecmp(palavra, palavrasReservadas[i]) != 0) {
			//error(nuLinha, 3, palavraAux);
		}		
		
	}
	
	return retorno;
}

/**
 * Valida palavras duplo balanceamento
 */
void validarDuploBalanceamento() {	
} 

/**
 * Valida declaracoes de variaveis.
 */
int validarDeclaracaoVariaveis(char *palavra) {
	int teste = 0;
	
	if ((int) palavra[0] == 35 && (int) palavra[1] >= 97 &&  (int) palavra[1] <= 122) {
		teste = 1;
	}
	
	return teste;
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
        exit(1);
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
		
		if (valorAscii != 10) {
			palavraAux[count] = (char) valorAscii;
			count++;
		} 
	}
	
	if (strcasecmp(palavraAux, palavrasReservadas[0]) != 0) {
		error(nuLinha, 2, palavraAux);
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
		
		if (valorAscii != 10) {
			palavraAux[count] = (char) valorAscii;
			count++;
		}
	}

	if (strcasecmp(palavraAux, palavrasReservadas[9]) != 0) {
		error(nuLinha, 3, palavraAux);
	}
}
 
