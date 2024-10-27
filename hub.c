#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "servidor.h"
#include "caixa.h"
#include "main.h"


int hub() {
    setlocale(LC_ALL, "portuguese");

    do {
        printf("Bem vindo! Por favor, selecione uma das aplica��es: \n\n");
        printf("1. Servidor \n");
        printf("2. Frente de Caixa \n\n");
        printf("0. Desligar \n\n");
        printf("Informe a op��o desejada: \n");
        scanf("%d", &selecao);

        // Condi��o para sele��o de op��es
        switch (selecao) {
            case 1:
                system("cls"); // Limpa todo conte�do presente na tela
                servidor(); // Chama a fun��o servidor() em servidor.c
                break; // Encerra o loop
            case 2:
                system("cls");
                caixa(); // Chama a fun��o caixa() em caixa.c
                break;
            case 0:
                system("cls");
                printf("Aplicativo encerrado. \n"); // Informa o encerramento do programa
                return; // Encerra o programa
            default:
                system("cls");
                printf("Op��o inv�lida! Tente novamente. \n\n");
        };
    } while (selecao != 0);
};
