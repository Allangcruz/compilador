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


*/

// GUARDA O ARQUIVO GLOBAL
FILE *arquivo;

/**
 * Ler arquivo conteudo de arquivo
 */
void lerArquivo() {
	char url[]="programa.txt";
	char ch;

    arquivo = fopen("programa.txt", "r");
    
    if (arquivo == NULL) {
    	printf("\nErro, nao foi possivel abrir o arquivo\n");
	} else {
		while((ch=fgetc(arquivo))!= EOF) {
			putchar(ch);
		}			
	}
	
	fclose(arquivo);
    
	printf("\nModulo de ler arquivo carregado ...\n");
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

