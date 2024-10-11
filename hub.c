#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "servidor.h"
#include "caixa.h"
#include "main.h"

int hub() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; //Variável global declarada em main.c. Só está presente aqui para fins de compreensão do código, pois o próprio compilador já a interpreta como "0" ao ser iniciado.

    //Exibição do Hub.
    printf("Bem vindo! Por favor, selecione uma das aplicações abaixo: \n");
    printf("\n");
    printf("1. Servidor \n");
    printf("2. Frente de Caixa \n");
    printf("\n");
    printf("0. Encerrar \n");
    printf("\n");

    //Condição para seleção de opções. *Estrutura provisória que será alterada em breve.
    while (selecao != 1 || 2 || 0) {
        //solicitação que ficará em loop enquanto o número digitado for diferente dos esperados em while().
        printf("Digite o número desejado e tecle ENTER: \n");
        scanf("%d", &selecao);

        //Condições
        if (selecao == 1) {
            system("cls"); //Limpar todo conteúdo presente na tela;
            servidor(); //Iniciar o arquivo servidor.c;
            return 0; //Encerrar hub.c.
        } else if (selecao == 2) {
            system("cls");
            caixa(); //Iniciar o arquivo caixa.c;
            return 0;
        } else if (selecao == 0) {
            system("cls");
            printf("Aplicativo encerrado. \n"); // Informa o encerramento do programa.
            return 0; // Encerra o programa.
        } else {
            printf("Número inválido.\n"); // Caso o valor digitado seja diferente da condição.
        };
    };

}
