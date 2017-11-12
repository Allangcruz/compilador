#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <limits.h>
#include <stdbool.h>
#include <locale.h>

/**
 * Constante com o total de palavras reservadas.
 */
#define NU_PALAVRA_RESERVADAS 10 

#include "palavras-reservadas.h"
#include "estrutura.h"
#include "arquivo.h"
#include "mensagem-erros.h"
#include "tabela-simbolo.h"
#include "validacoes-palavras-reservadas.h"

/*
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos

Fases do compilador
OK => 1 - Definir estrutura que armazena o conteudo do arquivo
OK => 2 - Ler Arquivo
OK => 3 - Definir lista de simbolos
OK => 4 - Definir palavras reservadas (utilizar vetor)
OK => 5 - validar palavras e popular tabelas de simbolos
	OK => 5.1 - As palavras reservadas sao case sensitive
	OK => 5.2 - Validar variaveis
6 - pesquisar algo que consiga medir consumo de memoria gasta para no final exibir indicadores.
7 - Validar 
*/

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
 * Verifica se a caracter ascii informado e uma condição de parada, para ser feita uma determinada analise.
 * As condiçoes de parada sao os caracterers : \0, espaco, (, ), virgula, ponto e virgula
 * @param int valorAscii
 */
bool checkCondicaoParada(int valorAscii) {
	return ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 40) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59));
}

/**
 * Aplica validacoes referente a analise lexica.
 */
void analiseLexica(Lista* lista, TabelaSimbolo* tabelaSimbolos) {
	validarAberturaFechamentoPrograma(lista);

	if (lista == NULL) {
        return false;
    }
    
    Elem* no = *lista;
    int i, valorAscii, nuLinha, count = 0;
    char palavraAux[UCHAR_MAX], conteudoLinha[UCHAR_MAX], palavraAuxVariavel[UCHAR_MAX];
    bool isVariavel = false, isPalavraReservada = false, isCondicaoParada = false;
    
	limparLixoVetor(palavraAux);
    limparLixoVetor(conteudoLinha);
    limparLixoVetor(palavraAuxVariavel);
    
    while (no != NULL) {
		strcpy(conteudoLinha, no->dados.conteudo);
		nuLinha = no->dados.linha;
		
		for (i = 0; i < strlen(conteudoLinha); i++) {
			valorAscii = (int) conteudoLinha[i]; 
			
			// \0, espaco, (, ), virgula, ponto e virgula
			if ((valorAscii != 10) && (valorAscii != 32) && (valorAscii != 40) && (valorAscii != 41) && (valorAscii != 44) && (valorAscii != 59)) {
				palavraAux[count] = (char) valorAscii;
				count++;
			} else {
				// printf("--------------------------------------------------------------------------------------\n");
				// printf("==> (Linha: %d) - Foi encontrado uma condição de parada (ascii: %d) <==\n", nuLinha, valorAscii);
				isVariavel = validarDeclaracaoVariaveis(palavraAux);
				
				// verifica se não e uma variavel, se ele nao variavel, verificar se é palavra reservada
				if (! isVariavel) {
					isPalavraReservada = validarPalavrasReservadas(palavraAux);
					
					if (isPalavraReservada == true) {
						// printf("[Linha: %d] - palavra reservada => (%s)\n", nuLinha, palavraAux);
					}
				} else {
					// (aqui são apenas para variaveis) tratar aqui os comportamento de variaveis e salvar na tabela de simbolos
					//printf("[Linha: %d] - variavel => (%s)\n", nuLinha, palavraAux);

    				Simbolo novoSimbolo;
    				strcpy(novoSimbolo.palavra, palavraAux);
					insereFinalTabelaSimbolo(tabelaSimbolos, novoSimbolo);
				}
				
				// por causa que quando e encontrado 2 ou mais criterio de paradas seguidos ele estava comparando com a palavra vazia, e isso nao pode acontecer
				if (strlen(palavraAux) > 0) {
					// compara se é uma variavel e se é uma palavra reservada
					// printf("isVariavel => [%d] - isPalavraReservada => [%d] (i: %d, coluna: %d) \n", isVariavel, isPalavraReservada, i, strlen(palavraAux));
					if (isVariavel == false && isPalavraReservada == false) {
						//printf("(linha: %d) - Nao e variavel e nem uma palavra reservada (%s).\n", nuLinha, palavraAux);
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
	int isValido = 0, i;

	for (i = 0; i < NU_PALAVRA_RESERVADAS; i++) {
		if (strcasecmp(palavra, palavrasReservadas[i]) == 0) {
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

	printf("|| %s - %s - %d ||", palavraAux, palavrasReservadas[0], strcasecmp(palavraAux, palavrasReservadas[0]));

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
	
	exit(1);
}
 


void main ()
{
	setlocale(LC_ALL, "PORTUGUESE");
    printf("\n================================================================\n");
    printf("#= COMPILADOR, COMPILADORZINHO, COMPILADORZÃO, COMPILADORZAÇO =#\n");
    printf("================================================================\n");

	printf("================================================================\n");
    printf("ALLAN GONÇALVE DA CRUZ - ELSON BENTO DOS SANTOS\n");
    printf("================================================================\n");

    Lista* linhas;
    TabelaSimbolo* tabelaSimbolos = criaListaTabelaSimbolo();
    
    linhas = lerArquivo();
	analiseLexica(linhas, tabelaSimbolos);
    // imprimeLista(linhas);
    liberaLista(linhas);

    imprimeTabelaSimbolo(tabelaSimbolos);
	liberaListaTabelaSimbolo(tabelaSimbolos);
	
    printf("\n\n");
    system("pause");
    // 1,2,3,4
}

