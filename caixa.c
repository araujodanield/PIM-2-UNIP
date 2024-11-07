#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>
#include "hub.h"
#include "servidor.h"
#include "main.h"


// Estrutura para itens do carrinho
typedef struct {
    char nome[50];
    float quantidade;
    float preco_unitario;
    float total;
} ItemCarrinho;

// Variáveis globais do carrinho
ItemCarrinho carrinho[100];
int qtd_itens_carrinho = 0;
float valor_total = 0.0;

// FUNÇÕES

void resetar_carrinho() {
    qtd_itens_carrinho = 0;
    valor_total = 0.0;
};

// Função para identificar nome do produto em estoque.txt
int buscar_produto(const char* nome_produto, float* quantidade, float* preco, char* unidade) {
    int encontrado = 0;

    // Função interna que compara o nome fornecido pelo usuário com os presentes em estoque.txt
    void ler_produto(FILE* arquivo) {
        char nome[50];
        float qtd;
        float preco_unit;
        char unidade_tmp[10];

        while (fgets(linha, sizeof(linha), arquivo)) {
            if (sscanf(linha, "%f %[^0-9] %f %s", &qtd, nome, &preco_unit, unidade_tmp) == 4) {
                // Remove espaços em branco do final do nome e permite a identificação de nomes com espaçamento (Ex: Arroz Integral)
                int tamanho = strlen(nome);
                while (tamanho > 0 && isspace(nome[tamanho-1])) {
                    nome[tamanho-1] = '\0';
                    tamanho--;
                };

                // Realiza a comparação dos nomes
                if (strcasecmp(nome_produto, nome) == 0) {
                    *quantidade = qtd;
                    *preco = preco_unit;
                    strcpy(unidade, unidade_tmp);
                    encontrado = 1;
                    break;
                };
            };
        };
    };

    manipular_arquivo("estoque.txt", "r", ler_produto);
    return encontrado;
};

// Função que cria uma linha com os dados do produto adicionado, para ser exibido no resumo da venda
void adicionar_ao_carrinho(const char* nome_produto, float quantidade, float preco_unitario) {
    strcpy(carrinho[qtd_itens_carrinho].nome, nome_produto);
    carrinho[qtd_itens_carrinho].quantidade = quantidade;
    carrinho[qtd_itens_carrinho].preco_unitario = preco_unitario;
    carrinho[qtd_itens_carrinho].total = quantidade * preco_unitario;
    valor_total += carrinho[qtd_itens_carrinho].total;
    qtd_itens_carrinho++;
};

// Função para remoção de itens antes de finalizar a venda
void remover_item_carrinho() {
    if (qtd_itens_carrinho == 0) {
        printf("Carrinho vazio! \n\n");
        return;
    };

    printf("\nDeseja realmente remover um produto? ");
    if (validar_resposta() == 'N') {
        system("cls");
        printf("Operação cancelada.\n\n");
        return;
    };

    printf("\nProdutos no carrinho:\n");
    for (int i = 0; i < qtd_itens_carrinho; i++) {
        printf("- %s (Quantidade: %.3f)\n", carrinho[i].nome, carrinho[i].quantidade);
    };

    char nome_produto[50];

    printf("\nDigite o nome do produto que deseja remover: ");
    scanf(" %[^\n]", nome_produto);

    // Caso o nome fornecido corresponda à um dos itens do carrinho, o valor daquele produto é subtraído do total
    for (int i = 0; i < qtd_itens_carrinho; i++) {
        if (strcasecmp(nome_produto, carrinho[i].nome) == 0) {
            valor_total -= carrinho[i].total;

            // Move todos os itens uma posição para trás para organização da lista de resumo de venda
            for (int j = i; j < qtd_itens_carrinho - 1; j++) {
                carrinho[j] = carrinho[j + 1];
            };
            qtd_itens_carrinho--;
            printf("Produto removido com sucesso! \n\n");
            return;
        };
    };
    printf("Produto não encontrado no carrinho! \n\n");
};

// Função que registra a venda finalizada no arquivo vendas.txt
void finalizar_venda() {
    static int numero_venda = 1;

    // Função interna que realiza a gravação dos dados da venda no txt
    void salvar_venda(FILE* arquivo) {
        fprintf(arquivo, "\nVenda Nº %d \n\n", numero_venda++);
        fprintf(arquivo, "%-15s %-10.3s %-8.2s %-10s\n\n", "Produto", "Qtd", "Preço", "Total");

        // Imprime cada um dos produtos registrados durante a venda
        for (int i = 0; i < qtd_itens_carrinho; i++) {
            fprintf(arquivo, "%-15s %-10.3f R$%-8.2f R$%-8.2f\n", carrinho[i].nome, carrinho[i].quantidade, carrinho[i].preco_unitario, carrinho[i].total);

            float qtd_atual;
            float preco;
            char unidade[10];

            // Atualiza a quantidade do produto disponível no estoque
            if (buscar_produto(carrinho[i].nome, &qtd_atual, &preco, unidade)) {
                float nova_qtd = qtd_atual - carrinho[i].quantidade;

                // Atualiza o arquivo estoque.txt
                FILE* estoque = fopen("estoque.txt", "r");
                FILE* temp = fopen("estoque_temp.txt", "w");

                char nome_produto[50];
                float qtd, preco_unit;
                char unidade_tmp[10];
                char linha_temp[256];

                // Repetição da lógica utilizada em buscar_produto() para identificar corretamente a linha do produto
                while (fgets(linha, sizeof(linha), estoque)) {
                    strcpy(linha_temp, linha);

                    if (sscanf(linha_temp, "%f %[^0-9] %f %s", &qtd, nome_produto, &preco_unit, unidade_tmp) == 4) {
                        int tamanho = strlen(nome_produto);
                        while (tamanho > 0 && isspace(nome_produto[tamanho-1])) {
                            nome_produto[tamanho-1] = '\0';
                            tamanho--;
                        };

                        // Compara os nomes presentes no carrinho com os presentes em estoque.txt
                        if (strcasecmp(carrinho[i].nome, nome_produto) == 0) {
                            // Verifica se a quantidade do produto é um número inteiro ou fracionado e grava as casas decimais apenas em valores fracionados
                            if (fmod(nova_qtd, 1.0) == 0.0) {
                                fprintf(temp, "%-12.0f %-20s %-15.2f %-10s\n", nova_qtd, carrinho[i].nome, preco, unidade);
                            } else {
                                fprintf(temp, "%-12.3f %-20s %-15.2f %-10s\n", nova_qtd, carrinho[i].nome, preco, unidade);
                            };
                        } else {
                            fputs(linha, temp);
                        };
                    } else {
                        fputs(linha, temp);
                    };
                };

                fclose(estoque);
                fclose(temp);
                remove("estoque.txt");
                rename("estoque_temp.txt", "estoque.txt");
            };
        };

        fprintf(arquivo, "\nVALOR TOTAL: R$ %.2f\n", valor_total);
        fprintf(arquivo, "------------------------------------------------\n");
    };

    manipular_arquivo("vendas.txt", "a", salvar_venda);
    system("cls");
    printf("Venda finalizada com sucesso! \n\n");
    resetar_carrinho();
};

// Função que exibe o resumo da venda
void exibir_carrinho() {
    do {
        system("cls");
        printf("\nRESUMO DA COMPRA: \n\n");
        printf("%-15s %-10s %-10s %-10s\n\n", "Produto", "Qtd", "Preço", "Total");

        for (int i = 0; i < qtd_itens_carrinho; i++) {
            printf("%-15s %-10.3f R$%-8.2f R$%-8.2f\n",
                   carrinho[i].nome, carrinho[i].quantidade,
                   carrinho[i].preco_unitario, carrinho[i].total);
        };

        printf("\nVALOR TOTAL: R$ %.2f\n", valor_total);
        printf("------------------------------------------------ \n\n");
        printf("1 - Finalizar compra\n2 - Remover produto\n0 - Cancelar compra\n");
        printf("\nDigite a opção desejada: ");

        scanf("%d", &selecao);
        getchar();

        switch (selecao) {
            case 1:
                finalizar_venda();
                return;
            case 2:
                if (qtd_itens_carrinho > 0) {
                    remover_item_carrinho();
                    printf("\nPressione Enter para continuar...");
                    getchar();
                } else {
                    printf("\nCarrinho vazio!\n");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                };
                break;
            case 0:
                system("cls");
                printf("Venda cancelada. \n\n");
                resetar_carrinho();
                caixa();
                return;
            default:
                printf("\nOpção inválida!\n");
                printf("Pressione Enter para continuar...");
                getchar();
        };
    } while (1);
};

// Função para verificação e adição de produtos durante o processo de venda
void iniciar_venda() {
    printf("Deseja iniciar uma nova venda? ");
    if (validar_resposta() == 'N') {
        system("cls");
        printf("Operação cancelada.\n\n");
        return;
    };

    do {
        char nome_produto[50];
        float qtd_estoque;
        float preco;
        char unidade[10];
        float quantidade;
        int quantidade_valida = 0;  // Verificação para saber se a quantidade é válida

        do {
            printf("\nDigite o nome do produto: ");
            scanf("%[^\n]", nome_produto);
            getchar();

            if (!buscar_produto(nome_produto, &qtd_estoque, &preco, unidade)) {
                printf("Produto não encontrado. Tente novamente. \n");
            };
        } while (!buscar_produto(nome_produto, &qtd_estoque, &preco, unidade));

        // Loop para verificar a quantidade
        while (!quantidade_valida) {
            printf("Digite a quantidade desejada (Para valores fracionados utilize vírgula): ");
            scanf("%f", &quantidade);
            getchar();

            // Verifica se a quantidade adicionada é maior que a disponível em estoque
            if (quantidade > qtd_estoque) {
                printf("Quantidade indisponível no estoque. Quantidade máxima disponível: %.3f %s \n\n", qtd_estoque, unidade);
                printf("Deseja tentar novamente? ");
                if (validar_resposta() == 'N') { // Se a resposta for não, pergunta se quer adicionar outro produto

                    printf("Deseja adicionar outro produto? ");
                    if (validar_resposta() == 'N') { // Se a resposta for não, e já houver produtos no carrinho, exibe o resumo da compra
                        if (qtd_itens_carrinho > 0) {
                            exibir_carrinho();
                        } else { // Cancela a operação e retorna ao menu inicial de caixa.c
                            system("cls");
                            printf("Operação cancelada.\n\n");
                            caixa();
                        };
                        return;
                    };
                    break;  // Sai do loop de quantidade para permitir escolher outro produto
                };
            } else {
                quantidade_valida = 1;  // Quantidade se torna válida, permitindo prosseguir
                adicionar_ao_carrinho(nome_produto, quantidade, preco);
                printf("\nProduto adicionado ao carrinho!\n");
            };
        };

        // Caso um produto seja adicionado com sucesso, pergunta se deseja adicionar mais
        if (quantidade_valida) {
            printf("\nDeseja adicionar mais produtos? ");
        };
    } while (validar_resposta() == 'S');

    // Ao final das interações, se houver mais de 0 itens no carrinho, exibe o resumo da compra
    if (qtd_itens_carrinho > 0) {
        exibir_carrinho();
    };
};

int caixa() {
    setlocale(LC_ALL, "portuguese");

    do {
        printf("FRENTE DE CAIXA \n\n");
        printf("\n");
        printf("1. Iniciar nova venda \n\n");
        printf("0. Sair \n\n");
        printf("Informe a opção desejada: \n");
        scanf("%d", &selecao);

        // Condição para seleção de opções
        switch (selecao) {
            case 1:
                system("cls"); // Limpar todo conteúdo presente na tela
                iniciar_venda();
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
