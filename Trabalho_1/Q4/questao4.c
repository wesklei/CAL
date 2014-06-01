#include "questao4.h"

void menuQuatro(void) {
    int opcao, i, j, amostra;
    char metodo[20];
    FILE *fp;

    do {
        system(LIMPA);
        printf("\tQ4 - ALGORITMOS DE ORDENACAO\n\n"
                "\t[1] Bubble Sort\n"
                "\t[2] Insertion Sort\n"
                "\t[3] Merge Sort\n"
                "\t[4] Quick Sort\n"
                "\t[5] Heap Sort\n"
                "\t[6] Gerar arquivo para estatisticas\n"
                "\t[0] Voltar menu principal\n"
                "Opcao:__[");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1: strcpy(metodo, "BUBBLE SORT: ");
                break;
            case 2: strcpy(metodo, "INSERTION SORT: ");
                break;
            case 3: strcpy(metodo, "MERGE SORT: ");
                break;
            case 4: strcpy(metodo, "QUICK SORT: ");
                break;
            case 5: strcpy(metodo, "HEAP SORT: ");
                break;
            case 6:
            {
                printf("Gerando Estatisticas...\nQual o tamanho da amostra?\n");
                scanf(" %d", &amostra);
                for (j = 0; j < amostra; j++) {
                    fp = fopen(arqEst, "a+t");
                    fprintf(fp, "\n\n\n---- AMOSTRA #%d ----\n", j + 1);
                    fclose(fp);
                    for (i = 1; i <= 5; i++) {
                        subMenuCasos(i, "Estatistica");
                    }
                }
            }
                break;
            case 0: puts("Voltandooo...\n");
                break;
            default: puts("Escolha de 0 a 6\n");
        }

        if (opcao > 0 && opcao < 6)
            subMenuCasos(opcao, metodo);
    } while (opcao != 0);
    printf("[ENTER] para continuar...\n");
    fflush(stdin);
    __fpurge(stdin);
    getchar();
}

void subMenuCasos(int numMet, char nomeMet[20]) {
    //Variaveis de controle
    char nomeCaso[20];
    int numCaso;

    if (strcmp(nomeMet, "Estatistica") == 0) {
        strcpy(nomeCaso, nomeMet);
        teste(1, nomeCaso, numMet, nomeMet);
        teste(2, nomeCaso, numMet, nomeMet);
        return;
    }

    do {
        system(LIMPA);
        printf("\t Q4 - ALGORITMOS DE ORDENACAO\n"
                "\t %d - %s\n\n"
                "\t[1] Ordenacao Crescente (melhor caso)\n"
                "\t[2] Ordenacao Decrescente (pior caso)\n"
                "\t[3] Ordenacao Aleatoria\n"
                "\t[0] Voltar ao Menu Q4\n"
                "Opcao:__[", numMet, nomeMet);
        scanf("%d", &numCaso);
        switch (numCaso) {
            case 1:
                strcpy(nomeCaso, "Melhor Caso\n");
                break;
            case 2:
                strcpy(nomeCaso, "Pior Caso\n");
                break;
            case 3:
                strcpy(nomeCaso, "Medio Caso\n");
                break;
            case 0: puts("Voltandooo...\n");
                break;
            default: puts("Escolha de 0 a 4\n");
        }
        if ((numCaso > 0) && (numCaso < 4))
            if (!teste(numCaso, nomeCaso, numMet, nomeMet))
                printf("Problemas no %s do %s", nomeCaso, nomeMet);
    } while (numCaso != 0);
}

int teste(int numCaso, char nomeCaso[20], int numMet, char nomeMet[20]) {
    //Variaveis para calculo de tempo

    double ti, tf, tempo; // ti = tempo inicial // tf = tempo final
    ti = tf = tempo = 0;
    struct timeval tempo_inicio, tempo_fim;

    //clock_t tempoInicial, tempoFinal;
    //double tempoGasto;
    int tamVet = 50000;
    int i, j, seg = 0, useg = 0, *v;
    FILE *fp;

    if (strcmp(nomeMet, nomeCaso) != 0) {
        fp = fopen(arq4, "a+t");
        if (fp == NULL)
            return FRACASSO;
        fprintf(fp, "\n%s%s\n", nomeMet, nomeCaso);
    } else {
        fp = fopen(arqEst, "a+t");
        if (fp == NULL)
            return FRACASSO;
        fprintf(fp, "\nM%d->C%d\n", numMet, numCaso);
    }
    fclose(fp);

    for (j = 0; j < 7; j++) {
        printf("\n\tTeste #%d Metod:%d / Caso:%d"
                "\n\tTamanho do vetor: %d\n", j + 1, numMet, numCaso, tamVet);
        int vet[tamVet];
        switch (numCaso) {
            case 1:
            {
                for (i = 0; i < tamVet; i++)
                    vet[i] = i;
            }
                break;
            case 2:
            {
                for (i = 0; i < tamVet; i++)
                    vet[i] = tamVet - i;
            }
                break;
            case 3:
            {
                for (i = 0; i < tamVet; i++)
                    vet[i] = rand() % 500000;
            }
                break;
            default:
            {
            }
        }
        v = vet;

        gettimeofday(&tempo_inicio, NULL); //funcao com maior precisao em ms
        //tempoInicial = clock();
        switch (numMet) {
            case 1: BubbleSort(v, tamVet);
                break;
            case 2: InsertionSort(v, tamVet);
                break;
            case 3: MergeSort(v, tamVet);
                break;
            case 4: QuickSort(v, tamVet);
                break;
            case 5: heapSort(v, tamVet);
                break;
            default:
            {
            }
        }
        //tempoFinal = clock();
        //tempoGasto = (tempoFinal - tempoInicial) / (double) CLOCKS_PER_SEC;
        gettimeofday(&tempo_fim, NULL);
        tf = (double) tempo_fim.tv_usec + ((double) tempo_fim.tv_sec * (1000000.0));
        ti = (double) tempo_inicio.tv_usec + ((double) tempo_inicio.tv_sec * (1000000.0));
        tempo = (tf - ti) / 1000;

        if (tempo > 1000) {
            seg = tempo / 1000;
            useg = (int) tempo % 1000;
            printf("\tTempo gasto: %d.%d (seg)\n", seg, useg);
        } else
            printf("\tTempo gasto: %.3f (mseg)\n", tempo);
        if (strcmp(nomeMet, nomeCaso) != 0) {
            fp = fopen(arq4, "a+t");
            if (fp == NULL)
                return FRACASSO;
            fprintf(fp, "%d; %.2f\n", tamVet, tempo);
        } else {
            fp = fopen(arqEst, "a+t");
            if (fp == NULL)
                return FRACASSO;
            fprintf(fp, "%.2f\n", tempo);
        }

        fclose(fp);

        tamVet += 50000;
    }
    if (strcmp(nomeMet, nomeCaso) != 0) {
        puts("[ENTER] para continuar\n");
        __fpurge(stdin);
        fflush(stdin);
        getchar();
    }
    return SUCESSO;
}