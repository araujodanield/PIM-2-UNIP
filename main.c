#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "servidor.h"
#include "caixa.h"
#include "hub.h"


int selecao; // Variável global utilizada por todos os arquivos do programa, para fins de seleção de opções na interface visual

int main() {

    hub(); // Ao iniciar o programa o compilador executará o código presente na função hub() do arquivo hub.c

};
