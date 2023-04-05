#include "header.h"

listaDesp inicializarListaDespesas() {
    listaDesp aux;

    struct despesa d1 = {0, "", 0, 0, 0, 0, 0};

    aux = (listaDesp)malloc(sizeof(noDesp));

    if (aux != NULL) {
        aux -> desp = d1;
        aux -> prox = NULL;
    }

    return aux;
}

void procurarDespesa(listaDesp listad, int num, listaDesp *ant, listaDesp *atual) {
    *ant = listad;
    *atual = listad -> prox;

    while((*atual) != NULL && (*atual) -> desp.numero < num) {
        *ant = *atual;
        *atual = (*atual) -> prox;
    }

    if ((*atual) != NULL && (*atual) -> desp.numero != num)
        *atual = NULL;
}

void inserirDespesa(listaDesp listad, struct despesa d1) {
    listaDesp noListaD, ant, inutil;

    noListaD = (listaDesp)malloc(sizeof(noDesp));

    if (noListaD != NULL) {
        noListaD -> desp = d1;
        procurarDespesa(listad, d1.numero, &ant, &inutil);
        noListaD -> prox = ant -> prox;
        ant -> prox = noListaD;
    }
}

void imprimirListaDespesas(listaDesp listad, int numAluno) {
    listaDesp aux = listad -> prox;

    while(aux) {
        if(aux->desp.numero == numAluno)
            printf("\nNúmero do aluno: %d\n"
                   "Tipo de produto: %s\n"
                   "Quantidade comprada: %d\n"
                   "Preço da compra: %.2lf\n"
                   "Data de emissão: %d/%d/%d\n", aux -> desp.numero, aux -> desp.tipo, aux -> desp.quantidade, aux -> desp.preco, aux -> desp.d.dia, aux -> desp.d.mes, aux -> desp.d.ano);
        aux = aux -> prox;
    }

    printf("\n");
}
