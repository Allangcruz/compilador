/*
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
*/

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <limits.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>

/**
 * Armazena o total de memoria utilizada no compilador.
 */
int TOTAL_CONSUMO_MEMORIA = 0;

// 367001600 bytes => 350 megabytes | 
int MAX_TOTAL_CONSUMO_MEMORIA = 367001600;

/**
 * Constante com o total de palavras reservadas.
 */
#define NU_PALAVRA_RESERVADAS 10 
#define NU_TIPO_VARIAVEL 4

#include "mensagem-erros.h"
#include "palavras-reservadas.h"
#include "estrutura.h"
#include "arquivo.h"
#include "tabela-simbolo.h"
#include "validacoes-palavras-reservadas.h"

void main ()
{
	setlocale(LC_ALL, "PORTUGUESE");
    printf("\n================================================================\n");
    printf("#= COMPILADOR, COMPILADORZINHO, COMPILADORZÃO, COMPILADORZAÇO =#\n");
    printf("================================================================\n");

	printf("================================================================\n");
    printf("ALLAN GONÇALVE DA CRUZ - ELSON BENTO DOS SANTOS\n");
    printf("================================================================\n");
    
    memoriaConsumida(sizeof(palavrasReservadas), 1);
    memoriaConsumida(sizeof(tiposVariaveis), 1);

    Lista* linhas;
	memoriaConsumida(sizeof(linhas), 1);
    
	TabelaSimbolo* tabelaSimbolos = criaListaTabelaSimbolo();
    memoriaConsumida(sizeof(tabelaSimbolos), 1);
    
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

