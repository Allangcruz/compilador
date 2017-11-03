#include <stdio.h>
#include <locale.h>

#include "palavras-reservadas.h"
#include "estrutura.h"
#include "arquivo.h"

/*
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos

Fases do compilador
1 - Definir estrutura
OK => 2 - Ler Arquivo
3 - Definir lista de simbolos
OK => 4 - Definir palavras reservadas (utilizar vetor)
5 - validar palavras e popular tabelas de simbolos
6 - pesquisar algo que consiga medir tempo de execução e consumo de memoria, para no final exibir indicadores.

*/

void main ()
{
	setlocale(LC_ALL, "PORTUGUESE");
    printf("============ COMPILADOR ============ \n");

    Lista* linhas;
	linhas = lerArquivo();
    imprimirPalavrasReservadas();
    imprimeLista(linhas);
    liberaLista(linhas);
    system("pause");
    // teste 1234
}

