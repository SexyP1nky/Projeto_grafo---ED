#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

// Estrutura do grafo com Matriz de Adjacência
typedef struct {
    int num_vertices;
    bool** matriz_adj;
} GrafoMatriz;

// Estrutura do grafo com Lista de Adjacência
typedef struct Nodo {
    int vertice;
    struct Nodo* prox;
} Nodo;

typedef struct {
    int num_vertices;
    Nodo** lista_adj;
} GrafoLista;

// Funções de criação e destruição dos grafos
GrafoMatriz* criar_grafo_matriz(int num_vertices);
void destruir_grafo_matriz(GrafoMatriz* grafo);
GrafoLista* criar_grafo_lista(int num_vertices);
void destruir_grafo_lista(GrafoLista* grafo);

// Funções de leitura dos arquivos e carregamento do grafo
GrafoMatriz* ler_grafo_matriz(const char* filename);
GrafoLista* ler_grafo_lista(const char* filename);

// Funções de busca
void bfs(GrafoLista* grafo, int s, int t);
void dfs_iterativo(GrafoLista* grafo, int inicio);

#endif
