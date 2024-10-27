#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "servidor.h"
#include "caixa.h"
#include "hub.h"

int selecao; // Variável global utilizada por funções para fins de seleção de opções na interface visual
char linha[150]; // Variável global utilizada por funções que utilizam laços de repetição para leitura ou exibição de itens dos arquivos txt

// Função global para manipular arquivos txt
void manipular_arquivo(const char* nome_arquivo, const char* modo, void (*funcao)(FILE*)) {
    FILE* arquivo = fopen(nome_arquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    };
    funcao(arquivo);
    fclose(arquivo);
};

// Função global para confirmação de ação
char validar_resposta() {
    char resposta;

    do {
        printf("Digite S para Sim ou N para Não: ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta); // Converte o caractere digitado, permitindo sua leitura tanto em maiúsculo quanto minúsculo

        while (getchar() != '\n');

        if (resposta != 'S' && resposta != 'N') {
            printf("Resposta inválida. Tente novamente.\n");
        };
    } while (resposta != 'S' && resposta != 'N');

    return resposta;
};

int main() {

    hub(); // Ao iniciar o programa o compilador executará o código presente na função hub() do arquivo hub.c
};

