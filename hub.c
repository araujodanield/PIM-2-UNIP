#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "servidor.h"
#include "caixa.h"
#include "main.h"

int hub() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; //Vari�vel global declarada em main.c. S� est� presente aqui para fins de compreens�o do c�digo, pois o pr�prio compilador j� a interpreta como "0" ao ser iniciado.

    //Exibi��o do Hub.
    printf("Bem vindo! Por favor, selecione uma das aplica��es abaixo: \n");
    printf("\n");
    printf("1. Servidor \n");
    printf("2. Frente de Caixa \n");
    printf("\n");
    printf("0. Encerrar \n");
    printf("\n");

    //Condi��o para sele��o de op��es. *Estrutura provis�ria que ser� alterada em breve.
    while (selecao != 1 || 2 || 0) {
        //solicita��o que ficar� em loop enquanto o n�mero digitado for diferente dos esperados em while().
        printf("Digite o n�mero desejado e tecle ENTER: \n");
        scanf("%d", &selecao);

        //Condi��es
        if (selecao == 1) {
            system("cls"); //Limpar todo conte�do presente na tela;
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
            printf("N�mero inv�lido.\n"); // Caso o valor digitado seja diferente da condi��o.
        };
    };

}
