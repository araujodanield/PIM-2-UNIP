#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hub.h"
#include "caixa.h"
#include "main.h"


char validar_resposta() {
    char resposta;

    do {
        printf("Digite S para Sim ou N para Não: ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta); // Aceita o caractere definido tanto em maiúsculo quanto minúsculo
        if (resposta != 'S' && resposta != 'N') {
            printf("Resposta inválida. Tente novamente.\n");
        };
    } while (resposta != 'S' && resposta != 'N');

    return resposta;
};

//
//

// ESTOQUE:

// Função para exibir o banco de dados dos produtos
void exibir_estoque() {
    setlocale(LC_ALL, "portuguese");
    char linha[150];

    FILE *arquivo = fopen("estoque.txt", "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque. \n\n");
        return; // Sai da função
    };

    printf("SERVIDOR - GESTÃO DE ESTOQUE - LISTA DE PRODUTOS: \n\n");
    printf("%-12s %-20s %-15s %-10s \n", "Quantidade", "Nome", "Preço Unitário", "Unidade");
    printf("--------------------------------------------------------- \n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha); // Exibe cada linha presente no arquivo
    };
    printf("\n");
    printf("--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Função para adicionar produtos ao estoque
void adicionar_produto() {
    setlocale(LC_ALL, "portuguese");

    char nome[50], unidade[3];
    int quantidade;
    float valor;

    FILE *arquivo = fopen("estoque.txt", "a"); // Abre o arquivo em modo de anexar conteúdo ao original
    if (arquivo == NULL) {
        printf("Erro ao abrir o(s) arquivo(s). \n\n");
        return;
    };

    // Verificação de prosseguimento usando a função validar_resposta()
    printf("Deseja adicionar um produto? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada. \n");
        fclose(arquivo);
        return;
    };

    printf("Digite o nome do produto à ser adicionado: ");
    getchar();
    scanf("%[^\n]", nome); // Permite a adição de nomes que contenham espaço. Ex: Feijão Carioca
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    printf("Digite o preço unitário: ");
    scanf("%f", &valor);
    printf("Digite o tipo de unidade (Kg ou Un): ");
    scanf("%s", unidade);

    // Adiciona o produto ao arquivo
    fprintf(arquivo, "\n%-12d %-20s %-15.2f %-10s", quantidade, nome, valor, unidade);
    printf("Produto adicionado ao estoque! \n");

    fclose(arquivo);
};

// Função para remover um produto do estoque
void remover_produto() {
    setlocale(LC_ALL, "portuguese");

    char nome_produto[50];
    char linha[150];
    int encontrado = 0;

    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n\n");
        return;
    };

    FILE *arquivo_temp = fopen("estoque_temp.txt", "w"); // Cria um arquivo temporário para salvar as alterações
    if (arquivo_temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n\n");
        fclose(arquivo);
        return;
    };

    // Verificação
    printf("Deseja remover um produto? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada.\n");
        fclose(arquivo);
        fclose(arquivo_temp);
        return;
    };

    // Solicitar o nome do produto a ser removido
    do {
        printf("Digite o nome do produto que deseja remover: ");
        getchar(); // Limpa o buffer do compilador
        scanf("%[^\n]", nome_produto);

        rewind(arquivo); // Reinicia a leitura do arquivo do início
        encontrado = 0;

        while (fgets(linha, sizeof(linha), arquivo)) {
            // Verifica se o nome do produto está na linha
            if (strstr(linha, nome_produto) != NULL) {
                encontrado = 1; // Produto encontrado
                printf("Produto %s removido do estoque!\n", nome_produto);
            } else {
                // Remove linhas em branco ao gravar no arquivo temporário
                if (strlen(linha) > 1) { // Evita gravar linhas vazias
                    fputs(linha, arquivo_temp);
                };
            };
        };

        if (!encontrado) {
            printf("Produto não encontrado. Tente novamente.\n");
        };
    } while (!encontrado);

    // Fecha os arquivos
    fclose(arquivo);
    fclose(arquivo_temp);

    // Substitui o arquivo original pelo temporário
    remove("estoque.txt");
    rename("estoque_temp.txt", "estoque.txt");

    printf("Remoção concluída!\n");
};

// Menu para gestão do estoque
void estoque() {

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

//
//

// FORNECEDORES:

// Função para exibir a lista de fornecedores
void exibir_fornecedores() {
    setlocale(LC_ALL, "portuguese");

    char linha[150];

    FILE *arquivo = fopen("fornecedores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores. \n\n");
        return;
    };

    printf("SERVIDOR - GESTÃO DE FORNECEDORES - LISTA DE FORNECEDORES: \n\n");
    printf("%-25s %-15s \n", "Nome Fantasia", "CNPJ");
    printf("--------------------------------------------------------- \n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha); // Exibe cada linha presente no arquivo
    };
    printf("--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Função para adicionar fornecedores
void adicionar_fornecedor() {
    setlocale(LC_ALL, "portuguese");

    char nome_fantasia[50], cnpj[15];

    FILE *arquivo = fopen("fornecedores.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores. \n\n");
        return;
    };

    // Verificação
    printf("Deseja adicionar um fornecedor? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada. \n");
        fclose(arquivo);
        return;
    };

    printf("Digite o nome fantasia do fornecedor: ");
    getchar();
    scanf("%[^\n]", nome_fantasia);

    printf("Digite o CNPJ do fornecedor (apenas números): ");
    scanf("%s", cnpj);

    // Adiciona o fornecedor ao arquivo
    fprintf(arquivo, "%-25s %-15s\n", nome_fantasia, cnpj);
    printf("Fornecedor adicionado com sucesso! \n");

    fclose(arquivo);
};

// Função para remover um fornecedor
void remover_fornecedor() {
    setlocale(LC_ALL, "portuguese");

    char nome_fantasia[50];
    char linha[150];
    int encontrado = 0;

    FILE *arquivo = fopen("fornecedores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores. \n\n");
        return;
    };

    FILE *temp = fopen("fornecedores_temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n\n");
        fclose(arquivo);
        return;
    };

    // Verificação
    printf("Deseja remover um fornecedor? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada.\n");
        fclose(arquivo);
        fclose(temp);
        return;
    };

    do {
        printf("Digite o nome fantasia do fornecedor que deseja remover: ");
        getchar();
        scanf("%[^\n]", nome_fantasia);

        rewind(arquivo);
        encontrado = 0;

        while (fgets(linha, sizeof(linha), arquivo)) {
            // Verifica se o nome do produto está na linha
            if (strstr(linha, nome_fantasia) != NULL) {
                encontrado = 1; // Produto encontrado
                printf("Fornecedor %s removido da lista!\n", nome_fantasia);
            } else {
                if (strlen(linha) > 1) {
                    fputs(linha, temp);
                };
            };
        };

        if (!encontrado) {
            printf("Fornecedor não encontrado. Tente novamente.\n");
        };
    } while (!encontrado);

    // Fecha os arquivos
    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo temporário
    remove("fornecedores.txt");
    rename("fornecedores_temp.txt", "fornecedores.txt");

    printf("Remoção concluída!\n");
};

// Menu para gestão de fornecedores
void fornecedores() {
    do {
        printf("SERVIDOR - GESTÃO DE FORNECEDORES \n\n");
        printf("1. Exibir fornecedores \n");
        printf("2. Adicionar fornecedor \n");
        printf("3. Remover fornecedor \n\n");
        printf("0. Voltar ao menu anterior \n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &selecao);

        switch (selecao) {
            case 1:
                system("cls"); // Limpa a tela
                exibir_fornecedores();
                break;
            case 2:
                system("cls");
                adicionar_fornecedor();
                break;
            case 3:
                system("cls");
                remover_fornecedor();
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

//
//

//MENU SERVIDOR

int servidor() {
    selecao = 0; // Variável global declarada em main.c. Só está presente aqui para fins de compreensão do código, pois o próprio compilador já a interpreta como "0" ao ser iniciado.

    do {
        //Exibição inicial da aplicação
        printf("SERVIDOR \n\n");
        printf("1. Gestão de Estoque \n");
        printf("2. Gestão de Fornecedores \n");
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
                fornecedores(); //*Provisório;
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
