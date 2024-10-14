#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hub.h"
#include "caixa.h"
#include "main.h"


// Função para exibir o banco de dados dos produtos
void exibir_estoque() {
    FILE *arquivo = fopen("estoque.txt", "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque. \n\n");
        return;
    };

    char linha[100];
    printf("SERVIDOR - GESTÃO DE ESTOQUE - LISTA DE PRODUTOS: \n\n");
    /*printf("%s %s %s %s \n", "Quantidade", "Nome", "Preço Unitário", "Unidade");
    printf("--------------------------------------------------------- \n");*/
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha); // Exibe cada linha presente no arquivo
    };
    printf("\n");
    printf("--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Função para adicionar produtos ao estoque *Provisório
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
        printf("Operação cancelada. \n");
        return; // Encerra o programa *Provisório
    }

    printf("Digite o nome do produto à ser adicionado: ");
    scanf(" %[^\n]", nome); // Lê caracteres de nova linha
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    printf("Digite o preço unitário: ");
    scanf("%f", &valor);
    printf("Digite o tipo de unidade (Kg ou Un): ");
    scanf("%s", unidade);

    // Adiciona o produto ao arquivo
    fprintf(arquivo, "%-10d%-20s%-15.2f%-10s\n", quantidade, nome, valor, unidade);
    printf("Produto adicionado ao estoque! \n");

    fclose(arquivo);
};

// Função para remover um produto do estoque
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
        printf("Operação cancelada.\n");
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
        printf("Produto não encontrado no estoque. \n");
    };

    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo temporário
    remove("estoque.txt");
    rename("temp.txt", "estoque.txt");
};

// Função para gestão do estoque
void estoque() {
    setlocale(LC_ALL, "portuguese");

    do {
        printf("SERVIDOR - GESTÃO DE ESTOQUE \n\n");
        printf("1. Exibir estoque \n");
        printf("2. Adicionar produto \n");
        printf("3. Remover produto \n\n");
        printf("0. Voltar ao menu anterior \n\n");
        printf("Escolha uma opção: ");
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
                printf("Opção inválida! Tente novamente. \n\n");
        };
    } while (selecao != 0);
};

int servidor() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; // Variável global declarada em main.c. Só está presente aqui para fins de compreensão do código, pois o próprio compilador já a interpreta como "0" ao ser iniciado.

    do {
        //Exibição inicial da aplicação
        printf("SERVIDOR \n\n");
        printf("1. Gestão de estoque \n");
        printf("2. Fornecedores \n");
        printf("3. Relatório do dia \n\n");
        printf("0. Sair \n\n");
        printf("Informe a opção desejada: \n");
        scanf("%d", &selecao);

        //Condição para seleção de opções
        switch (selecao) {
            case 1:
                system("cls"); //Limpar todo conteúdo presente na tela
                estoque(); //Chama a função estoque()
                break; //Encerra o loop
            case 2:
                system("cls");
                printf("Fornecedores selecionado. \n\n"); //*Provisório;
                break;
            case 3:
                system("cls");
                printf("Relatório do dia selecionado. \n\n"); //*Provisório;
                break;
            case 0:
                system("cls");
                hub(); // Retorna à tela inicial de hub.c.
                break;
            default:
                system("cls");
                printf("Opção inválida! Tente novamente. \n\n");
        };
    } while (selecao != 0);
};
