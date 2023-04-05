#include "header.h"

int main() {
    lista lista_aluno;
    listaDesp listad;

    lista_aluno = inicializarListaAlunos();
    listad = inicializarListaDespesas();

    lerFicheiro_alunos(lista_aluno);
    lerFicheiro_despesas(listad);
    executarOperacao(lista_aluno, listad, selecionarOperacao());

    continuarOperacoes(lista_aluno, listad);

    return 0;
}