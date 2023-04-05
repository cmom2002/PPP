#include "header.h"

lista inicializarListaAlunos() {
    lista aux;

    struct aluno a1 = {"", 0, "", 0, 0, 0, 0, 0};

    aux = (lista)malloc(sizeof(no));

    if (aux != NULL) {
        aux -> a = a1;
        aux -> prox = NULL;
    }

    return aux;
}

void inserirAluno(lista listal, struct aluno a1) {
    lista noLista, ant, inutil;

    noLista = (lista)malloc(sizeof(no));

    if (noLista != NULL) {
        noLista -> a = a1;
        procurarAluno_nome(listal, a1.nome, &ant, &inutil);
        noLista -> prox = ant -> prox;
        ant -> prox = noLista;
    }
}

void procurarAluno_nome(lista listal, char *nome, lista *ant, lista *atual) {
    *ant = listal;
    *atual = listal -> prox;

    while((*atual) != NULL && strcmp((*atual) -> a.nome, nome) < 0) {
        *ant = *atual;
        *atual = (*atual) -> prox;
    }

    if ((*atual) != NULL && strcmp((*atual) -> a.nome, nome) != 0)
        *atual = NULL;
}

void procurarAluno_numero(lista listal, int numero, lista *ant, lista *atual) {
    *ant = listal;
    *atual = listal -> prox;

    while((*atual) != NULL && (*atual) -> a.numero != numero) {
        *ant = *atual;
        *atual = (*atual) -> prox;
    }

    if ((*atual) != NULL && (*atual) -> a.numero != numero)
        *atual = NULL;
}

lista verificarAluno(lista listal, int numero) {
    lista aux = listal -> prox;

    while(aux) {
        if (aux -> a.numero == numero) {
            return aux;
        }
        aux = aux -> prox;
    }
    return 0;
}

void eliminarAluno(lista listal, int numero) {
    lista ant, atual;

    procurarAluno_numero(listal, numero, &ant, &atual);

    if (atual != NULL) {
        ant -> prox = atual -> prox;
        free(atual);
        printf("Aluno removido com sucesso!\n");
    }
    else
        printf("O aluno não existe!\n");
}

void imprimirLista(lista listal) {
    lista aux = listal -> prox;
    while(aux) {
        printf("%s %d\n", aux -> a.nome, aux->a.numero);
        aux = aux -> prox;
    }
}