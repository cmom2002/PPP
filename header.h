#ifndef PROJETOV2_HEADER_H
#define PROJETOV2_HEADER_H

#endif //PROJETOV2_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TAM 50

typedef struct data {
    int dia;
    int mes;
    int ano;
} data;

typedef data *dat;

struct aluno {
    char nome[TAM];
    int ano;
    char turma[TAM];
    int numero;
    double saldo;
    struct data d;
};

typedef struct no {
    struct aluno a;
    struct no *prox;
} no;

typedef no *lista;

struct despesa {
    int numero;
    char tipo[TAM];
    int quantidade;
    data d;
    double preco;
};

typedef struct noDesp {
    struct despesa desp;
    struct noDesp *prox;
} noDesp;

typedef noDesp *listaDesp;

struct bar {
    char nome[TAM];
    int quantidade;
    double preco;
};


//-------------Lista Ligada de Despesas-------------------------------------------
listaDesp inicializarListaDespesas();

void procurarDespesa(listaDesp listad, int num, listaDesp *ant, listaDesp *atual);

void inserirDespesa(listaDesp listad, struct despesa d1);

void imprimirListaDespesas(listaDesp listad, int numAluno);

//-------------Lista Ligada de Nomes---------------------------------------------
lista inicializarListaAlunos();

void inserirAluno(lista listal, struct aluno a1);

void procurarAluno_nome(lista listal, char *nome, lista *ant, lista *atual);

void procurarAluno_numero(lista listal, int numero, lista *ant, lista *atual);

lista verificarAluno(lista listal, int numero);

void eliminarAluno(lista listal, int numero);

void imprimirLista(lista listal);

//-------------------Ler e Escrever em ficheiros-----------------------------------
void lerFicheiro_alunos(lista listal);

void escreverFicheiro_alunos(lista listal);

void lerFicheiro_despesas(listaDesp listad);

void escreverFicheiro_despesas(listaDesp listad);

int lerFicheiro_Bar(struct bar b[]);

void escreveFicheiro_Bar(struct bar b[], int num);

//--------------------Menu Bar-----------------------------------------------------
void comprar_bar(lista listal, listaDesp listad, struct bar b[], int num);

void menu_bar(lista listal, listaDesp listad, struct bar b[], int tam, int num);

//-------------------Opcoes---------------------------------------------
void adicionarAluno(lista listal);


void ordenaSaldo(double *saldo, int tam);

bool verifica_saldo(const double *saldo, double sal, int tam);

void imprimirPorSaldo(lista listal, double saldoReferencia);


void imprimirInformacao(lista listal, int numAluno);

void carregarConta(lista listal, int numAluno);

void transfere_saldo(lista listal, int num1, int num2);

//----------------------Menu--------------------------------------------------
void menu();

int selecionarOperacao();

void executarOperacao(lista listal, listaDesp listad, int operacao);

int inputContinuacao();

void continuarOperacoes(lista listal, listaDesp listad);

bool validarInput(lista listal, int numAluno);

//-------------------Funções verificação data----------------------------------
dat lerData(char *token);

int verifica_data(int dia, int mes, int ano, int count);