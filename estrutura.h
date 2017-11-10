/**
Alunos:
Allan Gonçalves da Cruz
Elson Bento dos Santos
====================================================================================================
	Definir estrutura para armazenar as linhas do arquivo. (nao sei se crio um struct para armazenas tabela de simbolos e erros encontrados)
	Baseado na estrutura disponibilizado em:
    1 - https://programacaodescomplicada.wordpress.com/complementar/
    2 - https://www.youtube.com/watch?v=cIpZ8YUh0Yo
    3 - http://www.cprogressivo.net/2013/03/typedef-Como-declarar-seus-proprios-tipos-em-C.html
====================================================================================================
*/

/**
 * Struct que armazena a informacoes do dado da lista.
 */
typedef struct linha {
    char conteudo[200];
    int linha;
} Linha;


/**
 * Struct que armazena os elementos da lista, de acordo com o tipo do dado.
 */
typedef struct elemento {
    struct elemento *ant;
    Linha dados;
    struct elemento *prox;
} Elem;

typedef struct elemento* Lista;

/**
 * Cria a lista.
 *
 * @return Lista* lista
 */
Lista* criaLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));

    if (lista != NULL) {
        *lista = NULL;
    }

    return lista;
}

/**
 * Remove todos os elementos da lista.
 *
 * @param Lista* lista
 */
void liberaLista(Lista* lista) {
    if (lista != NULL) {
        Elem* no;

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
 * @param Lista* lista
 * @param Linha lin
 * @return int
 */
int insereListaFinal(Lista* lista, Linha lin) {
    if (lista == NULL) {
        return 0;
    }

    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) {
        return 0;
    }

    no->dados = lin;
    no->prox = NULL;

    // lista vazia: insere início
    if ((*lista) == NULL) {
        no->ant = NULL;
        *lista = no;
    } else {
        Elem *aux;
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
int insereListaInicio(Lista* lista, Linha lin) {
    if (lista == NULL) {
        return 0;
    }

    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));

    if (no == NULL) {
        return 0;
    }

    no->dados = lin;
    no->prox = (*lista);
    no->ant = NULL;

    //lista não vazia: apontar para o anterior!
    if (*lista != NULL) {
        (*lista)->ant = no;
    }

    *lista = no;

    return 1;
}

/**
 * Remove o item da lista de acordo com o numero da linha informado.
 *
 * @param Lista* lista
 * @param int nuLinha
 * @return int
 */
int removeLista(Lista* lista, int nuLinha) {
    if (lista == NULL) {
        return 0;
    }

    // lista vazia
    if ((*lista) == NULL) {
        return 0;
    }

    Elem *no = *lista;
    while (no != NULL && no->dados.linha != nuLinha) {
        no = no->prox;
    }

    // não encontrado
    if(no == NULL) {
        return 0;
    }

    // remover o primeiro?
    if (no->ant == NULL) {
        *lista = no->prox;
    } else {
        no->ant->prox = no->prox;
    }

    // não é o último?
    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    }

    free(no);
    return 1;
}

/**
 * Remove o item no inicio da lista.
 *
 * @param Lista* lista
 * @return int
 */
int removeListaInicio(Lista* lista) {
    if (lista == NULL) {
        return 0;
    }

    // lista vazia
    if ((*lista) == NULL) {
        return 0;
    }

    Elem *no = *lista;
    *lista = no->prox;

    if(no->prox != NULL) {
        no->prox->ant = NULL;
    }

    free(no);
    return 1;
}

/**
 * Remove o item no final da lista.
 *
 * @param Lista* lista
 * @return int
 */
int removeListaFinal(Lista* lista) {
    if(lista == NULL) {
        return 0;
    }

    // lista vazia
    if ((*lista) == NULL) {
        return 0;
    }

    Elem *no = *lista;

    while(no->prox != NULL) {
        no = no->prox;
    }

    // remover o primeiro e único
    if(no->ant == NULL) {
        *lista = no->prox;
    } else {
        no->ant->prox = NULL;
    }

    free(no);
    return 1;
}

/**
 * Retorna o total de itens que compoen a lista.
 *
 * @param Lista* lista
 * @return int cont
 */
int tamanhoLista(Lista* lista) {
    if (lista == NULL) {
        return 0;
    }

    int cont = 0;
    Elem* no = *lista;

    while (no != NULL) {
        cont++;
        no = no->prox;
    }

    return cont;
}

/**
 * Verifica se a lista esta vazia.
 *
 * @param Lista* lista
 * @return int
 */
int listaVazia(Lista* lista) {
    if (lista == NULL) {
        return 1;
    }

    if (*lista == NULL) {
        return 1;
    }

    return 0;
}

/**
 * Imprime os itens da lista.
 *
 * @param Lista* lista
 */
void imprimeLista(Lista* lista) {
    if (lista == NULL) {
        return;
    }

    Elem* no = *lista;

    while (no != NULL) {
        printf("Linha: %d \n", no->dados.linha);
        printf("Conteudo: %s \n", no->dados.conteudo);
        printf("Total caracter linha: %d \n", strlen(no->dados.conteudo));
        printf("------------------------------------------\n");
        no = no->prox;
    }
}


