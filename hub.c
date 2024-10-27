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
        printf("Bem vindo! Por favor, selecione uma das aplicações: \n\n");
        printf("1. Servidor \n");
        printf("2. Frente de Caixa \n\n");
        printf("0. Desligar \n\n");
        printf("Informe a opção desejada: \n");
        scanf("%d", &selecao);

        // Condição para seleção de opções
        switch (selecao) {
            case 1:
                system("cls"); // Limpa todo conteúdo presente na tela
                servidor(); // Chama a função servidor() em servidor.c
                break; // Encerra o loop
            case 2:
                system("cls");
                caixa(); // Chama a função caixa() em caixa.c
                break;
            case 0:
                system("cls");
                printf("Aplicativo encerrado. \n"); // Informa o encerramento do programa
                return; // Encerra o programa
            default:
                system("cls");
                printf("Opção inválida! Tente novamente. \n\n");
        };
    } while (selecao != 0);
};
