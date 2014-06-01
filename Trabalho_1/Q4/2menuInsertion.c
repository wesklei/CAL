//Insertion Sort
#include "questao4.h"

void InsertionSort(int *v, int n){
    int i,j,aux;
    
    for(i = 1; i < n; i++){
        aux = v[i];
        j = i-1;
        while((j >= 0) && (v[j] > aux)){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = aux;
    }
}