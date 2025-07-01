#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "processo.h"
 
// Função auxiliar para verificar se um número é potência de dois
int eh_potencia_de_dois(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main() {
    int tam_mem_fisica, tam_pagina, tam_max_processo;
    do {
        printf("Tamanho da memória física (bytes): ");
        scanf("%d", &tam_mem_fisica);
        if (!eh_potencia_de_dois(tam_mem_fisica)) {
            printf("O tamanho da memória física deve ser uma potência de dois!\n");
        }
    } while (!eh_potencia_de_dois(tam_mem_fisica));
    do {
        printf("Tamanho da página/quadro (bytes): ");
        scanf("%d", &tam_pagina);
        if (!eh_potencia_de_dois(tam_pagina)) {
            printf("O tamanho da página deve ser uma potência de dois!\n");
        }
    } while (!eh_potencia_de_dois(tam_pagina));
    do {
        printf("Tamanho máximo de um processo (bytes): ");
        scanf("%d", &tam_max_processo);
        if (!eh_potencia_de_dois(tam_max_processo)) {
            printf("O tamanho máximo do processo deve ser uma potência de dois!\n");
        }
    } while (!eh_potencia_de_dois(tam_max_processo));

    inicializar_memoria(tam_mem_fisica, tam_pagina);
    inicializar_processos(tam_max_processo, tam_pagina);

    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Visualizar memória física\n");
        printf("2. Criar processo\n");
        printf("3. Visualizar tabela de páginas de um processo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                visualizar_memoria();
                break;
            case 2:
                criar_processo_interativo();
                break;
            case 3:
                visualizar_tabela_paginas_interativo();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    liberar_memoria();
    liberar_processos();
    return 0;
} 