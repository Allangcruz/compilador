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















