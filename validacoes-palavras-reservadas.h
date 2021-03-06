/**
Alunos:
Allan Gon�alves da Cruz
Elson Bento dos Santos
=================================================================================================================================
	Tabela ascii util para vazer compara�oes pois comparar string nao estava sendo confiavel: 
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

    int i, 
		valorAscii, 
		nuLinha, 
		count = 0, 
		countValor = 0,
		countVariaveis = 0,
		countVirgulas = 0, 
		countAspas = 0;

    char palavraAux[UCHAR_MAX],
		 conteudoLinha[UCHAR_MAX], 
		 palavraAuxVariavel[UCHAR_MAX], 
		 tipoVariavel[UCHAR_MAX], 
		 tamanhoPalavra[UCHAR_MAX], 
		 auxTamanhoPalavra[UCHAR_MAX],
		 auxPalavraValor[UCHAR_MAX],
		 auxNomeVariavel[UCHAR_MAX];
		 
    bool isVariavel = false,
		 isPalavraReservada = false, 
		 isCondicaoParada = false, 
		 isLinhaComVariavel = false, // verifica se a linha � uma declara��o de variavel
		 isString = false, 
		 isPossuiPontoVirgula = false, 
		 isLeia = false,
		 isEscreva = false,
		 isPossuiAspas = false,
		 isAtribuicao = false;
    
	limparLixoVetor(palavraAux);
    limparLixoVetor(tipoVariavel);
    limparLixoVetor(conteudoLinha);
    limparLixoVetor(tamanhoPalavra);
    limparLixoVetor(auxTamanhoPalavra);
    limparLixoVetor(palavraAuxVariavel);
    limparLixoVetor(auxPalavraValor);
    limparLixoVetor(auxNomeVariavel);
    
    while (no != NULL) {
		strcpy(conteudoLinha, no->dados.conteudo);
		nuLinha = no->dados.linha;
		
		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i]; 
			
			// verifica se existe ';'
			if (valorAscii == 59) {
				isPossuiPontoVirgula = true;
			}
			
			// verifica se � '"'
			if (valorAscii == 34) {
				countAspas++;
				isPossuiAspas = true;
			}
					
			// Verifica se a caracter ascii informado e uma condi��o de parada, para ser feita uma determinada analise.
			// As condi�oes de parada sao os caracterers : \0, espaco, (, ), virgula, ponto virgula, #, tabs, =
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 40) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59) && (valorAscii != 35) && (valorAscii != 9) && (valorAscii != 61)) {
				if (isPossuiAspas == false) {
					palavraAux[count] = (char) valorAscii;
					count++;
				}

				atualizarValorVariavel(tabelaSimbolos, auxNomeVariavel, auxPalavraValor);		
			} else if (isPossuiAspas == false) {
				//printf("[%d][%d] - [%d][%c] - (%s) - (%s) - (%s)\n", nuLinha, i, valorAscii, (char) valorAscii, palavraAux, auxPalavraValor, auxNomeVariavel);
				//printf("[%d][%d][%c][%s][%s] - (%d)(%d) \n", nuLinha, i, (char) valorAscii, palavraAux, auxPalavraValor, countVariaveis, countVirgulas);
				
				// verifica se � declara��o de variavel e atribui��o
				if (isLinhaComVariavel == true && valorAscii == 61) {
					isAtribuicao = true;
				}
										
				isVariavel = validarDeclaracaoVariaveis(palavraAux, nuLinha);
				
				// verifica se n�o e uma variavel
				// verificar se � palavra reservada
				if (! isVariavel) {
					isPalavraReservada = validarPalavrasReservadas(palavraAux);
					
					// quando for palavra reservada posso tratar aqui, exemplo se for tipo de variavel posso guarda para validar depois
					if (isPalavraReservada == true) {
					
						// caso seja: inteiro, caractere, real
						if (isTipoVariavel(palavraAux) == 1) {
							strcpy(tipoVariavel, palavraAux);
							isLinhaComVariavel = true;
						}
						
						// caso seja leia
						isLeia = validarPalavraLeia(palavraAux, nuLinha, conteudoLinha);
											
						// caso seja escreva
						isEscreva = validarPalavraEscreva(palavraAux, nuLinha, conteudoLinha);
						
						// TODO caso seja se
						
						// TODO caso seja senao
						
						// TODO caso seja para
						
					}
				} else {
					
					countVariaveis ++;

					if (isLinhaComVariavel == true && isLeia == false) {
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
	    				strcpy(auxNomeVariavel, palavraAux);
	    				strcpy(novoSimbolo.tipo, tipoVariavel);
						
						insereFinalTabelaSimbolo(tabelaSimbolos, novoSimbolo);
						limparLixoVetor(auxTamanhoPalavra);
					}

					// validar se a variavel ja foi declarada. 
					if (validarVariavelDeclarada(palavraAux, tabelaSimbolos) == 0) {
						error(nuLinha, 7, palavraAux);
					}
				}
				
				// verifica se a string em '"' esta valida
				if (strlen(palavraAux) > 0) {
					if (isVariavel == false && isPalavraReservada == false && countAspas > 0) {
						// verifica se a palavra e uma string	
						isString = validaPalavraString(palavraAux, nuLinha);
						
						if (! isString) {
							//error(nuLinha, 5, palavraAux);
						}
					}
				}
				
				// por causa que quando e encontrado 2 ou mais criterio de paradas seguidos ele estava comparando com a palavra vazia, e isso nao pode acontecer
				if (strlen(palavraAux) > 0) {
					// compara se � uma variavel e se � uma palavra reservada
					if (isVariavel == false && isPalavraReservada == false && countAspas == 0) {
						error(nuLinha, 5, palavraAux);
					}
				}
				
				limparLixoVetor(palavraAux);
				count=0;
				isVariavel = 0;
				isPalavraReservada = 0;
				isString = 0;
				
				// como # faz parte da variavel e tambem � uma condi��o de parada, entao preciso incrementar aqui
				if (valorAscii == 35) {
					palavraAux[count] = (char) valorAscii;
					count++;	
				}
			} // fim else valores que s�o condi��o de parada
			
			// condic�o de parada quando para limpar a variavel 'auxPalavraValor'
			// espaco, #, virgula, ponto e virgula
			if ((countAspas == 2) && ((valorAscii == 32) || (valorAscii == 35) || (valorAscii == 44) || (valorAscii == 59))) {
				atualizarValorVariavel(tabelaSimbolos, auxNomeVariavel, auxPalavraValor);
				limparLixoVetor(auxPalavraValor);
				limparLixoVetor(auxNomeVariavel);
				countValor = 0;
				isPossuiAspas = false;
				//printf("zerou as varaiveis aqui\n");
				
				// como # faz parte da variavel e tambem � uma condi��o de parada, entao preciso incrementar aqui
				if (valorAscii == 35) {
					palavraAux[count] = (char) valorAscii;
					count++;	
				}
			}

			// caso seja encontrada 2 aspas, e em seguida seja um caracter de parada tais como:
			// virgula, ')', ';'
			// deve ser zerado a contagem de 'countAspas'
			if ((countAspas == 2) && ((valorAscii == 44) || (valorAscii == 41) || (valorAscii == 59))) {
				countAspas = 0;
			}
			
			if (isAtribuicao == true && countAspas > 0) {
				auxPalavraValor[countValor] = (char) valorAscii;
				countValor++;
			}
			
			// conta a quantidade de ','
			if (valorAscii == 44 && isPossuiAspas == false) {
				countVirgulas ++;	
			}

		} // fim for que percorre as colunas da linha
		
		// -------------------------------------------------------------------------------
		// verifica o duplo balanceamento de '"'
		if (countAspas != 0) {
			error(nuLinha, 22, conteudoLinha);
		}

		// Essa valida��o de ; no final esta invalida criar uma nova
		isPossuiPontoVirgula = validaDeclaracaoComPontoVirgula(conteudoLinha, nuLinha);
		
		// verifica se a linha possui declara��o de variavel e tem ; nessa linha
		if (isLinhaComVariavel == true && isPossuiPontoVirgula == false) {
			error(nuLinha, 11, conteudoLinha);
		}
		
		// caso tenha mais de 1 variavel a quantidade de virgulas ser�o 'countVirgulas' - 'countVariaveis' - 1)
		if (countVariaveis > 1 && isEscreva == false) {
			if (countVirgulas != (countVariaveis - 1)) {
				error(nuLinha, 20, conteudoLinha);	
			}
		}
		
		// talvez criar uma funcao que sempre reset essa itens
		no = no->prox;
		isLinhaComVariavel = false;
		limparLixoVetor(tipoVariavel);
		limparLixoVetor(auxPalavraValor);
		limparLixoVetor(auxNomeVariavel);
		isPossuiPontoVirgula = false;
		isLeia = false;
		isEscreva = false;
		countVariaveis = 0;
		countVirgulas = 0;
		countAspas = 0;
		isPossuiAspas = false;
		isAtribuicao = false;
		countValor = 0;
    } // fim while que percorre as linhas
}

/**
 * Atualiza o valor da variavel existente.
 */
void atualizarValorVariavel(TabelaSimbolo* lista, char * noVariavel, char * valor) {
	if (lista == NULL) {
        return;
    }
    
	ElemSimbolo* no = *lista;
	
	while (no != NULL) {
		if (strcmp(noVariavel, no->dados.palavra) == 0) {
			strcpy(no->dados.valor, valor);
		}
		no = no->prox;
    }
}

/**
 * Verifica se a linha possui estrutura 'escreva' e verifica seus criterios.
 *
 * @param char* palavra
 * @param int nuLinha
 * @param int linha
 */
int validarPalavraEscreva(char * palavra, int nuLinha, char * linha) {
	int isValido = 0, 
		i , 
		count = 0, 
		parenteses = 0, 
		valorAscii, 
		isPossuiPontoVirgula = 0, 
		isEscrevaValido = 0; // verifica se a palavra escreva esta no padrao 'escreva(#' ou 'escreva("'
	
	char palavraAux[UCHAR_MAX];
	limparLixoVetor(palavraAux);
	
	// verifica se a palavra reservada � escreva
	if (strcmp(palavra, palavrasReservadas[2]) == 0) {
		
		// identifica se a palavra reservada � 'escreva'
		isValido = 1;
		
		// valida se apos a palavra 'escreva' possui obrigatoriamente um '(' e uma variavel.
		for (i = 0; i < strlen(linha); i++) {
			valorAscii = (int) linha[i];
			
			// Verifica se a caracter ascii informado e uma condi��o de parada, para ser feita uma determinada analise.
			// As condi�oes de parada sao os caracterers : \0, espaco, ), virgula, ponto virgula, #, tabs
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59) && (valorAscii != 9)) {
				palavraAux[count] = (char) valorAscii;
				count++;
				
				if ((strcmp(palavraAux, "escreva(") == 0)) {
					isEscrevaValido++;
					break;
				}
			}
		}
		if (isEscrevaValido == 0) {
			error(nuLinha, 21, linha);
		}
		
		// nao pode haver declara��es dentro da estrutura
		for (i = 0; i < strlen(linha); i++) {
			valorAscii = (int) linha[i]; 
			
			// cada caractere tem que ser diferente de \0, espaco e tab
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 9)) {
				// balanceamento de parenteses '('
				if (valorAscii == 40) {
					parenteses ++;
				}
				
				// balanceamento de parenteses ')'
				if (valorAscii == 41) {
					parenteses --;
				}
			}
		}
		
		// verifica se a linha do leia possui ';'
		for (i = strlen(linha); i > 0; i--) {
			valorAscii = (int) linha[i]; 
			
			// cada caractere tem que ser diferente de \0, espaco e tab
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 9)) {
				
				// verifica se o caracter � ';'
				if (valorAscii == 59 && isPossuiPontoVirgula == 0) {
					isPossuiPontoVirgula ++;
					break;
				}
			}
		}
		
		// verifica se existe duplo balanceamento de parentes
		if (parenteses != 0) {
			error(nuLinha, 17, linha);
		}

		// verificar o ; no final da linha do leia
		if (isPossuiPontoVirgula != 1) {
			error(nuLinha, 18, linha);
		}
	}
		
	return isValido;
}

/**
 * Verifica se a linha possui estrutura 'leia' e verifica seus criterios.
 *
 * @param char* palavra
 * @param int nuLinha
 * @param int linha
 */
int validarPalavraLeia(char * palavra, int nuLinha, char * linha) {
	int isValido = 0, 
		i , 
		count = 0, 
		parenteses = 0, 
		valorAscii, 
		isPossuiPontoVirgula = 0, 
		isLeiaValido = 0; // verifica se a palavra leia esta no padrao 'leia('
	
	char palavraAux[UCHAR_MAX];
	limparLixoVetor(palavraAux);
	
	// verifica se a palavra reservada � leia
	if (strcmp(palavra, palavrasReservadas[1]) == 0) {
		
		// identifica se a palavra reservada � 'leia'
		isValido = 1;
		
		// valida se apos a palavra 'leia' possui obrigatoriamente um '(' e uma variavel.
		for (i = 0; i < strlen(linha); i++) {
			valorAscii = (int) linha[i];
			
			// Verifica se a caracter ascii informado e uma condi��o de parada, para ser feita uma determinada analise.
			// As condi�oes de parada sao os caracterers : \0, espaco, ), virgula, ponto virgula, #, tabs
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59) && (valorAscii != 9)) {
				palavraAux[count] = (char) valorAscii;
				count++;
				
				if (strcmp(palavraAux, "leia(#") == 0) {
					isLeiaValido++;
					break;
				}
			}
		}
		
		if (isLeiaValido == 0) {
			error(nuLinha, 19, linha);
		}
		
		// nao pode haver declara��es dentro da estrutura
		for (i = 0; i < strlen(linha); i++) {
			valorAscii = (int) linha[i]; 
			
			// cada caractere tem que ser diferente de \0, espaco e tab
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 9)) {
				// balanceamento de parenteses '('
				if (valorAscii == 40) {
					parenteses ++;
				}
				
				// balanceamento de parenteses ')'
				if (valorAscii == 41) {
					parenteses --;
				}
			}
		}
		
		// verifica se a linha do leia possui ';'
		for (i = strlen(linha); i > 0; i--) {
			valorAscii = (int) linha[i]; 
			
			// cada caractere tem que ser diferente de \0, espaco e tab
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 9)) {
				
				// verifica se o caracter � ';'
				if (valorAscii == 59 && isPossuiPontoVirgula == 0) {
					isPossuiPontoVirgula ++;
					break;
				}
			}
		}
		
		// verifica se existe duplo balanceamento de parentes
		if (parenteses != 0) {
			error(nuLinha, 17, linha);
		}
		
		// verificar o ; no final da linha do leia
		if (isPossuiPontoVirgula != 1) {
			error(nuLinha, 18, linha);
		}
	}
		
	return isValido;
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
		
	if (strcmp(tipoVariavel, tiposVariaveis[0]) == 0) {
		for (i = 0; i < strlen(palavra); i++) {
			valorAscii = (int) palavra[i];

			// se na declara��o possui [ ou ] 
			if (valorAscii == 91 || valorAscii == 93) {
				error(nuLinha, 14, palavra);
			}
		}
	}
	
	// TODO tratar quando for caractere
	if (strcmp(tipoVariavel, tiposVariaveis[1]) == 0) {
		validarTipoCaractere(palavra, nuLinha);
	}
	
	// TODO tratar quando for real
	if (strcmp(tipoVariavel, tiposVariaveis[2]) == 0) {
		validarTipoReal(palavra, nuLinha);
	}
}

/**
 * Valida o tipo de dados do caractere
 */
void validarTipoCaractere(char * palavra, int nuLinha) {
	int i, tamanhoPalavra = strlen(palavra) - 1, valorAscii, count = 0, countValorEntreConchete = 0;
	char auxValorTamanho[UCHAR_MAX];
	int isFecharColchete = 0;
	int isAberturaColchete = 0;

	limparLixoVetor(auxValorTamanho);
	
	// percorre a palavra de traz para frente
	for (i = tamanhoPalavra; i >= 0; i--) {
		valorAscii = palavra[i];

		// verifica se o ultimo caracter � um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			isFecharColchete++;
			continue;
			// condi��o que ira acumular enquanto for numero e nao encontrar [.
		} else if(valorAscii >= 48 && valorAscii <= 57) { 
			auxValorTamanho[count] = palavra[i];
			countValorEntreConchete++;
			
			count++;
		} else if (valorAscii == 91) {
			isAberturaColchete++;
		}
	}
	
	// TODO Validar valores acima ou iguais a zero.
	
	if (isFecharColchete == 0 || isAberturaColchete == 0 || countValorEntreConchete == 0) {
		printf("\n[TIPO CARACTERE]\n");
		error(nuLinha, 15, palavra);
	}
}

/**
 * Valida o tipo de dados real
 */
void validarTipoReal(char * palavra, int nuLinha) {
	int i, tamanhoPalavra = strlen(palavra) - 1, valorAscii, count = 0, countValorEntreConchete = 0;
	char auxValorTamanho[UCHAR_MAX];
	int isFecharColchete = 0;
	int isAberturaColchete = 0;
	int countTotalPonto = 0;

	limparLixoVetor(auxValorTamanho);
	// percorre a palavra de traz para frente
	for (i = tamanhoPalavra; i >= 0; i--) {
		valorAscii = palavra[i];

		// verifica se o ultimo caracter � um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			isFecharColchete++;
			continue;
			// condi��o que ira acumular enquanto for 0-9 e que o mesmo tenha .
		} else if((valorAscii >= 48 && valorAscii <= 57) || valorAscii == 46) { 
			auxValorTamanho[count] = palavra[i];
			countValorEntreConchete++;
			
			count++;
		} else if (valorAscii == 91) {
			isAberturaColchete++;
		}
	}
	
	// TODO Validar valores acima ou iguais a zero, tratar depois
	
	if (isFecharColchete == 0 || isAberturaColchete == 0 || countValorEntreConchete == 0) {
		printf("\n[TIPO REAL]\n");
		error(nuLinha, 15, palavra);
	}
	
	for (i = 0; i < strlen(auxValorTamanho); i++) {
		valorAscii = auxValorTamanho[i];
		
		if (valorAscii == 46) {
			countTotalPonto++;
		}
	}
	
	if (countTotalPonto != 1) {
		printf("\n[TIPO REAL]\n");
		error(nuLinha, 15, palavra);
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
	
	// verifica se � impar, caso seja o duplo balanceamento esta invalido.
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
		// apenas a-z
		if ((int) palavra[1] >= 97 &&  (int) palavra[1] <= 122) {
			isValido = 1;
		} else {
			isValido = 0;
			printf("\n[Declara��o variavel]\n");
			error(nuLinha, 6, palavra);
		}
		
		for (i = 2; i < strlen(palavra); i++) {
			valorAscii = (int) palavra[i];
			
			// permiter apenas a-z, 0-9, A-Z, [, ], .
			if (! ((valorAscii >= 97 && valorAscii <= 122) || (valorAscii >= 48 && valorAscii <= 57) || (valorAscii >= 65 && valorAscii <= 90) || valorAscii == 91 || valorAscii == 93 || valorAscii == 46)) {
				isValido = 0;
				printf("\n[Declara��o variavel]\n");
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

		// verifica se o ultimo caracter � um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			isPossuiConchete++;
			continue;
		} else if((valorAscii >= 48 && valorAscii <= 57) && valorAscii != 91) { // condi��o que ira acumular enquanto for numero e nao encontrar [.
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

		// verifica se o ultimo caracter � um ], caso seja vai percorrendo para salvar o tamanho
		if (i == tamanhoPalavra && valorAscii == 93) {
			palavra[i] = '\0';
			continue;
		} else if((valorAscii >= 48 && valorAscii <= 57) && valorAscii != 91) { // condi��o que ira acumular enquanto for numero e nao encontrar [.
			palavra[i] = '\0';
		} else if (valorAscii == 91) {
			palavra[i] = '\0';
			break;
		}
	}
}


/**
 * Verifica se a palavra reservada � um tipo de variavel.
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
			
			// apenas se nao for espa�o e tabs
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
			
			// apenas se nao for espa�o e tabs
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
 
