//MergeSort
#include "questao4.h"

void intercala(int *vet, int p, int q, int r) {
    int i, j, k, *w;
    w = (int *) malloc((r - p) * sizeof (int));

    i = p;
    j = q;
    k = 0;
    while (i < q && j < r) {
        if (vet[i] <= vet[j]) w[k++] = vet[i++];
        else w[k++] = vet[j++];
    }
    while (i < q) {
        w[k++] = vet[i++];
    }
    while (j < r) {
        w[k++] = vet[j++];
    }
    for (i = p; i < r; ++i) {
        vet[i] = w[i - p];
    }
    free(w);
}

// A funcao mergesort rearranja o vetor v[p..r-1] em ordem crescente.

void Merge(int *vet, int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) / 2;
        Merge(vet, p, q);
        Merge(vet, q + 1, r);
        intercala(vet, p, q, r);
    }
}

void MergeSort(int *v, int n) {
    Merge(v, 0, n - 1);
}