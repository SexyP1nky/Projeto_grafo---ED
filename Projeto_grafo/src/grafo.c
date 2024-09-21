#include <stdio.h> 
#include <stdlib.h>
#include "grafo.h"
#include <stdbool.h>
#include <limits.h>

// Funções de criação e destruição de grafos

// Cria um grafo representado por matriz de adjacência
GrafoMatriz* criar_grafo_matriz(int num_vertices) {
    GrafoMatriz* grafo = malloc(sizeof(GrafoMatriz)); // Aloca memória para a estrutura do grafo
    grafo->num_vertices = num_vertices; // Armazena o número de vértices
    grafo->matriz_adj = malloc(num_vertices * sizeof(bool*)); // Aloca memória para a matriz de adjacência

    // Inicializa todas as entradas da matriz como "false" (sem arestas)
    for (int i = 0; i < num_vertices; i++) {
        grafo->matriz_adj[i] = calloc(num_vertices, sizeof(bool)); // Aloca e zera cada linha da matriz
    }
    return grafo;
}

// Libera a memória alocada para um grafo representado por matriz de adjacência
void destruir_grafo_matriz(GrafoMatriz* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        free(grafo->matriz_adj[i]); // Libera cada linha da matriz
    }
    free(grafo->matriz_adj); // Libera a matriz
    free(grafo); // Libera a estrutura do grafo
}

// Cria um grafo representado por lista de adjacência
GrafoLista* criar_grafo_lista(int num_vertices) {
    GrafoLista* grafo = malloc(sizeof(GrafoLista)); // Aloca memória para o grafo
    grafo->num_vertices = num_vertices; // Armazena o número de vértices
    grafo->lista_adj = malloc(num_vertices * sizeof(Nodo*)); // Aloca memória para as listas de adjacência

    // Inicializa cada lista de adjacência como NULL
    for (int i = 0; i < num_vertices; i++) {
        grafo->lista_adj[i] = NULL;
    }
    return grafo;
}

// Libera a memória de um grafo representado por lista de adjacência
void destruir_grafo_lista(GrafoLista* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        Nodo* atual = grafo->lista_adj[i];
        while (atual) {
            Nodo* temp = atual;
            atual = atual->prox; // Avança para o próximo nodo
            free(temp); // Libera o nodo atual
        }
    }
    free(grafo->lista_adj); // Libera o array de listas de adjacência
    free(grafo); // Libera a estrutura do grafo
}

// Função de leitura de arquivos para lista de adjacência

GrafoLista* ler_grafo_lista(const char* filename) {
    FILE* file = fopen(filename, "r"); // Abre o arquivo para leitura
    if (!file) { // Verifica se o arquivo foi aberto corretamente
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int num_vertices, num_arestas;
    if (fscanf(file, "%d %d", &num_vertices, &num_arestas) != 2) { // Lê o número de vértices e arestas
        fprintf(stderr, "Erro ao ler número de vértices e arestas\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    GrafoLista* grafo = criar_grafo_lista(num_vertices); // Cria o grafo com o número de vértices

    int u, v;
    while (fscanf(file, "%d %d", &u, &v) != EOF) { // Lê as arestas (u, v)
        if (u >= num_vertices || v >= num_vertices) { // Verifica se os vértices estão dentro dos limites
            fprintf(stderr, "Erro: Vértices fora do limite (%d, %d)\n", u, v);
            destruir_grafo_lista(grafo);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Insere a aresta na lista de adjacência do vértice u
        Nodo* novo = malloc(sizeof(Nodo));
        novo->vertice = v;
        novo->prox = grafo->lista_adj[u];
        grafo->lista_adj[u] = novo;
    }

    fclose(file); // Fecha o arquivo
    return grafo;
}

// Função de leitura de arquivos para matriz de adjacência

GrafoMatriz* ler_grafo_matriz(const char* filename) {
    FILE* file = fopen(filename, "r"); // Abre o arquivo para leitura
    if (!file) { // Verifica se o arquivo foi aberto corretamente
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int num_vertices, num_arestas;
    fscanf(file, "%d %d", &num_vertices, &num_arestas); // Lê o número de vértices e arestas

    GrafoMatriz* grafo = criar_grafo_matriz(num_vertices); // Cria o grafo com matriz de adjacência

    int u, v;
    while (fscanf(file, "%d %d", &u, &v) != EOF) { // Lê as arestas (u, v)
        if (u < num_vertices && v < num_vertices) {
            grafo->matriz_adj[u][v] = true; // Adiciona a aresta na matriz
            grafo->matriz_adj[v][u] = true; // Para grafos não direcionados, adiciona a aresta simétrica
        } else {
            fprintf(stderr, "Erro: Vértices fora do limite (%d, %d)\n", u, v);
            destruir_grafo_matriz(grafo);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file); // Fecha o arquivo
    return grafo;
}

// Implementação da BFS (Busca em Largura)

void bfs(GrafoLista* grafo, int s, int t) {
    if (s >= grafo->num_vertices || t >= grafo->num_vertices) {
        fprintf(stderr, "Erro: Vértices fora do limite\n");
        return;
    }

    // Arrays para armazenar distâncias, predecessores e vértices visitados
    int* dist = malloc(grafo->num_vertices * sizeof(int));
    int* pred = malloc(grafo->num_vertices * sizeof(int));
    bool* visitado = calloc(grafo->num_vertices, sizeof(bool));

    // Inicializa os arrays
    for (int i = 0; i < grafo->num_vertices; i++) {
        dist[i] = INT_MAX; // Inicializa as distâncias como infinito
        pred[i] = -1; // Nenhum predecessor definido inicialmente
    }

    dist[s] = 0; // Distância da origem para ela mesma é 0
    visitado[s] = true; // Marca a origem como visitada

    // Fila para BFS
    int* fila = malloc(grafo->num_vertices * sizeof(int));
    int inicio = 0, fim = 0;
    fila[fim++] = s; // Insere a origem na fila

    while (inicio < fim) {
        int v = fila[inicio++]; // Remove o próximo vértice da fila
        Nodo* adj = grafo->lista_adj[v]; // Percorre a lista de adjacência de v
        while (adj) {
            if (!visitado[adj->vertice]) {
                visitado[adj->vertice] = true;
                dist[adj->vertice] = dist[v] + 1; // Atualiza a distância
                pred[adj->vertice] = v; // Define o predecessor

                fila[fim++] = adj->vertice; // Insere o vértice adjacente na fila

                // Verifica se o destino foi encontrado
                if (adj->vertice == t) {
                    printf("Caminho de %d para %d: ", s, t);
                    int caminho = adj->vertice;
                    while (caminho != -1) {
                        printf("%d ", caminho);
                        caminho = pred[caminho];
                    }
                    printf("\n");
                    free(fila); free(dist); free(pred); free(visitado); // Libera memória
                    return;
                }
            }
            adj = adj->prox; // Avança para o próximo vértice adjacente
        }
    }

    printf("Não há caminho entre %d e %d\n", s, t); // Se o destino não foi encontrado
    free(fila); free(dist); free(pred); free(visitado); // Libera memória
}

// Implementação iterativa do DFS (Busca em Profundidade) com pilha

void dfs_iterativo(GrafoLista* grafo, int inicio) {
    if (inicio >= grafo->num_vertices) {
        fprintf(stderr, "Erro: Vértice fora do limite\n");
        return;
    }

    bool* visitado = calloc(grafo->num_vertices, sizeof(bool)); // Marca os vértices visitados
    int* pilha = malloc(grafo->num_vertices * sizeof(int)); // Pilha para armazenar os vértices
    int topo = -1;

    if (!visitado || !pilha) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    pilha[++topo] = inicio;

    while (topo >= 0) {
        int v = pilha[topo--];

        if (!visitado[v]) {
            visitado[v] = true;
            printf("%d ", v);
        }

        Nodo* adj = grafo->lista_adj[v];
        while (adj) {
            if (!visitado[adj->vertice]) {
                pilha[++topo] = adj->vertice;
            }
            adj = adj->prox;
        }
    }
    printf("\n");

    free(pilha);
    free(visitado);
}
