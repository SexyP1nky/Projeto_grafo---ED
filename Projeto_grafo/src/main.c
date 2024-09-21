#include "grafo.h"
#include <stdio.h>

int main() {
    // Ler arquivo do grafo
    GrafoLista* grafo = ler_grafo_lista("test/test_case_1.txt");
    
    // Realizar busca em largura entre dois vértices
    bfs(grafo, 0, 4);
    
    // Realizar busca em profundidade iterativa
    dfs_iterativo(grafo, 0);

    // Liberar memória
    destruir_grafo_lista(grafo);

    return 0;
}
