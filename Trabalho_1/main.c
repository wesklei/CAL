/* 
 * File:   main.c
 * Authors: Daniel e Wesklei
 * 
 * Projeto:     IDE NetBeans 8.0
 * Linguagem:   C
 * Sistema Op:  Linux
 * Licensa:     GPL v2
 */

#include "main.h"

void main(void) {
    int opc;
    do {
        system(LIMPA);
        printf("\t ---TRABALHO 01 CAL---\n");
        printf("\t ---MENU PRINCIPAL---\n\n");
        printf("Deseja executar qual questao?\n "
                "\t[1] Q1) Merge Sort Arquivos\n "
                "\t[2] Q2) Lista Encadeada\n "
                "\t[3] Q3) Arvore Binaria de Pesquisa\n "
                "\t[4] Q4) Metodos de Ordenacao\n"
                "\t[5] Q5) Algoritmo de Dijkstra\n"
                "\t[0] Para Sair..."
                "\nOpcao:__[");
        scanf("%d", &opc);
        switch (opc) {
            case 1: questao1();
                break;
            case 2: questao2();
                break;
            case 3: questao3();
                break;
            case 4: menuQuatro();
                break;
            case 5: questao5();
                break;
            default:
            {
            }//printf("Opcao errada!\n Tente de 0 a 5..\n");
        }
    } while (opc != 0);
    exit(EXIT_SUCCESS);
}

