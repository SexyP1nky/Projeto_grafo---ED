# Projeto_grafo---ED

Pontos atendidos de acordo com o projeto:

Representação de Grafos:

    O código implementa a estrutura de grafos em Matriz de Adjacência e Lista de Adjacência, como solicitado.
    As funções criar_grafo_matriz, destruir_grafo_matriz, criar_grafo_lista e destruir_grafo_lista lidam com a criação e destruição dessas representações.

Leitor de Arquivos e Carregamento das Estruturas:

    As funções ler_grafo_matriz e ler_grafo_lista são responsáveis pela leitura dos arquivos e carregamento das estruturas do grafo (Matriz e Lista de Adjacência).

Busca em Largura (BFS):

    A função bfs implementa a busca em largura e imprime o caminho entre dois vértices, conforme solicitado.
    Caso não haja caminho entre os vértices, ela informa o usuário que "não há caminho entre os vértices".

Busca em Profundidade (DFS) com Pilha:

    A função dfs_iterativo implementa o DFS de maneira iterativa usando uma pilha, eliminando a recursividade, como especificado.




Exemplo de compilação na minha máquina:PS C:\Users\yuris\Downloads\Projeto_grafo> mingw32-make
gcc -Wall -g -Iinclude -c src/grafo.c -o obj/grafo.o
gcc -Wall -g obj/grafo.o obj/main.o -o bin/main
PS C:\Users\yuris\Downloads\Projeto_grafo> mingw32-make run
gcc -Wall -g obj/grafo.o obj/main.o -o bin/main
bin\main
Caminho de 0 para 4: 4 3 2 0
0 1 3 4 2
PS C:\Users\yuris\Downloads\Projeto_grafo> mingw32-make clean
rmdir /s /q obj bin.


passo a passo: 
1.mingw32-make
2.mingw32-make run
3. mingw32-make clear
