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
    bool isVariavel = false, isPalavraReservada = false, isCondicaoParada = false, isLinhaComVariavel = false, isString = false, isPossuiPontoVirgula = false;
    
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
			
			if (valorAscii ==59) {
				isPossuiPontoVirgula = true;
			}
			
			// Verifica se a caracter ascii informado e uma condição de parada, para ser feita uma determinada analise.
			// As condiçoes de parada sao os caracterers : \0, espaco, (, ), virgula, ponto virgula, #, tabs
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 40) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59) && (valorAscii != 35) && (valorAscii != 9)) {
				palavraAux[count] = (char) valorAscii;
				count++;
			} else {
							
				isVariavel = validarDeclaracaoVariaveis(palavraAux);
				
				// verifica se não e uma variavel, se ele nao variavel, verificar se é palavra reservada
				if (! isVariavel) {
					isPalavraReservada = validarPalavrasReservadas(palavraAux);
					
					// quando for palavra reservada posso tratar aqui, exemplo se for tipo de variavel posso guarda para validar depois
					if (isPalavraReservada == true) {
					
						// caso seja: inteiro, caractere, real
						if (isTipoVariavel(palavraAux) == 1) {
							strcpy(tipoVariavel, palavraAux);
							isLinhaComVariavel = true;
						}
						
						// TODO caso seja leia
						
						// TODO caso seja escreva
						
						// TODO caso seja se
						
						// TODO caso seja senao
						
						// TODO caso seja para
						
					}
				} else {
					if (isLinhaComVariavel == true) {
						// validar se a variavel ja foi declarada. 
						if (validarVariavelDeclarada(palavraAux, tabelaSimbolos) == 1) {
							error(nuLinha, 13, palavraAux);
						}
						
						// verificar se tipo inteiro esta declarado com [, ]
						verificarPresencaColchetes(palavraAux, tipoVariavel, nuLinha);

						// salva a variavel valida
	    				Simbolo novoSimbolo;
	    				
	    				// caso tenha tamanho recupera o tamanho e adiciona na tabela de simbolo
						getTamanhoVariavel(palavraAux, auxTamanhoPalavra, nuLinha);
						strcpy(tamanhoPalavra, auxTamanhoPalavra);
						strcpy(novoSimbolo.tamanho, tamanhoPalavra);
	    				
						removeTamanhoVariavel(palavraAux);
	    				strcpy(novoSimbolo.palavra, palavraAux);
	    				strcpy(novoSimbolo.tipo, tipoVariavel);
						
						insereFinalTabelaSimbolo(tabelaSimbolos, novoSimbolo);
						limparLixoVetor(auxTamanhoPalavra);
					}
					
					// validar se a variavel ja foi declarada. 
					if (validarVariavelDeclarada(palavraAux, tabelaSimbolos) == 0) {
						error(nuLinha, 7, palavraAux);
					}
					
					
					// TODO verifica se a variavel esta sendo redeclarada

					// TODO Validar ponto e virgula no final da linha
				}
				
				// TODO verificar se a linha é uma declaracao de variavel e se o ultimo caracter é ;
				
				// por causa que quando e encontrado 2 ou mais criterio de paradas seguidos ele estava comparando com a palavra vazia, e isso nao pode acontecer
				if (strlen(palavraAux) > 0) {
					// compara se é uma variavel e se é uma palavra reservada
					if (isVariavel == false && isPalavraReservada == false) {
						
						error(nuLinha, 5, palavraAux);
						// verifica se a palavra e uma string	
						isString = validaPalavraString(palavraAux, nuLinha);
						
						if (! isString) {
						}
					}
				}
				
				limparLixoVetor(palavraAux);
				count=0;
				isVariavel = 0;
				isPalavraReservada = 0;
				isString = 0;
				
				// como # faz parte da variavel e tambem é uma condição de parada, entao preciso incrementar aqui
				if (valorAscii == 35) {
					palavraAux[count] = (char) valorAscii;
					count++;	
				}
			}
			
		} // fim for que percorre as colunas da linha
		
		// -------------------------------------------------------------------------------
		// Essa validação de ; no final esta invalida criar uma nova
		isPossuiPontoVirgula = validaDeclaracaoComPontoVirgula(conteudoLinha, nuLinha);
		
		// verifica se a linha possui declaração de variavel e tem ; nessa linha
		if (isLinhaComVariavel == true && isPossuiPontoVirgula == false) {
			//error(nuLinha, 11, conteudoLinha);
		}
		// -------------------------------------------------------------------------------

		no = no->prox;
		isLinhaComVariavel = false;
		limparLixoVetor(tipoVariavel);
		isPossuiPontoVirgula = false;
    } // fim while que percorre as linhas

}

/**
 * Verifica se a linha possui ; no final
 *
 * @param char* palavra
 * @param char* tipoVariavel
 * @param int nuLinha
 */
void verificarPresencaColchetes(char* palavra, char* tipoVariavel, int nuLinha) {
	int i, valorAscii;
	
	// se o tipo informado nao for caractere e real
	if ( (strcmp(tipoVariavel, tiposVariaveis[1]) == 0) || (strcmp(tipoVariavel, tiposVariaveis[2]) == 0)) {
		
		// TODO tratar quando for caractere
		if (strcmp(tipoVariavel, tiposVariaveis[1]) == 0) {
			
		}
		
		// TODO tratar quando for real
		if (strcmp(tipoVariavel, tiposVariaveis[2]) == 0) {
			
		}
		
		
	} else {
		for (i = 0; i < strlen(palavra); i++) {
			valorAscii = (int) palavra[i];
			// se na declaração possui [ ou ] 
			if (valorAscii == 91 || valorAscii == 93) {
				error(nuLinha, 14, palavra);
			}
		}
		
	}
}

/**
 * Verifica se a linha possui ; no final
 *
 * @param char* conteudoLinha
 * @param int nuLinha
 */
int validaDeclaracaoComPontoVirgula(char* conteudoLinha, int nuLinha) {
	int isValido = 0, i, valorAscii, countTotalPontoVirgula = 0;
	
	for (i = 0; i < strlen(conteudoLinha); i++) {
		valorAscii = (int) conteudoLinha[i]; 
		
		if (valorAscii == 59) {
			countTotalPontoVirgula++;
		}
	}
	
	if (countTotalPontoVirgula == 1) {
		isValido = 1;
	}
	
	return isValido;
}

/**
 * Verifica se a palavra informada e uma string valida, ou seja se a mesma esta dentro de ", " 
 *
 * @param char* palavra
 * @param int nuLinha
 */
int validaPalavraString(char* palavra, int nuLinha) {
	int isValido = 0, i, valorAscii, isDuploPalanceamentoValido = 0;
	
	for (i = 0; i < strlen(palavra); i++) {
		valorAscii = (int) palavra[i];
		
		// verifica se existe um caracter de abertura
		if (valorAscii == 34) {
			isDuploPalanceamentoValido++;
		}
	}
	
	// verifica se é impar, caso seja o duplo balanceamento esta invalido.
	if (isParImpar(isDuploPalanceamentoValido) == 0) {
		error(nuLinha, 10, palavra);
	} else {
		isValido = 1;
	}

	return isValido;
}

/**
 * Verifica se o valor informado e par ou impar. Retorna 1 - par, 0 - impar.
 *
 * @param int valor
 */
int isParImpar(int valor) {
	int isValido = 0;
	
	if (valor % 2 == 0) {
		isValido = 1;
	}
	
	return isValido;
}

/**
 * Valida se a variavel informada ja esta declarada na tabela de simbolos
 *
 * @param char * palavra
 */
int validarVariavelDeclarada(char* palavra, TabelaSimbolo* tabelaSimbolos) {
	int isValido = 0;
    
	if (tabelaSimbolos == NULL) {
        exit(1);
    }
	
	ElemSimbolo* no = *tabelaSimbolos;

    while (no != NULL) {
    	if (strcmp(palavra, no->dados.palavra) == 0) {
    		isValido = 1;
    		break;
		}
        no = no->prox;
    }
	
	return isValido;
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
 * @param char retorno[]
 * @param int nuLinha
 */
void getTamanhoVariavel(char palavra[], char retorno[], int nuLinha) {

	int i, tamanhoPalavra = strlen(palavra) - 1, valorAscii, count = 0, countValorEntreConchete = 0, isPossuiConchete = 0;
	char valorTamanho[UCHAR_MAX], auxValorTamanho[UCHAR_MAX];
	
	limparLixoVetor(valorTamanho);
	limparLixoVetor(auxValorTamanho);
	
	// percorre a palavra de traz para frente
	for (i = tamanhoPalavra; i >= 0; i--) {
		valorAscii = palavra[i];
		// printf("(%d) - %c \n", i, palavra[i]);

		// verifica se o ultimo caracter é um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			isPossuiConchete++;
			continue;
		} else if((valorAscii >= 48 && valorAscii <= 57) && valorAscii != 91) { // condição que ira acumular enquanto for numero e nao encontrar [.
			auxValorTamanho[count] = palavra[i];
			countValorEntreConchete++;
			
			// printf("=>=> (%d) - %c \n", i, palavra[i]);
			count++;
		} else if (valorAscii == 91) {
			isPossuiConchete++;
			break;
		}
	}
	
	// se existir apenas um abertura ou fechamento de conchete
	if (isPossuiConchete == 1) {
		error(nuLinha, 9, palavra);
	} else if (isPossuiConchete == 2) {
		if (countValorEntreConchete == 0) {
			error(nuLinha, 8, palavra);
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
		
		// \0, quebra de linha
		if (valorAscii != 10) {
			
			// apenas se nao for espaço e tabs
			if (valorAscii != 32 && valorAscii != 9) {
				palavraAux[count] = (char) valorAscii;
				count++;
			}
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
		
		// \0, quebra de linha
		if (valorAscii != 10) {
			
			// apenas se nao for espaço e tabs
			if (valorAscii != 32 && valorAscii != 9) {
				palavraAux[count] = (char) valorAscii;
				count++;
			}
		}
	}

	if (strcmp(palavraAux, palavrasReservadas[9]) != 0) {
		error(nuLinha, 2, palavraAux);
	}
}
 
