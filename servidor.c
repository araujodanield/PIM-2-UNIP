#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "hub.h"
#include "caixa.h"
#include "main.h"

int servidor() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; //Vari�vel global declarada em main.c. S� est� presente aqui para fins de compreens�o do c�digo, pois o pr�prio compilador j� a interpreta como "0" ao ser iniciado.

    //Exibi��o inicial da aplica��o de servidor.
    printf("SERVIDOR\n");
    printf("\n");
    printf("\n");
    printf("1. Estoque \n");
    printf("2. Fornecedores \n");
    printf("3. Relat�rio do dia \n");
    printf("\n");
    printf("0. Sair \n");
    printf("\n");

    //Condi��o para sele��o de op��es. *Estrutura provis�ria que ser� alterada em breve.
    while (selecao != 1 || 2 || 3 || 0) {
        //solicita��o que ficar� em loop caso o n�mero digitado seja diferente de 1, 2, 3 ou 0.
        printf("Informe a op��o desejada: \n");
        scanf("%d", &selecao);

        //Condi��es. *Estruturas provis�rias que ser�o alteradas em breve.
        if (selecao == 1) {
            system("cls"); //Limpar todo conte�do presente na tela;
            printf("Estoque selecionado. \n"); //*Provis�rio;
            return 0; // Encerra o programa.
        } else if (selecao == 2) {
            system("cls");
            printf("Fornecedores selecionado. \n"); //*Provis�rio;
            return 0;
        } else if (selecao == 3) {
            system("cls");
            printf("Relat�rio do dia selecionado. \n"); //*Provis�rio;
            return 0;
        } else if (selecao == 0) {
            system("cls");
            hub(); // Retorna � tela inicial de hub.c.
            return 0;
        } else {
            printf("N�mero inv�lido.\n"); // Caso o valor digitado seja diferente da condi��o.
        };
    };

}
