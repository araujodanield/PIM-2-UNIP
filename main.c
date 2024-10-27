#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "servidor.h"
#include "caixa.h"
#include "hub.h"

int selecao; // Vari�vel global utilizada por fun��es para fins de sele��o de op��es na interface visual
char linha[150]; // Vari�vel global utilizada por fun��es que utilizam la�os de repeti��o para leitura ou exibi��o de itens dos arquivos txt

// Fun��o global para manipular arquivos txt
void manipular_arquivo(const char* nome_arquivo, const char* modo, void (*funcao)(FILE*)) {
    FILE* arquivo = fopen(nome_arquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    };
    funcao(arquivo);
    fclose(arquivo);
};

// Fun��o global para confirma��o de a��o
char validar_resposta() {
    char resposta;

    do {
        printf("Digite S para Sim ou N para N�o: ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta); // Converte o caractere digitado, permitindo sua leitura tanto em mai�sculo quanto min�sculo

        while (getchar() != '\n');

        if (resposta != 'S' && resposta != 'N') {
            printf("Resposta inv�lida. Tente novamente.\n");
        };
    } while (resposta != 'S' && resposta != 'N');

    return resposta;
};

int main() {

    hub(); // Ao iniciar o programa o compilador executar� o c�digo presente na fun��o hub() do arquivo hub.c
};

