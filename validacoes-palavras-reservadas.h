/**
Alunos:
Allan Gon�alves da Cruz
Elson Bento dos Santos
=================================================================================================================================
	Valida��es:
	1 - O arquivo come�a com a palavra reservada "programa" e termina com a palavra reservada "fim".
	2 - As palavras reservadas validas s�o apenas as que est�o definidas na variavel global "palavrasReservadas", case sensitive.
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
    int i, valorAscii, nuLinha = 1, count = 0;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX];
    bool isVariavel = 0, isPalavraReservada = 0;
    
	limparLixoVetor(palavraAux);
    limparLixoVetor(conteudoLinha);
    limparLixoVetor(palavraAuxVariavel);
    
    while (no != NULL) {
		strcpy(conteudoLinha, no->dados.conteudo);
		
		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i]; 
			
			// condicoes de parada para a analizar [\0, espaco, (, ), virgula, ponto e virgula]
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 40) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59)) {
				palavraAux[count] = (char) valorAscii;
				count++;
			} else {
				isVariavel = validarDeclaracaoVariaveis(palavraAux);
				
				// validar a palavra reservada ou como variavel, se ele nao variavel, verificar se � palavra reservada
				if (! isVariavel) {
					// imprime apenas as palavras reservadas
					printf("[%d] - possivel palavra reservada => %s\n", nuLinha, palavraAux);
					isPalavraReservada = validarPalavrasReservadas(palavraAux);
					
					if (isPalavraReservada) {
						// imprime apenas as varaiveis encontradas
						printf("[%d] - possivel variavel => %s\n", nuLinha, palavraAux);
					}
				} else {
					// compara se � uma variavel e se � uma palavra reservada
					if (isVariavel == false && isPalavraReservada == false) {
						printf("(%d) - Nao e variavel e nem uma palavra reservada\n", nuLinha);
					}
				}
				
				
				limparLixoVetor(palavraAux);
				count=0;
			}
		}
		
		no = no->prox;
		nuLinha++;
    }
	
	// validar tipo ...
}

/**
 * Valida palavras reservadas, utilizar como boleando, apos passar a palavra. validar separadamente.
 *
 * @param char* palavra
 * @return int isValido
 */
int validarPalavrasReservadas(char* palavra) {
	int isValido = 1, i;

	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		if (strcasecmp(palavra, palavrasReservadas[i]) != 0) {
			isValido = 0;
			break;
		}		
		
	}
	
	return isValido;
}

/**
 * Valida declaracoes de variaveis.
 *
 * @param char *palavra
 */
int validarDeclaracaoVariaveis(char *palavra) {
	int isValido = 0;
	
	if ((int) palavra[0] == 35 && (int) palavra[1] >= 97 &&  (int) palavra[1] <= 122) {
		isValido = 1;
	}
	
	return isValido;
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
 * Valida palavras duplo balanceamento
 */
void validarDuploBalanceamento() {	
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
		error(nuLinha, 1, palavraAux);
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
		error(nuLinha, 2, palavraAux);
	}
}
 
