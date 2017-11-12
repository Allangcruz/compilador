/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
=================================================================================================================================
	Tabela ascii util para vazer comparaçoes pois comparar string nao estava sendo confiavel: 
	http://www.ricardoarrigoni.com.br/tabela-ascii-completa/
==================================================================================================================================
*/

/**
 * Aplica validacoes referente a analise lexica.
 */
void analiseLexica(Lista* lista, TabelaSimbolo* tabelaSimbolos) {
	validarAberturaFechamentoPrograma(lista);

	if (lista == NULL) {
        exit(1);
    }
    
    Elem* no = *lista;
    int i, valorAscii, nuLinha, count = 0;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX], tipoVariavel[UCHAR_MAX], tamanhoPalavra[UCHAR_MAX], auxTamanhoPalavra[UCHAR_MAX];
    bool isVariavel = false, isPalavraReservada = false, isCondicaoParada = false, isLinhaComVariavel = false;
    
    char valorTamanhoAllan[UCHAR_MAX], allan[UCHAR_MAX];
    
	limparLixoVetor(palavraAux);
    limparLixoVetor(tipoVariavel);
    limparLixoVetor(conteudoLinha);
    limparLixoVetor(tamanhoPalavra);
    limparLixoVetor(auxTamanhoPalavra);
    limparLixoVetor(palavraAuxVariavel);
    
    while (no != NULL) {
		strcpy(conteudoLinha, no->dados.conteudo);
		nuLinha = no->dados.linha;
		
		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i]; 
			
			// Verifica se a caracter ascii informado e uma condição de parada, para ser feita uma determinada analise.
			// As condiçoes de parada sao os caracterers : \0, espaco, (, ), virgula, ponto e virgula
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 40) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59)) {
				palavraAux[count] = (char) valorAscii;
				count++;
			} else {
				// TODO verificar se a variavel possui tamanho, caso sim, armazenar o tamanho
				// Remover tambem as chaves do tamanho pois estão invalidas
				isVariavel = validarDeclaracaoVariaveis(palavraAux);
				
				// verifica se não e uma variavel, se ele nao variavel, verificar se é palavra reservada
				if (! isVariavel) {
					isPalavraReservada = validarPalavrasReservadas(palavraAux);
					
					if (isPalavraReservada == true) {
						// quando for palavra reservada posso tratar aqui, exemplo se for tipo de variavel posso guarda para validar depois
						// caso se, senao, leia, escreva, para. preciso tratar cada um.
						
						if (isTipoVariavel(palavraAux) == 1) {
							strcpy(tipoVariavel, palavraAux);
							isLinhaComVariavel = true;
						}	
					}
				} else {
					if (isLinhaComVariavel == true) {
						// salva a variavel valida
	    				Simbolo novoSimbolo;
	    				
	    				// caso tenha tamanho recupera o tamanho e adiciona na tabela de simbolo
						getTamanhoVariavel(palavraAux, auxTamanhoPalavra);
						strcpy(tamanhoPalavra, auxTamanhoPalavra);
						strcpy(novoSimbolo.tamanho, tamanhoPalavra);
	    				
						removeTamanhoVariavel(palavraAux);
	    				strcpy(novoSimbolo.palavra, palavraAux);
	    				strcpy(novoSimbolo.tipo, tipoVariavel);
						
						insereFinalTabelaSimbolo(tabelaSimbolos, novoSimbolo);
						limparLixoVetor(auxTamanhoPalavra);
					}
				}
				
				// por causa que quando e encontrado 2 ou mais criterio de paradas seguidos ele estava comparando com a palavra vazia, e isso nao pode acontecer
				if (strlen(palavraAux) > 0) {
					// compara se é uma variavel e se é uma palavra reservada
					if (isVariavel == false && isPalavraReservada == false) {
						error(nuLinha, 5, palavraAux);
					}
				}
				
				limparLixoVetor(palavraAux);
				count=0;
				isVariavel = 0;
				isPalavraReservada = 0;
			}
		}
		
		no = no->prox;
		isLinhaComVariavel = false;
		limparLixoVetor(tipoVariavel);
    }
}

/**
 * Valida palavras reservadas, utilizar como boleando, apos passar a palavra. validar separadamente.
 *
 * @param char* palavra
 * @return int isValido
 */
int validarPalavrasReservadas(char* palavra) {
	int isValido = 0, i;

	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		if (strcmp(palavra, palavrasReservadas[i]) == 0) {
			isValido = 1;
			break;
		}		
	}
	
	return isValido;
}

/**
 * Valida declaracoes de variaveis.
 *
 * @param char *palavra
 * @param int nuLinha
 */
int validarDeclaracaoVariaveis(char *palavra, int nuLinha) {
	int isValido = 0, i, valorAscii;
	
	if ((int) palavra[0] == 35) {
		if ((int) palavra[1] >= 97 &&  (int) palavra[1] <= 122) {
			isValido = 1;
		} else {
			isValido = 0;
			error(nuLinha, 6, palavra);
		}
		
		for (i = 2; i < strlen(palavra); i++) {
			valorAscii = (int) palavra[i];
			
			// permiter apenas a-z, 0-9, A-Z, [, ]
			if (! ((valorAscii >= 97 && valorAscii <= 122) || (valorAscii >= 48 && valorAscii <= 57) || (valorAscii >= 65 && valorAscii <= 90) || valorAscii == 91 || valorAscii == 93)) {
				isValido = 0;
				error(nuLinha, 6, palavra);
			}
		}
	}
	
	return isValido;
}

/**
 * Verifica se a variavel informada possui tamanho, caso sim, retorna o tamanho.
 *
 * @param char palavra[]
 */
void getTamanhoVariavel(char palavra[], char retorno[]) {

	int i, tamanhoPalavra = strlen(palavra) - 1, valorAscii, count = 0;
	char valorTamanho[UCHAR_MAX], auxValorTamanho[UCHAR_MAX];
	
	limparLixoVetor(valorTamanho);
	limparLixoVetor(auxValorTamanho);
	
	// percorre a palavra de traz para frente
	for (i = tamanhoPalavra; i >= 0; i--) {
		valorAscii = palavra[i];
		// printf("(%d) - %c \n", i, palavra[i]);

		// verifica se o ultimo caracter é um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			continue;
		} else if((valorAscii >= 48 && valorAscii <= 57) && valorAscii != 91) { // condição que ira acumular enquanto for numero e nao encontrar [.
			auxValorTamanho[count] = palavra[i];
			// printf("=>=> (%d) - %c \n", i, palavra[i]);
			count++;
		} else if (valorAscii == 91) {
			break;
		}
	}
	
	count = 0;
	
	for (i = strlen(auxValorTamanho) - 1; i >= 0; i--) {
		valorTamanho[count] = auxValorTamanho[i];
		count++;
	}
	
	// por motivos que nao sei, criar uma funcao que retorna string esta dando erro
	// entao uma maneira de contornar tive que devolver o valor por referencia, infelizmente.
	strcpy(retorno, valorTamanho);
}

/**
 * Remove a string referente ao tamanho da variavel, [].
 *
 * @param char palavra[]
 */
void removeTamanhoVariavel(char palavra[]) {
	int i, tamanhoPalavra = strlen(palavra) - 1, valorAscii;
	
	// percorre a palavra de traz para frente
	for (i = tamanhoPalavra; i >= 0; i--) {
		valorAscii = palavra[i];

		// verifica se o ultimo caracter é um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			palavra[i] = '\0';
			continue;
		} else if((valorAscii >= 48 && valorAscii <= 57) && valorAscii != 91) { // condição que ira acumular enquanto for numero e nao encontrar [.
			palavra[i] = '\0';
		} else if (valorAscii == 91) {
			palavra[i] = '\0';
			break;
		}
	}
}


/**
 * Verifica se a palavra reservada é um tipo de variavel.
 *
 * @param char *palavra
 */
int isTipoVariavel(char *palavra) {
	int isValido = 0, i;
	
	for (i = 0; i < NU_TIPO_VARIAVEL; i++) {
		if (strcmp(palavra, tiposVariaveis[i]) == 0) {
			isValido = 1;
			break;
		}		
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
    char inicio[UCHAR_MAX], final[UCHAR_MAX], palavraAux[UCHAR_MAX];
    int i, nuLinha, count = 0, valorAscii;
    
    limparLixoVetor(final);
    limparLixoVetor(inicio);
    limparLixoVetor(palavraAux);
    
    strcpy(inicio, no->dados.conteudo);
    nuLinha = no->dados.linha;

    for (i = 0; i < strlen(inicio); i++) {
		valorAscii = (int) inicio[i]; 
		
		if (valorAscii != 10) {
			palavraAux[count] = (char) valorAscii;
			count++;
		} 
	}

	if (strcmp(palavraAux, palavrasReservadas[0]) != 0) {
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

	if (strcmp(palavraAux, palavrasReservadas[9]) != 0) {
		error(nuLinha, 2, palavraAux);
	}
}
 
