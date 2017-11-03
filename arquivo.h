/*
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
		//while ((ch=fgetc(arquivo))!= EOF) {
		while ((fgets(ch, sizeof(ch), arquivo)) != NULL) {
			Linha item;
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

/**
 * Escreve conteudo no arquivo.
 */
void escreverArquivo() {
	printf("\nModulo de escrever arquivo carregado ...\n");
}

/**
 * Retorna o Total de linhas continas no arquivo lido.
 */
int getTotalLinhas() {
	int total = 0;
	char ch;
	
	if (arquivo == NULL) {
    	printf("\nErro, nao foi possivel abrir o arquivo\n");
	} else {
		while((ch=fgetc(arquivo))!= EOF) {
			// '\n' indica o final  da linha
			if (ch == '\n') {
				total ++;
			}
		}			
	}
	printf("\nModulo de contar o total de linhas do arquivo carregado ...\n");
	
	printf("Existem %d linhas no arquivo\n", total);
	
	return total;
}

