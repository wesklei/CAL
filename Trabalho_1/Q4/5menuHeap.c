//HeapSort
#include "questao4.h"

// troca o valor de duas variaveis

void troca(int *data1, int *data2) {
    int temp;
    temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

// devolve o índice do filho esquerdo no no de indice i

int filho_esq(int i) {
    return 2 * i;
}

// devolve o indice do filho direito do no de indice i

int filho_dir(int i) {
    return 2 * i + 1;
}

// efetua um push down no no de indice i

void pushDown(int i, int *heap, int tam) {
    int ha_esq = 0, ha_dir = 0;
    if (filho_esq(i) <= tam) ha_esq = 1;
    if (filho_dir(i) <= tam) ha_dir = 1;
    if (ha_esq && !ha_dir) {
        if (heap[i] < heap[filho_esq(i)]) {
            troca(&heap[filho_esq(i)], &heap[i]);
            pushDown(filho_esq(i), heap, tam);
        }
    } else
        if (ha_esq && ha_dir) {
        if ((heap[i] < heap[filho_esq(i)]) || (heap[i] < heap[filho_dir(i)])) {
            if (heap[filho_esq(i)] > heap[filho_dir(i)]) {
                troca(&heap[filho_esq(i)], &heap[i]);
                i = filho_esq(i);
            } else {
                troca(&heap[filho_dir(i)], &heap[i]);
                i = filho_dir(i);
            }
            pushDown(i, heap, tam);
        }
    }
}

// funcao para fazer a montagem da heap

void montaHeap(int *heap, int n) {
    int i;
    for (i = n / 2; i >= 1; i--) {
        pushDown(i, heap, n);
    }
}

// funcao para fazer a desmontagem da heap

void desmontaHeap(int *heap, int tam) {
    int i;
    int n = tam;
    for (i = 1; i <= n; i++) {
        troca(&heap[1], &heap[tam]);
        tam--;
        pushDown(1, heap, tam);
    }
}

// heapSort: funcao que ordena uma lista dada, chamando, em ordem,
// a rotina que monta a heap e a que efetua a desmontagem

void heapSort(int *v, int n) {
    montaHeap(v, n);
    desmontaHeap(v, n);
}