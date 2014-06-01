#include "main.h"

typedef struct Aresta { //Para o Dijkstra
    int adj;
    int peso;
} Aresta;

typedef struct Grafo { //Para o Dijkstra
    struct Aresta matriz[TAMANHOMAX][TAMANHOMAX]; //matriz de adj
} Grafo;

int insereAdj(Grafo *grafo, int i, int j, int adj_valor, int peso) {
    if (grafo == NULL || i < 0 || j > TAMANHOMAX) {
        return FRACASSO;
    } else {

        //se nao tem adjacencia o peso eh infinito
        grafo->matriz[i][j].adj = adj_valor;
        if (adj_valor == 0) {
            grafo->matriz[i][j].peso = INFINITO;
        } else {
            grafo->matriz[i][j].peso = peso;
        }

        return SUCESSO;
    }
}

/**
 * Como usar:
 * Passar o grafo, o vertici inicial S e o vertice destino T
 * Passar um vertice *caminho com tamanho n_vertices e um vetor distancia com
 * tamanho n_vertices. 'caminho' e 'distancia' deve estar alocado, mas nao precisa
 * estar inicializado.
 * 
 * O retorno estara em 'caminho' e 'distancia' sendo:
 * distancia[t] o custo do caminho ate 't'
 * @param grafo
 * @param s
 * @param t
 * @param n_vertices
 * @param caminho
 * @param distancia
 * @return 
 */
int dijkstra(Grafo *grafo, int s, int t, int n_vertices, int *caminho, int *distancia) {

    int visitados[n_vertices];
    int atual, i, k, dist_atual;
    int menor_dist, nova_dist;

    //inicializa a lista de visitados e distancia com valor padrao
    for (i = 0; i < n_vertices; i++) {
        visitados[i] = NAOVISITOU;
        distancia[i] = INFINITO;
    }

    //inicia em S entao marca que visitou
    visitados[s] = VISITOU;
    distancia[s] = 0; //pra ele mesmo eh zero

    //marca s o ponto inicial
    atual = s;
    k = atual;

    //enquanto nao chegar no vertice final informado 't'
    while (atual != t) {

        menor_dist = INFINITO;
        dist_atual = distancia[atual];

        for (i = 0; i < n_vertices; i++) {

            //se nao visitou ainda
            if (visitados[i] == NAOVISITOU) {

                nova_dist = dist_atual + grafo->matriz[atual][i].peso;

                //verifica se a distancia apartir do atual eh menor
                //se for atualiza o vetor de distancia e de caminho percorrido
                if (nova_dist < distancia[i]) {
                    distancia[i] = nova_dist;
                    caminho[i] = atual;
                }

                //compara com o geral
                //se a distancia avaliada eh menor que a menor encontrada ate o momento
                //atualiza o menor global e guarda o indice no 'k'
                if (distancia[i] < menor_dist) {
                    menor_dist = distancia[i];
                    k = i;
                }
            }
        }

        //evita loop infinito
        if (atual == k) {
            printf("\nCaminho nao foi encontrado!\n");
            return FRACASSO;
        }

        atual = k;
        visitados[atual] = VISITOU;
    }

    return SUCESSO;
}

int carregaMatrizAdjArquivo(Grafo *grafo, int *n_vertices) {
    FILE *fp;
    int i, j, test_qt_vertic_read = 0;
    int adj_valor, adj_peso;

    fp = fopen(arq5, "r");
    if (fp == NULL)
        return FRACASSO;

    fscanf(fp, "%d", n_vertices);
    printf("%d\n", *n_vertices);

    for (i = 0; i<*n_vertices; i++) {
        for (j = 0; j<*n_vertices; j++) {

            fscanf(fp, "%d %d", &adj_valor, &adj_peso);

            if (!insereAdj(grafo, i, j, adj_valor, adj_peso)) {
                printf("\nERRO! Problema de insercao no graco com a adjacencia %d %d!\n", i, j);
            }

            printf("%d %d ", adj_valor, adj_peso);
        }
        test_qt_vertic_read++;
        printf("\n");
    }

    fclose(fp);
    printf("teste %d %d\n", test_qt_vertic_read, *n_vertices);

    if (test_qt_vertic_read == *n_vertices)
        return SUCESSO;
    else
        return FRACASSO;
}

void questao5(void) {
    char opcao;
    Grafo grafo;
    int n_vertices = -1, i, j, k, s, t, caminho_iterator;
    int *caminho;
    int *distancia;
    int adj_valor, adj_peso;

    do {
        system(LIMPA);
        printf("\tQ5 - ALGORITMO DE DIJKSTRA\n\n"
                "\t[1] Carregar matriz de adjacencia do arquivo\n"
                "\t[2] Entrar com matriz de adjacencia\n"
                "\t[3] Calcular Caminho mais curto\n"
                "\t[4] Mostra complexidade\n"
                "\t[5] Mostra a matriz de adjacencia\n"
                "\t[0] Sair\n"
                "Opcao:__[");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                printf("Carregando matriz de arquivo\n\n");
                if (carregaMatrizAdjArquivo(&grafo, &n_vertices)) {
                    printf("Carregou com sucesso!\n");
                } else {
                    printf("Problema ao carregar matriz do arquivo!\n");
                }
                break;
            case 2:
                printf("Deseja inserir qntos vertices?\n");
                scanf(" %d", &n_vertices);
                if (n_vertices > 0) {
                    printf("Digite a matriz de adjacencia com %d vertices e seus respectivos pesos:\n\n", n_vertices);
                    for (i = 0; i < n_vertices; i++) {
                        for (j = 0; j < n_vertices; j++) {
                            printf("\nAdj e peso para matriz[%d][%d]:_ ", i, j);
                            scanf("%d", &adj_valor);
                            scanf("%d", &adj_peso);

                            if (insereAdj(&grafo, i, j, adj_valor, adj_peso))
                                printf("\nInseriu adjacencia %d %d com sucesso!\n", i, j);
                            else printf("\nERRO! Problema de insercao no graco com a adjacencia %d %d!\n", i, j);
                        }
                    }
                }
                break;

            case 3:

                printf("Qual o vertice de inicio?\n");
                scanf(" %d", &s);
                printf("Qual o vertice final?\n");
                scanf(" %d", &t);

                //aloca os vetores caminho e distancia
                caminho = malloc(sizeof (int) * n_vertices);
                distancia = malloc(sizeof (int) * n_vertices);

                for (i = 0; i < n_vertices; i++) {
                    caminho[i] = 0;
                    distancia[i] = INFINITO;
                }

                if (dijkstra(&grafo, s, t, n_vertices, caminho, distancia)) {

                    printf("\n\n Caminho percorrido: ");
                    caminho_iterator = t;

                    printf("%d <- ", t);

                    while (caminho_iterator != s) {
                        printf("%d", caminho[caminho_iterator]);
                        caminho_iterator = caminho[caminho_iterator];

                        if (caminho_iterator != s)
                            printf(" <- ");
                    }

                    printf("\n\nCusto de %d ate %d: %d\n\n", s, t, distancia[t]);
                } else {
                    printf("\nERRO! Problema ao executar Dijkstra de %d ate %d!\n", s, t);
                }


                break;

            case 4:
                printf("O(n^2)\n");
                break;
            case 5:
                if (n_vertices > 0) {
                    //faz cabecalho da matriz
                    printf("      ");
                    for (j = 0; j < n_vertices; j++) {
                        printf("(%d)        ", j);
                    }
                    printf("\n");
                    //o i vai imprimir o numero da linha
                    for (i = 0; i < n_vertices; i++) {
                        printf("(%d)  ", i);

                        for (j = 0; j < n_vertices; j++) {
                            printf("[%d / %d]   ", grafo.matriz[i][j].adj, grafo.matriz[i][j].peso == INFINITO ? -1 : grafo.matriz[i][j].peso);
                        }
                        printf("\n");
                    }
                } else {
                    printf("\nVoce deve primeiro carregar uma matriz de adjacencia!\n");
                }

                break;

            default:
            {
            }
        }
        printf("\n[ENTER] para continuar...\n");
        fflush(stdin);
        __fpurge(stdin);
        getchar();
    } while (opcao != 0);
}
