//QuickSort
#include "questao4.h"

int Particione(int *v, int esquerda, int direita){
    //Criando ponto de pivo
    int x = v[(esquerda+direita)/2];
    int aux;
    
    int alto = direita;
    int baixo = esquerda;
    
    while(baixo < alto){
        while(x < v[alto]){
            alto--;
        }
        while(x > v[baixo]){
            baixo++;
        }
        if(baixo < alto){
            aux = v[baixo];
            v[baixo] = v[alto];
            v[alto] = aux;
        }
        else {
            return alto;
        }
    }
}

void Quick(int *v, int esquerda, int direita){
    int i;
    
    if(esquerda < direita){
        i = Particione(v, esquerda, direita);
        Quick(v,esquerda,i-1);
        Quick(v,i+1,direita);
    }
}

void QuickSort(int *v, int n){
    Quick(v, 0, n-1);
}