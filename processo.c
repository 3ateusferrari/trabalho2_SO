#include "processo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"
#include <time.h>

typedef struct Processo {
    int pid;
    int tamanho;
    int num_paginas;
    unsigned char *memoria_logica;
    int *tabela_paginas;
    struct Processo *prox;
} Processo;

static Processo *lista_processos = NULL;
static int tam_max_processo = 0;
static int tam_pagina = 0;

void inicializar_processos(int tam_max, int tam_pag) {
    tam_max_processo = tam_max;
    tam_pagina = tam_pag;
    lista_processos = NULL;
}

void liberar_processos() {
    Processo *p = lista_processos;
    while (p) {
        Processo *prox = p->prox;
        if (p->memoria_logica) free(p->memoria_logica);
        if (p->tabela_paginas) free(p->tabela_paginas);
        free(p);
        p = prox;
    }
    lista_processos = NULL;
}

void criar_processo_interativo() {
    int pid, tamanho;
    printf("\n--- Criar Processo ---\n");
    printf("Informe o PID do processo: ");
    scanf("%d", &pid);
    Processo *p = lista_processos;
    while (p) {
        if (p->pid == pid) {
            printf("PID já existe!\n");
            return;
        }
        p = p->prox;
    }
    do {
        printf("Informe o tamanho do processo (bytes): ");
        scanf("%d", &tamanho);
        if (tamanho > tam_max_processo) {
            printf("Tamanho excede o máximo permitido (%d bytes)!\n", tam_max_processo);
        }
    } while (tamanho > tam_max_processo);
    int num_paginas = (tamanho + tam_pagina - 1) / tam_pagina;
    if (contar_quadros_livres() < num_paginas) {
        printf("Memória insuficiente para alocar o processo!\n");
        return;
    }
    Processo *novo = (Processo*) malloc(sizeof(Processo));
    novo->pid = pid;
    novo->tamanho = tamanho;
    novo->num_paginas = num_paginas;
    novo->memoria_logica = (unsigned char*) malloc(tamanho * sizeof(unsigned char));
    novo->tabela_paginas = (int*) malloc(num_paginas * sizeof(int));
    if (!novo || !novo->memoria_logica || !novo->tabela_paginas) {
        printf("Erro ao alocar memória para o processo!\n");
        if (novo) free(novo);
        return;
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < tamanho; i++) {
        novo->memoria_logica[i] = rand() % 256;
    }
    for (int i = 0; i < num_paginas; i++) {
        int quadro = alocar_quadro_livre();
        if (quadro == -1) {
            printf("Erro inesperado: não há quadros livres suficientes!\n");
            for (int j = 0; j < i; j++) liberar_quadro(novo->tabela_paginas[j]);
            free(novo->memoria_logica);
            free(novo->tabela_paginas);
            free(novo);
            return;
        }
        novo->tabela_paginas[i] = quadro;
        int offset_logico = i * tam_pagina;
        int bytes_para_copiar = tam_pagina;
        if (offset_logico + bytes_para_copiar > tamanho) {
            bytes_para_copiar = tamanho - offset_logico;
        }
        memcpy(&((unsigned char*)memoria_fisica)[quadro * tam_pagina], &novo->memoria_logica[offset_logico], bytes_para_copiar);
    }
    novo->prox = lista_processos;
    lista_processos = novo;
    printf("Processo criado com sucesso! PID=%d, %d bytes, %d páginas.\n", pid, tamanho, num_paginas);
}

void visualizar_tabela_paginas_interativo() {
    int pid;
    printf("\n--- Visualizar Tabela de Páginas ---\n");
    printf("Informe o PID do processo: ");
    scanf("%d", &pid);
    Processo *p = lista_processos;
    while (p) {
        if (p->pid == pid) {
            printf("Processo PID=%d\n", p->pid);
            printf("Tamanho: %d bytes\n", p->tamanho);
            printf("Número de páginas: %d\n", p->num_paginas);
            printf("Tabela de páginas (página -> quadro):\n");
            for (int i = 0; i < p->num_paginas; i++) {
                printf("Página %2d -> Quadro %2d\n", i, p->tabela_paginas[i]);
            }
            return;
        }
        p = p->prox;
    }
    printf("Processo com PID %d não encontrado!\n", pid);
} 