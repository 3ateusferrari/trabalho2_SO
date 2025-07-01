#ifndef MEMORIA_H
#define MEMORIA_H

extern unsigned char *memoria_fisica;

void inicializar_memoria(int tamanho_fisico, int tamanho_pagina);
void visualizar_memoria();
void liberar_memoria();

int contar_quadros_livres();
int alocar_quadro_livre();
void liberar_quadro(int indice);

#endif