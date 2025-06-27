#ifndef MEMORIA_H
#define MEMORIA_H

void inicializar_memoria(int tamanho_fisico, int tamanho_pagina);
void visualizar_memoria();
void liberar_memoria();

// Funções auxiliares para quadros
int contar_quadros_livres();
int alocar_quadro_livre(); // retorna índice do quadro ou -1
void liberar_quadro(int indice);

#endif // MEMORIA_H 