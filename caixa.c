#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "hub.h"
#include "servidor.h"
#include "main.h"


// Função que recebe o produto e quantidade a ser adicionada na compra *Lógica provisória que será alterada em breve
void iniciar_venda() {
    setlocale(LC_ALL, "portuguese");
    char produto[1];
    int quantidade;

    printf("FRENTE DE CAIXA - VENDA \n\n");
    printf("\n");
    printf("Informe o nome ou código do produto à ser adicionado: \n");
    scanf("%s", &produto);
    printf("\n");
    printf("Informe a quantidade à ser adicionada: \n");
    scanf("%d", &quantidade);
    printf("\n");
    printf("Foram adicionadas %d unidade(s) de %s. \n\n", quantidade, produto);
};

int caixa() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; // Variável global declarada em main.c. Só está presente aqui para fins de compreensão do código, pois o próprio compilador já a interpreta como "0" ao ser iniciado.

    do {
        // Exibição inicial da aplicação
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
                iniciar_venda(); // Chama a função iniciar_venda()
                break; //Encerra o loop
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
