#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "hub.h"
#include "caixa.h"
#include "main.h"

int servidor() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; //Variável global declarada em main.c. Só está presente aqui para fins de compreensão do código, pois o próprio compilador já a interpreta como "0" ao ser iniciado.

    //Exibição inicial da aplicação de servidor.
    printf("SERVIDOR\n");
    printf("\n");
    printf("\n");
    printf("1. Estoque \n");
    printf("2. Fornecedores \n");
    printf("3. Relatório do dia \n");
    printf("\n");
    printf("0. Sair \n");
    printf("\n");

    //Condição para seleção de opções. *Estrutura provisória que será alterada em breve.
    while (selecao != 1 || 2 || 3 || 0) {
        //solicitação que ficará em loop caso o número digitado seja diferente de 1, 2, 3 ou 0.
        printf("Informe a opção desejada: \n");
        scanf("%d", &selecao);

        //Condições. *Estruturas provisórias que serão alteradas em breve.
        if (selecao == 1) {
            system("cls"); //Limpar todo conteúdo presente na tela;
            printf("Estoque selecionado. \n"); //*Provisório;
            return 0; // Encerra o programa.
        } else if (selecao == 2) {
            system("cls");
            printf("Fornecedores selecionado. \n"); //*Provisório;
            return 0;
        } else if (selecao == 3) {
            system("cls");
            printf("Relatório do dia selecionado. \n"); //*Provisório;
            return 0;
        } else if (selecao == 0) {
            system("cls");
            hub(); // Retorna à tela inicial de hub.c.
            return 0;
        } else {
            printf("Número inválido.\n"); // Caso o valor digitado seja diferente da condição.
        };
    };

}
