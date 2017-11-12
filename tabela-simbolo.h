/**
Alunos:
Allan Gon�alves da Cruz
Elson Bento dos Santos
*/

/**
 * Struct que armazena a informacoes do simbolo da tabela de simbolos.
 */
typedef struct simbolo {
	char tipo[UCHAR_MAX], palavra[UCHAR_MAX], valor[UCHAR_MAX];
    int tamanho;
} Simbolo;

/**
 * Struct que armazena os elementos da lista, de acordo com o tipo do dado.
 */
typedef struct elemSimbolo {
    struct elemSimbolo *ant;
    Simbolo dados;
    struct elemSimbolo *prox;
} ElemSimbolo;

typedef struct elemSimbolo* TabelaSimbolo;

/**
 * Cria a lista, que armazena a tabela de simbolos.
 *
 * @return TabelaSimbolo* lista
 */
TabelaSimbolo* criaListaTabelaSimbolo() {
    TabelaSimbolo* lista = (TabelaSimbolo*) malloc(sizeof(TabelaSimbolo));

    if (lista != NULL) {
        *lista = NULL;
    }

    return lista;
}

/**
 * Remove todos os elementos da lista.
 *
 * @param TabelaSimbolo* lista
 */
void liberaListaTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista != NULL) {
        ElemSimbolo* no;

        while ((*lista) != NULL) {
            no = *lista;
            *lista = (*lista)->prox;
            free(no);
        }

        free(lista);
    }
}

/**
 * Inseri no final da lista de acordo com parametros informados.
 *
 * @param TabelaSimbolo* lista
 * @param Simbolo simbolo
 * @return int
 */
int insereFinalTabelaSimbolo(TabelaSimbolo* lista, Simbolo simbolo) {
    if (lista == NULL) {
        return 0;
    }

    ElemSimbolo *no;
    no = (ElemSimbolo*) malloc(sizeof(ElemSimbolo));
    if (no == NULL) {
        return 0;
    }

    no->dados = simbolo;
    no->prox = NULL;

    // lista vazia: insere in�cio
    if ((*lista) == NULL) {
        no->ant = NULL;
        *lista = no;
    } else {
        ElemSimbolo *aux;
        aux = *lista;

        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

/**
 * Inseri no inicio da lista de acordo com parametros informados.
 *
 * @param Lista* lista
 * @param Linha lin
 * @return int
 */
int insereInicioTabelaSimbolo(TabelaSimbolo* lista, Simbolo simbolo) {
    if (lista == NULL) {
        return 0;
    }

    ElemSimbolo* no;
    no = (ElemSimbolo*) malloc(sizeof(ElemSimbolo));

    if (no == NULL) {
        return 0;
    }

    no->dados = simbolo;
    no->prox = (*lista);
    no->ant = NULL;

    //lista n�o vazia: apontar para o anterior!
    if (*lista != NULL) {
        (*lista)->ant = no;
    }

    *lista = no;

    return 1;
}

/**
 * Retorna o total de itens que compoen a lista.
 *
 * @param TabelaSimbolo* lista
 * @return int cont
 */
int tamanhoTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista == NULL) {
        return 0;
    }

    int cont = 0;
    ElemSimbolo* no = *lista;

    while (no != NULL) {
        cont++;
        no = no->prox;
    }

    return cont;
}

/**
 * Verifica se a lista esta vazia.
 *
 * @param TabelaSimbolo* lista
 * @return int
 */
int isVazioTabelaSimbolo(TabelaSimbolo* lista) {
	int isVazio = 0;

    if (lista == NULL) {
        isVazio = 1;
    }

    if (*lista == NULL) {
        isVazio = 1;
    }

    return isVazio;
}

/**
 * Imprime os itens da lista.
 *
 * @param TabelaSimbolo* lista
 */
void imprimeTabelaSimbolo(TabelaSimbolo* lista) {
    if (lista == NULL) {
        return;
    }

    ElemSimbolo* no = *lista;
    bool isListaVazia = isVazioTabelaSimbolo(lista);
    printf("\n================================================\n");
    printf("============== TABELA DE SIMBOLOS ==============\n");
    printf("================================================\n");
    
    if (isListaVazia == 1) {
    	printf("\tA TABELA DE SIMBOLOS EST� VAZIA.\n");	
    	exit(1);
	}

    while (no != NULL) {
        printf("Palavra: %s \n", no->dados.palavra);
        printf("Tipo: %s \n", no->dados.tipo);
        //printf("Total caracter da palavra: %d \n", strlen(no->dados.palavra));
        printf("-------------------------------------------------------------\n");
        no = no->prox;
    }
    
    exibirConsumoMemoria();
}

/**
 * Exibe o tatal de memoria consumida pelo compilado.	
 */
void exibirConsumoMemoria() {
	printf("\nCONSUMO DE MEMORIA: %d ", TOTAL_CONSUMO_MEMORIA);
}

