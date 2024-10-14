#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hub.h"
#include "caixa.h"
#include "main.h"


// Fun��o para exibir o banco de dados dos produtos
void exibir_estoque() {
    FILE *arquivo = fopen("estoque.txt", "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque. \n\n");
        return;
    };

    char linha[100];
    printf("SERVIDOR - GEST�O DE ESTOQUE - LISTA DE PRODUTOS: \n\n");
    /*printf("%s %s %s %s \n", "Quantidade", "Nome", "Pre�o Unit�rio", "Unidade");
    printf("--------------------------------------------------------- \n");*/
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha); // Exibe cada linha presente no arquivo
    };
    printf("\n");
    printf("--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Fun��o para adicionar produtos ao estoque *Provis�rio
void adicionar_produto() {
    FILE *arquivo = fopen("estoque.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o(s) arquivo(s). \n\n");
        return;
    };

    char nome[50], unidade[3];
    int quantidade;
    float valor;
    char confirmacao;

    printf("Deseja adicionar um produto? (S/N): ");
    scanf("%c", &confirmacao);
    if (confirmacao == 'N' || confirmacao == 'n') {
        printf("Opera��o cancelada. \n");
        return; // Encerra o programa *Provis�rio
    }

    printf("Digite o nome do produto � ser adicionado: ");
    scanf(" %[^\n]", nome); // L� caracteres de nova linha
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    printf("Digite o pre�o unit�rio: ");
    scanf("%f", &valor);
    printf("Digite o tipo de unidade (Kg ou Un): ");
    scanf("%s", unidade);

    // Adiciona o produto ao arquivo
    fprintf(arquivo, "%-10d%-20s%-15.2f%-10s\n", quantidade, nome, valor, unidade);
    printf("Produto adicionado ao estoque! \n");

    fclose(arquivo);
};

// Fun��o para remover um produto do estoque
void remover_produto() {
    FILE *arquivo = fopen("estoque.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o(s) arquivo(s). \n\n");
        return;
    };

    char nome[50], nome_arquivo[50], unidade[3];
    int quantidade;
    float valor;
    int encontrado = 0;
    char confirmacao;

    printf("Deseja remover um produto? (S/N): ");
    scanf("%c", &confirmacao);
    if (confirmacao == 'N' || confirmacao == 'n') {
        printf("Opera��o cancelada.\n");
        return;
    };

    printf("Digite o nome do produto que deseja remover: ");
    scanf(" %[^\n]", nome);

    // Copia os dados do arquivo original, exceto o produto a ser removido
    while (fscanf(arquivo, "%d\t%[^\t]\t%f\t%s\n", &quantidade, nome_arquivo, &valor, unidade) != EOF) {
        if (strcmp(nome_arquivo, nome) == 0) {
            printf("Produto removido com sucesso! \n");
            encontrado = 1;
        } else {
            fprintf(temp, "%-10d%-20s%-15.2f%-10s \n", quantidade, nome_arquivo, valor, unidade);
        };
    };

    if (!encontrado) {
        printf("Produto n�o encontrado no estoque. \n");
    };

    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo tempor�rio
    remove("estoque.txt");
    rename("temp.txt", "estoque.txt");
};

// Fun��o para gest�o do estoque
void estoque() {
    setlocale(LC_ALL, "portuguese");

    do {
        printf("SERVIDOR - GEST�O DE ESTOQUE \n\n");
        printf("1. Exibir estoque \n");
        printf("2. Adicionar produto \n");
        printf("3. Remover produto \n\n");
        printf("0. Voltar ao menu anterior \n\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &selecao);

        switch (selecao) {
            case 1:
                system("cls"); // Limpa a tela
                exibir_estoque();
                break;
            case 2:
                system("cls");
                adicionar_produto();
                break;
            case 3:
                system("cls");
                remover_produto();
                break;
            case 0:
                system("cls");
                servidor();
                break;
            default:
                system("cls");
                printf("Op��o inv�lida! Tente novamente. \n\n");
        };
    } while (selecao != 0);
};

int servidor() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; // Vari�vel global declarada em main.c. S� est� presente aqui para fins de compreens�o do c�digo, pois o pr�prio compilador j� a interpreta como "0" ao ser iniciado.

    do {
        //Exibi��o inicial da aplica��o
        printf("SERVIDOR \n\n");
        printf("1. Gest�o de estoque \n");
        printf("2. Fornecedores \n");
        printf("3. Relat�rio do dia \n\n");
        printf("0. Sair \n\n");
        printf("Informe a op��o desejada: \n");
        scanf("%d", &selecao);

        //Condi��o para sele��o de op��es
        switch (selecao) {
            case 1:
                system("cls"); //Limpar todo conte�do presente na tela
                estoque(); //Chama a fun��o estoque()
                break; //Encerra o loop
            case 2:
                system("cls");
                printf("Fornecedores selecionado. \n\n"); //*Provis�rio;
                break;
            case 3:
                system("cls");
                printf("Relat�rio do dia selecionado. \n\n"); //*Provis�rio;
                break;
            case 0:
                system("cls");
                hub(); // Retorna � tela inicial de hub.c.
                break;
            default:
                system("cls");
                printf("Op��o inv�lida! Tente novamente. \n\n");
        };
    } while (selecao != 0);
};
