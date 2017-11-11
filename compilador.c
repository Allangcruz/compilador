#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <limits.h>
#include <stdbool.h>

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
3 - Definir lista de simbolos
OK => 4 - Definir palavras reservadas (utilizar vetor)
5 - validar palavras e popular tabelas de simbolos
	5.1 - As palavras reservadas sao case sensitive
	5.2 - Validar variaveis
6 - pesquisar algo que consiga medir consumo de memoria gasta para no final exibir indicadores.
7 - Validar 
*/


void main ()
{
	setlocale(LC_ALL, "PORTUGUESE");
    printf("============ COMPILADOR ============ \n\n");

    Lista* linhas;
    TabelaSimbolo* tabelaSimbolos = criaListaTabelaSimbolo();
    
    linhas = lerArquivo();
	analiseLexica(linhas);
    //imprimeLista(linhas);
    liberaLista(linhas);

    imprimeTabelaSimbolo(tabelaSimbolos);
	liberaListaTabelaSimbolo(tabelaSimbolos);

    printf("\n\n");
    system("pause");
    // 123,4
}

