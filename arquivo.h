/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos

Responsavel por manipular a leitura de arquivos.
Funcoes para ler string:

(http://www.cprogressivo.net/2013/11/Como-ler-arquivos-em-C-As-funcoes-fgetc-fscanf-fgets.html)
getchar
scanf
gets.
------------------------------------------------------------------------------------
fgetc : Ler caracter por caracter ate encontrar o final do arquico 'EOF'.
fgets : Ler linha por linha do arquivo

*/

// GUARDA O ARQUIVO GLOBAL
FILE *arquivo;

/**
 * Ler arquivo conteudo de arquivo
 */
Lista* lerArquivo() {
	char url[]="programa.txt";
	char ch[200];
	int nuLinhas = 1;
	Lista* linhas = criaLista();

    arquivo = fopen(url, "r");
    
    if (arquivo == NULL) {
    	printf("\nErro, nao foi possivel abrir o arquivo\n");
	} else {
		while ((fgets(ch, sizeof(ch), arquivo)) != NULL) {
			Linha item;
			item.isLinhaVazia = 0;
			
			if (strlen(ch) == 1) {
				item.isLinhaVazia = 1;
			}
			
			item.linha = nuLinhas;
			strcpy(item.conteudo, ch);
			insereListaFinal(linhas, item);
			nuLinhas ++;
		}			
	}
	
	fclose(arquivo);
    
	printf("\nModulo de ler arquivo carregado ...\n");
	
	return linhas;
}

