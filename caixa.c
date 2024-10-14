#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "hub.h"
#include "servidor.h"
#include "main.h"


// Fun��o que recebe o produto e quantidade a ser adicionada na compra *L�gica provis�ria que ser� alterada em breve
void iniciar_venda() {
    setlocale(LC_ALL, "portuguese");
    char produto[1];
    int quantidade;

    printf("FRENTE DE CAIXA - VENDA \n\n");
    printf("\n");
    printf("Informe o nome ou c�digo do produto � ser adicionado: \n");
    scanf("%s", &produto);
    printf("\n");
    printf("Informe a quantidade � ser adicionada: \n");
    scanf("%d", &quantidade);
    printf("\n");
    printf("Foram adicionadas %d unidade(s) de %s. \n\n", quantidade, produto);
};

int caixa() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; // Vari�vel global declarada em main.c. S� est� presente aqui para fins de compreens�o do c�digo, pois o pr�prio compilador j� a interpreta como "0" ao ser iniciado.

    do {
        // Exibi��o inicial da aplica��o
        printf("FRENTE DE CAIXA \n\n");
        printf("\n");
        printf("1. Iniciar nova venda \n\n");
        printf("0. Sair \n\n");
        printf("Informe a op��o desejada: \n");
        scanf("%d", &selecao);

        // Condi��o para sele��o de op��es
        switch (selecao) {
            case 1:
                system("cls"); // Limpar todo conte�do presente na tela
                iniciar_venda(); // Chama a fun��o iniciar_venda()
                break; //Encerra o loop
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
