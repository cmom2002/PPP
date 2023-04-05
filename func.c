#include "header.h"

/*----------------------------------------Ficheiro De Alunos----------------------------------------*/

void lerFicheiro_alunos(lista listal) {
    char *token;
    char line[TAM];

    FILE* file = fopen("Alunos.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
    }

    struct aluno a1;
    while (!feof(file)) {
        fgets(line, TAM, file);
        token = strtok(line, "-");

        int aux = 0;
        while (token != NULL) {
            if (aux == 0) {
                strcpy(a1.nome, token);
            }
            else if (aux == 1) {
                a1.ano = atoi(token);
            }
            else if (aux == 2) {
                strcpy(a1.turma, token);
            }
            else if (aux == 3) {
                a1.numero = atoi(token);
            }
            else if (aux == 4) {
                a1.saldo = atof(token);
            }
            else if (aux == 5) {
                a1.d.dia = lerData(token) -> dia;
                a1.d.mes = lerData(token) -> mes;
                a1.d.ano = lerData(token) -> ano;

                inserirAluno(listal, a1);
            }

            aux++;
            token = strtok(NULL, "-");
        }
    }
    fclose(file);
}

dat lerData(char *token) {
    dat d1;

    char *tokenAux;
    int dataAux = 0;

    tokenAux = strtok(token, "/");
    while (tokenAux != NULL) {
        if (dataAux == 0)
            d1 -> dia = atoi(tokenAux);
        else if (dataAux == 1)
            d1 -> mes = atoi(tokenAux);
        else
            d1 -> ano = atoi(tokenAux);

        dataAux++;
        tokenAux = strtok(NULL, "/\r\n");
    }

    return d1;
}

void escreverFicheiro_alunos(lista listal) {
    FILE *file;

    file = fopen("Alunos.txt", "w");

    if (file == NULL) {
        printf("Ocorreu um erro ao abrir o ficheiro de texto.\n");
        exit(1);
    }

    lista aux = listal -> prox;

    while(aux) {
        fprintf(file, "%s-", aux -> a.nome);
        fprintf(file, "%d-", aux -> a.ano);
        fprintf(file, "%s-", aux -> a.turma);
        fprintf(file, "%d-", aux -> a.numero);
        fprintf(file, "%.2lf-", aux -> a.saldo);
        fprintf(file, "%d/", aux -> a.d.dia);
        fprintf(file, "%d/", aux -> a.d.mes);
        fprintf(file, "%d\n", aux -> a.d.ano);

        aux = aux -> prox;
    }

    fclose(file);
}

/*----------------------------------------Ficheiro De Despesas----------------------------------------*/

void lerFicheiro_despesas(listaDesp listad){
    FILE *f = fopen("Despesas.txt", "r");
    char *token, line[TAM], data [TAM];

    struct despesa d;
    while(!feof(f)){
        int count = 0;
        fgets(line, TAM, f);
        token = strtok(line, ";");
        while(token != NULL){
            if(count == 0){
                d.numero = atoi(token);
            }
            else if(count == 1){
                strcpy(d.tipo, token);
            }
            else if(count == 2){
                d.quantidade = atoi(token);
            }
            else if(count == 3){
                d.preco = atof(token);
            }
            else if(count == 4){
                strcpy(data, token);
                d.d.dia = lerData(data) -> dia;
                d.d.mes = lerData(data) -> mes;
                d.d.ano = lerData(data) -> ano;
                inserirDespesa(listad, d);
            }
            token = strtok(NULL, ";\r\n");
            count++;
        }
    }
    fclose(f);

}
void escreverFicheiro_despesas(listaDesp listad){
    FILE  *f = fopen("Despesas.txt", "w");
    listaDesp aux = listad -> prox;

    while(aux){
        fprintf(f, "%d;%s;%d;%.2lf;%d/%d/%d\n", aux -> desp.numero, aux -> desp.tipo, aux -> desp.quantidade, aux -> desp.preco,aux -> desp.d.dia, aux -> desp.d.mes, aux -> desp.d.ano);
        aux = aux -> prox;
    }

    fclose(f);
}

/*----------------------------------------Ficheiro Do Bar----------------------------------------*/

int lerFicheiro_Bar(struct bar b[]){
    int num_consumiveis = 0;
    FILE *f = fopen("MenuBar.txt", "r");
    char line[TAM], *buffer;

    while(!feof(f)){
        fgets(line, TAM, f);
        buffer = strtok(line, ";");
        strcpy(b[num_consumiveis].nome, buffer);
        buffer = strtok(NULL, ";");
        b[num_consumiveis].quantidade = atoi(buffer);
        buffer = strtok(NULL, "\n\r");
        b[num_consumiveis].preco = atof(buffer);
        num_consumiveis++;
    }

    fclose(f);

    return num_consumiveis;
}

void escreveFicheiro_Bar(struct bar b[], int num){
    FILE *f = fopen("MenuBar.txt", "w");

    for(int i = 0; i < num - 1; i++){
        if(b[i].quantidade > 0)
            fprintf(f, "%s;%d;%0.2f\n", b[i].nome, b[i].quantidade, b[i].preco);
    }

    if(b[num -1].quantidade > 0)
        fprintf(f, "%s;%d;%0.2f", b[num -1].nome, b[num -1].quantidade, b[num -1].preco);

    fclose(f);
}

/*----------------------------------------Menu Do Bar----------------------------------------*/

void comprar_bar(lista listal, listaDesp listad, struct bar b[], int num){
    int compra, quantidade, aux = 0;

    do {
        printf("O que deseja comprar? ");
        scanf("%d", &compra);

        if(aux != 0)
            printf("A quantidade que deseja comprar é maior do que a quantidade disponível.\n");

        printf("Que quantide deseja comprar? ");
        scanf("%d", &quantidade);
        aux++;
    }while(b[compra - 1].quantidade < quantidade && b[compra - 1].quantidade < 0);

    lista aux1 = listal -> prox;
    struct despesa d;
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    while(aux1){
        if(aux1 -> a.numero == num){
            if(aux1 -> a.saldo < b[compra - 1].preco * quantidade)
                printf("Não tem saldo suficiente para efetuar o pagamento.\n");
            else {
                aux1 -> a.saldo -= b[compra - 1].preco * quantidade;
                b[compra - 1].quantidade -= quantidade;
                d.numero = aux1->a.numero;
                d.preco = b[compra - 1].preco * quantidade;
                d.quantidade = quantidade;
                strcpy(d.tipo, b[compra -1].nome);
                d.d.dia = ptm->tm_mday;
                d.d.mes = ptm->tm_mon + 1;
                d.d.ano = ptm->tm_year + 1900;

                inserirDespesa(listad, d);
            }
        }
        aux1 = aux1 -> prox;
    }
}

void menu_bar(lista listal, listaDesp listad, struct bar b[], int tam, int num){
    int fim = 0;
    do {
        printf("------------------Bar---------------------\n");
        for (int i = 0; i < tam; i++) {
            printf("%d-%s (%0.2f€)\n", i + 1, b[i].nome, b[i].preco);
        }
        printf("------------------------------------------\n");

        comprar_bar(listal, listad, b, num);
        escreveFicheiro_Bar(b, tam);

        printf("Deseja comprar mais alguma coisa? (1-Sim/0-Não) ");
        scanf("%d", &fim);
    }while(fim != 0);
}

/*----------------------------------------Adicionar Aluno à Lista Ligada----------------------------------------*/

int verifica_data(int dia, int mes, int ano, int count){
    if(count == 0)
        return 1;
    if(ano < 1950 || ano > 2003) {
        printf("Ano inválido!!\n");
        return 1;
    }
    if(dia < 1 || dia > 31){
        printf("Dia inválido!!\n");
        return 1;
    }
    if(mes < 1 || mes > 12){
        printf("Mês inválido!!\n");
        return 1;
    }
    if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31){
        printf("O mês %d não tem 31 dias!!\n", mes);
        return 1;
    }
    if(mes == 2 && ((ano % 4 != 0 && dia == 29) || dia > 28)){
        printf("O mês %d só tem 28 dias, a menos que seja bissexto!!\n", mes);
        return 1;
    }
    return 0;
}

void adicionarAluno(lista listal) {
    struct aluno a1;

    char nome[TAM];
    char *nomeAux;
    char temp;

    printf("Introduza o nome do aluno: ");
    scanf("%c", &temp);
    fgets(nome, sizeof(nome), stdin);

    nomeAux = strtok(nome, "\n");
    strcpy(a1.nome, nomeAux);

    printf("Introduza o ano do aluno: ");
    scanf("%d", &a1.ano);

    printf("Introduza a turma do aluno: ");
    scanf("%s", a1.turma);

    do{
        printf("Introduza o número do aluno: ");
        scanf("%d", &a1.numero);
    }while(validarInput(listal, a1.numero));

    printf("Introduza o saldo do aluno: ");
    scanf("%lf", &a1.saldo);

    char data[TAM], aux[TAM], *buffer;
    int dia = 0, mes = 0, ano = 0, count = 0;
    while(verifica_data(dia, mes, ano, count) == 1 || count == 0) {
        if(count != 0)
            printf("Introduza uma data de nascimento válida: ");
        else
            printf("Introduza a data de nascimento do aluno: ");

        scanf("%s", data);
        strcpy(aux, data);
        buffer = strtok(aux, "/");
        dia = atoi(buffer);
        buffer = strtok(NULL, "/");
        mes = atoi(buffer);
        buffer = strtok(NULL, "\n");
        ano = atoi(buffer);
        count ++;
    }

    a1.d.dia = dia;
    a1.d.mes = mes;
    a1.d.ano = ano;

    inserirAluno(listal, a1);
}

/*----------------------------------------Imprimir Aluno Por Saldo----------------------------------------*/

void ordenaSaldo(double *saldo, int tam){
    double aux;

    for(int i = 0; i < tam; i++){
        for(int j = i; j < tam ;  j++){
            if(saldo[i] < saldo[j]){
                aux = saldo[i];
                saldo[i] = saldo[j];
                saldo[j] = aux;
            }
        }
    }
}

bool verifica_saldo(const double *saldo, double sal, int tam){
    for(int i = 0; i < tam; i++){
        if(saldo[i] == sal)
            return false;
    }
    return true;
}

void imprimirPorSaldo(lista listal, double saldoReferencia) {
    lista aux = listal -> prox;
    double saldo[TAM];

    int i = 0;
    while(aux) {
        if (aux -> a.saldo < saldoReferencia && verifica_saldo(saldo, aux -> a.saldo, i)) {
            saldo[i] = aux -> a.saldo;
            i++;
        }
        aux = aux -> prox;
    }

    ordenaSaldo(saldo, i);

    for(int j = 0; j < i; j++){
        lista aux_aux = listal -> prox;

        while(aux_aux) {
            if (saldo[j] == aux_aux->a.saldo)
                printf("%s\n", aux_aux->a.nome);
            aux_aux = aux_aux -> prox;
        }
    }

    if (i == 0)
        printf("Não foram encontrados alunos com saldo inferior a %.2lf!\n", saldoReferencia);
}

/*----------------------------------------Imprimir Informação De Um Aluno----------------------------------------*/

void imprimirInformacao(lista listal, int numAluno) {
    lista aux = listal -> prox;

    while(aux) {
        if (numAluno == aux -> a.numero)
            printf("\nNome do aluno: %s\n"
                   "Ano matriculado: %d\n"
                   "Turma inscrito: %s\n"
                   "Saldo do aluno: %.2lf\n"
                   "Data de nascimento: %d/%d/%d\n\n", aux -> a.nome, aux -> a.ano, aux -> a.turma, aux -> a.saldo, aux -> a.d.dia, aux -> a.d.mes, aux -> a.d.ano);
        aux = aux -> prox;
    }
}

/*----------------------------------------Carregar Conta De Um Aluno----------------------------------------*/

void carregarConta(lista listal, int numAluno) {
    double carregamento;

    printf("Por favor, introduza a quantia com que deseja carregar a conta: ");
    scanf("%lf", &carregamento);

    lista aux = listal -> prox;

    while(aux) {
        if (numAluno == aux -> a.numero)
            aux -> a.saldo = aux -> a.saldo + carregamento;

        aux = aux -> prox;
    }

    printf("Cartão carregado com sucesso!\n");
}

//-------------------------------------Transferir saldo para outro aluno-----------------------------
void transfere_saldo(lista listal, int num1, int num2){
    lista aluno1 = verificarAluno(listal, num1);
    lista aluno2 = verificarAluno(listal, num2);

    double saldo;
    int opcao;
    do {
        printf("Que quantidade deseja tranferir: ");
        scanf("%lf", &saldo);
        if (saldo > aluno1->a.saldo) {
            printf("Saldo insuficiente\nQuer transferir outra quantidade?(1-sim/0-Não)");
            scanf("%d", &opcao);
        }
    }while(saldo > aluno1->a.saldo && opcao == 1);

    if(opcao == 1){
        aluno1->a.saldo -= saldo;
        aluno2->a.saldo += saldo;
    }
}

//----------------------------------------Menu Principal----------------------------------------

void menu() {
    printf("_________________________________________________________________\n"
           "| 1- Introduzir dados de um novo aluno;                         |\n"
           "| 2- Eliminar um aluno;                                         |\n"
           "| 3- Listar todos os alunos por ordem alfabética;               |\n"
           "| 4- Listar os alunos com saldo abaixo de um determinado valor; |\n"
           "| 5- Apresentar toda a informação de um determinado aluno;      |\n"
           "| 6- Efetuar uma despesa por um determinado aluno;              |\n"
           "| 7- Carregar a conta de um aluno com um valor;                 |\n"
           "| 8- Imprimir despesas de um determinado aluno;                 |\n"
           "| 9- Transferir saldo para outro aluno;                         |\n"
           "| 0 -Sair;                                                      |\n"
           "|_______________________________________________________________|\n"
           "Escolha uma opção: ");
}

int selecionarOperacao() {
    int operacao;

    menu();

    scanf("%d", &operacao);

    while (operacao < 0 || operacao > 9) {
        printf("Por favor, introduza uma opção válida: ");
        scanf("%d", &operacao);
    }

    return operacao;
}

void executarOperacao(lista listal, listaDesp listad, int operacao) {
    int numAluno = 0, numAluno1 = 0;
    double saldoRef;
    int tam;

    if (operacao == 0) {
        printf("A encerrar o programa...\n");
        exit(0);
    }
    else if (operacao == 1) {
        adicionarAluno(listal);
        printf("Aluno registado com sucesso.\n");
    }
    else if (operacao == 2) {
        printf("Por favor, introduza o número do aluno a eliminar: ");
        scanf("%d", &numAluno);
        eliminarAluno(listal, numAluno);
    }
    else if (operacao == 3) {
        printf("Alunos registados: \n");
        imprimirLista(listal);
    }
    else if (operacao == 4) {
        printf("Por favor, introduza o saldo de referência: ");
        scanf("%lf", &saldoRef);
        imprimirPorSaldo(listal, saldoRef);
    }
    else if (operacao == 5) {
        printf("Por favor, introduza o número do aluno a consultar informação: ");
        scanf("%d", &numAluno);

        if (validarInput(listal, numAluno) == true) {
            imprimirInformacao(listal, numAluno);
        }
        else {
            do {
                printf("Não foi encontrado nenhum aluno associado ao número introduzido!\nPor favor, introduza um número válido: ");
                scanf("%d", &numAluno);
            } while (validarInput(listal, numAluno) == false);

            imprimirInformacao(listal, numAluno);
        }
    }
    else if (operacao == 6){
        printf("Por favor, introduza o número de aluno: ");
        scanf("%d", &numAluno);

        struct bar b[100];
        tam = lerFicheiro_Bar(b);

        if (validarInput(listal, numAluno) == true) {
            menu_bar(listal, listad, b, tam, numAluno);
        }
        else {
            do {
                printf("Não foi encontrado nenhum aluno associado ao número introduzido!\nPor favor, introduza um número válido: ");
                scanf("%d", &numAluno);
            } while (validarInput(listal, numAluno) == false);

            menu_bar(listal, listad, b, tam, numAluno);
        }

    }
    else if (operacao == 7) {
        printf("Por favor, introduza o número do aluno que deseja carregar a conta: ");
        scanf("%d", &numAluno);

        if (validarInput(listal, numAluno) == true) {
            carregarConta(listal, numAluno);
        }
        else {
            do {
                printf("Não foi encontrado nenhum aluno associado ao número introduzido!\nPor favor, introduza um número válido: ");
                scanf("%d", &numAluno);
            } while (validarInput(listal, numAluno) == false);

            carregarConta(listal, numAluno);
        }
    }
    else if(operacao == 8){
        printf("Por favor, introduza o número do aluno a que deseja consultar as despesas: ");
        scanf("%d", &numAluno);

        if (validarInput(listal, numAluno) == true) {
            imprimirListaDespesas(listad, numAluno);
        }
        else {
            do {
                printf("Não foi encontrado nenhum aluno associado ao número introduzido!\nPor favor, introduza um número válido: ");
                scanf("%d", &numAluno);
            } while (validarInput(listal, numAluno) == false);

            imprimirListaDespesas(listad, numAluno);
        }
    }
    else if(operacao == 9){

        do {
            printf("Por favor, introduza o número do aluno que vai enviar o dinheiro: ");
            scanf("%d", &numAluno);
        }while (validarInput(listal, numAluno) == false);

        do {
            printf("Por favor, introduza o número do aluno que vai receber o dinheiro: ");
            scanf("%d", &numAluno1);
        }while (validarInput(listal, numAluno1) == false);
        transfere_saldo(listal, numAluno, numAluno1);

    }
    escreverFicheiro_alunos(listal);
    escreverFicheiro_despesas(listad);
}

int inputContinuacao() {
    int continuar;

    printf("Deseja efetuar mais alguma operação?(1-Sim/0-Não) ");
    scanf("%d", &continuar);

    while (continuar < 0 || continuar > 1) {
        printf("Por favor, introduza uma opção válida.(1-Sim/0-Não) ");
        scanf("%d", &continuar);
    }

    return continuar;
}

void continuarOperacoes(lista listal, listaDesp listad) {
    bool ciclo = true;
    int continuar;
    int oper;

    continuar = inputContinuacao();

    do {
        if (continuar == 0) {
            printf("A encerrar o programa...\n");
            escreverFicheiro_alunos(listal);
            escreverFicheiro_despesas(listad);
            ciclo = false;
        }
        else if (continuar == 1) {
            oper = selecionarOperacao();
            executarOperacao(listal, listad, oper);
            continuar = inputContinuacao();
        }
    } while (ciclo);
}

bool validarInput(lista listal, int numAluno) {
    lista aux = listal -> prox;

    while (aux) {
        if (numAluno == aux -> a.numero) {
            return true;
        }

        aux = aux -> prox;
    }

    return false;
}
