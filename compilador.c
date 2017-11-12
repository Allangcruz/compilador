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

