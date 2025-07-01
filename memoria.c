#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *memoria_fisica = NULL;
static int *quadros_livres = NULL;
static int tamanho_memoria = 0;
static int tamanho_pagina = 0;
static int num_quadros = 0;

void inicializar_memoria(int tamanho_fisico, int tamanho_pagina_param) {
    tamanho_memoria = tamanho_fisico;
    tamanho_pagina = tamanho_pagina_param;
    num_quadros = tamanho_memoria / tamanho_pagina;
    memoria_fisica = (unsigned char*) malloc(tamanho_memoria * sizeof(unsigned char));
    quadros_livres = (int*) malloc(num_quadros * sizeof(int));
    if (!memoria_fisica || !quadros_livres) {
        printf("Erro ao alocar memória física!\n");
        exit(1);
    }
    memset(memoria_fisica, 0, tamanho_memoria);
    for (int i = 0; i < num_quadros; i++) {
        quadros_livres[i] = 1;
    }
}

void visualizar_memoria() {
    if (!memoria_fisica || !quadros_livres) {
        printf("Memória não inicializada!\n");
        return;
    }
    int livres = 0;
    for (int i = 0; i < num_quadros; i++) {
        if (quadros_livres[i]) livres++;
    }
    float percentual_livre = 100.0f * livres / num_quadros;
    printf("\nMemória Física: %d bytes, %d quadros de %d bytes\n", tamanho_memoria, num_quadros, tamanho_pagina);
    printf("Quadros livres: %d/%d (%.2f%% livre)\n", livres, num_quadros, percentual_livre);
    for (int i = 0; i < num_quadros; i++) {
        printf("Quadro %2d: %s | ", i, quadros_livres[i] ? "LIVRE " : "OCUPADO");
        for (int j = 0; j < tamanho_pagina; j++) {
            printf("%02X ", memoria_fisica[i * tamanho_pagina + j]);
        }
        printf("\n");
    }
}

void liberar_memoria() {
    if (memoria_fisica) free(memoria_fisica);
    if (quadros_livres) free(quadros_livres);
    memoria_fisica = NULL;
    quadros_livres = NULL;
    tamanho_memoria = 0;
    tamanho_pagina = 0;
    num_quadros = 0;
}

int contar_quadros_livres() {
    int livres = 0;
    for (int i = 0; i < num_quadros; i++) {
        if (quadros_livres[i]) livres++;
    }
    return livres;
}

int alocar_quadro_livre() {
    for (int i = 0; i < num_quadros; i++) {
        if (quadros_livres[i]) {
            quadros_livres[i] = 0;
            memset(&memoria_fisica[i * tamanho_pagina], 0, tamanho_pagina);
            return i;
        }
    }
    return -1;
}

void liberar_quadro(int indice) {
    if (indice >= 0 && indice < num_quadros) {
        quadros_livres[indice] = 1;
        memset(&memoria_fisica[indice * tamanho_pagina], 0, tamanho_pagina);
    }
} 