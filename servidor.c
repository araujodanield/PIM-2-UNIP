#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hub.h"
#include "caixa.h"
#include "main.h"


// Função global para remoção de itens nas aplicações de estoque, fornecedores e relatório
void remover_item(const char* arquivo_origem, const char* arquivo_temp, const char* item_nome, const char* tipo_item, int* encontrado) {
    FILE *origem = fopen(arquivo_origem, "r");
    FILE *temp = fopen(arquivo_temp, "w");

    if (!origem || !temp) {
        printf("Erro ao manipular arquivos.\n");
        return;
    };

    *encontrado = 0;  // Inicializa como não encontrado

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), origem)) {
        // Se a linha não contém o item a ser removido, repete essa linha no arquivo temporário
        if (strstr(linha, item_nome) == NULL) {
            fputs(linha, temp);
        } else {
            *encontrado = 1;  // Marca como encontrado
            printf("%s %s removido!\n", tipo_item, item_nome);
        };
    };

    fclose(origem);
    fclose(temp);
};

//

// ESTOQUE:

// Função para exibir o arquivo estoque.txt
void exibir_estoque() {
    setlocale(LC_ALL, "portuguese");

    FILE *arquivo = fopen("estoque.txt", "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque. \n\n");
        return;
    };

    printf("SERVIDOR - GESTÃO DE ESTOQUE - LISTA DE PRODUTOS: \n\n");
    printf("%-12s %-20s %-15s %-10s \n", "Quantidade", "Nome", "Preço Unitário", "Unidade");
    printf("--------------------------------------------------------- \n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha); // Exibe cada linha presente no arquivo
    };
    printf("--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Função para adicionar produtos ao estoque
void adicionar_produto() {
    char nome[50], unidade[3];
    int quantidade;
    float valor;

    printf("Deseja adicionar um produto? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada.\n");
        return;
    };

    printf("Digite o nome do produto: ");
    scanf("%[^\n]", nome);
    getchar();
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    printf("Digite o preço unitário: ");
    scanf("%f", &valor);
    printf("Digite o tipo de unidade (Kg ou Un): ");
    scanf("%s", unidade);

    void escrever_produto(FILE* arquivo) {
        fprintf(arquivo, "%-12d %-20s %-15.2f %-10s\n", quantidade, nome, valor, unidade);
        printf("Produto adicionado ao estoque!\n");
    };

    manipular_arquivo("estoque.txt", "a", escrever_produto);
};

// Função para remover produto do estoque
void remover_produto() {
    char nome_produto[50];
    int encontrado = 0;

    printf("\nDeseja realmente remover um produto? ");
    if (validar_resposta() == 'N') return;

    printf("\nDigite o nome do produto que deseja remover: ");
    scanf("%[^\n]", nome_produto);
    getchar();

    // Remove o produto
    remover_item("estoque.txt", "estoque_temp.txt", nome_produto, "Produto", &encontrado);

    // Se o item for encontrado o arquivo é atualizado
    if (encontrado) {
        if (remove("estoque.txt") == 0 && rename("estoque_temp.txt", "estoque.txt") == 0) {
            printf("Arquivo atualizado com sucesso!\n");
        } else {
            printf("Erro ao atualizar o arquivo!\n");
        };
    } else {
        remove("estoque_temp.txt");
        printf("Produto não encontrado!\n");
    };
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

// FORNECEDORES:

// Função para exibir o arquivo fornecedores.txt
void exibir_fornecedores() {
    setlocale(LC_ALL, "portuguese");

    FILE *arquivo = fopen("fornecedores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores. \n\n");
        return;
    };

    printf("SERVIDOR - GESTÃO DE FORNECEDORES - LISTA DE FORNECEDORES: \n\n");
    printf("%-25s %-15s \n", "Nome Fantasia", "CNPJ");
    printf("--------------------------------------------------------- \n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    };
    printf("--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Função para adicionar fornecedores
void adicionar_fornecedor() {
    char nome_fantasia[50], cnpj[15];

    printf("Deseja adicionar um fornecedor? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada.\n");
        return;
    };

    printf("Digite o nome fantasia do fornecedor: ");
    scanf("%[^\n]", nome_fantasia);
    getchar();
    printf("Digite o CNPJ do fornecedor (apenas números): ");
    scanf("%s", &cnpj);

    void escrever_produto(FILE* arquivo) {
        fprintf(arquivo, "%-25s %-15s\n", nome_fantasia, cnpj);
        printf("Fornecedor adicionado com sucesso! \n");
    };

    manipular_arquivo("fornecedores.txt", "a", escrever_produto);
};

// Função para remover um fornecedor
void remover_fornecedor() {
    char nome_fantasia[50];
    int encontrado = 0;

    printf("\nDeseja realmente remover um fornecedor da lista? ");
    if (validar_resposta() == 'N') return;

    printf("\nDigite o nome fantasia do fornecedor que deseja remover: ");
    scanf("%[^\n]", nome_fantasia);
    getchar();

    remover_item("fornecedores.txt", "fornecedores_temp.txt", nome_fantasia, "Fornecedor", &encontrado);

    // Se o item for encontrado o arquivo é atualizado
    if (encontrado) {
        if (remove("fornecedores.txt") == 0 && rename("fornecedores_temp.txt", "fornecedores.txt") == 0) {
            printf("Arquivo atualizado com sucesso!\n");
        } else {
            printf("Erro ao atualizar o arquivo!\n");
        };
    } else {
        remove("fornecedores_temp.txt");
        printf("Fornecedor não encontrado!\n");
    };
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

// RELATÓRIOS

// Função para exibir o conteúdo do arquivo vendas.txt
void exibir_relatorio() {
    setlocale(LC_ALL, "portuguese");

    FILE *arquivo = fopen("vendas.txt", "r"); // Abre o arquivo em modo de leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque. \n\n");
        return;
    };


    printf("--------------------------------------------------------- \n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha); // Exibe cada linha presente no arquivo
    };
    printf("\n--------------------------------------------------------- \n\n");

    fclose(arquivo);
};

// Função para resetar o arquivo vendas.txt
void limpar_relatorio() {
    printf("\nDeseja realmente limpar o relatório? ");
    if (validar_resposta() == 'N') {
        printf("Operação cancelada.\n");
        return;
    }

    // Abre o arquivo em modo de escrita e então o fecha, apagando todo o conteúdo e deixando-o em branco
    FILE *arquivo = fopen("vendas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fclose(arquivo);
    printf("Relatório limpo com sucesso!\n");
};

// Menu para gestão de relatório
void relatorio() {
    do {
        printf("SERVIDOR - RELATORIO DO DIA \n\n");
        printf("1. Exibir relatorio \n");
        printf("2. Limpar relatorio \n\n");
        printf("0. Voltar ao menu anterior \n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &selecao);

        switch (selecao) {
            case 1:
                system("cls"); // Limpa a tela
                exibir_relatorio();
                break;
            case 2:
                system("cls");
                limpar_relatorio();
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

//MENU SERVIDOR
int servidor() {
    do {
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
                estoque();
                break;
            case 2:
                system("cls");
                fornecedores();
                break;
            case 3:
                system("cls");
                relatorio();
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
