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
 * Valida se o programa inicializa com a palavra reservada 'programa' e finaliza com a palavra reservada 'fim'.
 *
 * @param Lista* lista 
 */
void validarAberturaFechamentoPrograma(Lista* lista) {
	Linha inicio = getPrimeiraLinha(lista);
	
	if (inicio.conteudo != "") {
		printf("Primeira 2 -  linha: %d - (%s) \n", inicio.linha, inicio.conteudo);	
	}
	
	// strcmp
	
//	if (inicioFim[1] != NULL) {
//		printf("Ultima linha: %d - %s \n", inicioFim[1].linha, inicioFim[1].conteudo);
//	}
}















