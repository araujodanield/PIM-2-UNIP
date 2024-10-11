#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "hub.h"
#include "servidor.h"
#include "main.h"


// Função que recebe o produto e quantidade a ser adicionada na compra *Lógica provisória que será alterada em breve
void iniciarVenda () {
    char produto[1];
    int quantidade;

    printf("FRENTE DE CAIXA\n");
    printf("\n");
    printf("\n");
    printf("Informe o nome ou código do produto à ser adicionado: \n");
    scanf("%s", &produto);
    printf("\n");
    printf("Informe a quantidade à ser adicionada: \n");
    scanf("%d", &quantidade);
    printf("\n");
    printf("Foram adicionadas %d unidade(s) de %s\n", quantidade, produto);
};

int caixa() {
    setlocale(LC_ALL, "portuguese");
    selecao = 0; //Variável global declarada em main.c. Só está presente aqui para fins de compreensão do código, pois o próprio compilador já a interpreta como "0" ao ser iniciado.

    //Exibição inicial da aplicação de caixa.
    printf("FRENTE DE CAIXA\n");
    printf("\n");
    printf("\n");
    printf("1. Iniciar nova venda \n");
    printf("\n");
    printf("0. Sair \n");
    printf("\n");

    //Condição para seleção de opções. *Estrutura provisória que será alterada em breve.
    while (selecao != 1 || 0) {
        //solicitação que ficará em loop caso o número digitado seja diferente de 1 ou 0.
        printf("Informe a opção desejada: \n");
        scanf("%d", &selecao);

        //Condições. *Estruturas provisórias que serão alteradas em breve.
        if (selecao == 1) {
            system("cls"); //Limpar todo conteúdo presente na tela;
            iniciarVenda(); //Iniciar a função iniciarVenda();
            return 0; // Encerrar o programa após o fim de iniciarVenda().
        }  else if (selecao == 0) {
            system("cls");
            hub(); // Retorna à tela inicial de hub.c.
            return 0; // Encerra o programa.
        } else {
            printf("Opção inválida.\n"); // Caso o valor digitado seja diferente da condição.
        };
    };

}

