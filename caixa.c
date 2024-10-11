#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "hub.h"
#include "servidor.h"
#include "main.h"


// Fun��o que recebe o produto e quantidade a ser adicionada na compra *L�gica provis�ria que ser� alterada em breve
void iniciarVenda () {
    char produto[1];
    int quantidade;

    printf("FRENTE DE CAIXA\n");
    printf("\n");
    printf("\n");
    printf("Informe o nome ou c�digo do produto � ser adicionado: \n");
    scanf("%s", &produto);
    printf("\n");
    printf("Informe a quantidade � ser adicionada: \n");
    scanf("%d", &quantidade);
    printf("\n");
    printf("Foram adicionadas %d unidade(s) de %s\n", quantidade, produto);
};

int caixa() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; //Vari�vel global declarada em main.c. S� est� presente aqui para fins de compreens�o do c�digo, pois o pr�prio compilador j� a interpreta como "0" ao ser iniciado.

    //Exibi��o inicial da aplica��o de caixa.
    printf("FRENTE DE CAIXA\n");
    printf("\n");
    printf("\n");
    printf("1. Iniciar nova venda \n");
    printf("\n");
    printf("0. Sair \n");
    printf("\n");

    //Condi��o para sele��o de op��es. *Estrutura provis�ria que ser� alterada em breve.
    while (selecao != 1 || 0) {
        //solicita��o que ficar� em loop caso o n�mero digitado seja diferente de 1 ou 0.
        printf("Informe a op��o desejada: \n");
        scanf("%d", &selecao);

        //Condi��es. *Estruturas provis�rias que ser�o alteradas em breve.
        if (selecao == 1) {
            system("cls"); //Limpar todo conte�do presente na tela;
            iniciarVenda(); //Iniciar a fun��o iniciarVenda();
            return 0; // Encerrar o programa ap�s o fim de iniciarVenda().
        }  else if (selecao == 0) {
            system("cls");
            hub(); // Retorna � tela inicial de hub.c.
            return 0; // Encerra o programa.
        } else {
            printf("Op��o inv�lida.\n"); // Caso o valor digitado seja diferente da condi��o.
        };
    };

}

