#include "main.h"

/****************************************************************************** 
 * COMPLECIDADE inserirLista()
 *  PIOR CASO: O(n)
 *      Se a lista tiver algum elemento
 *  MELHOR CASO: O(1)
 *      Se a lista estiver vazia insere na primeira posicao
 * 
 */
int inserirLista(ppAgenda2 agenda, int cod, char nome[T_NOME], char end[T_END], char fone[T_FONE]) {
    pAgenda2 aux;

    //Lista vazia
    if ((*agenda) == NULL) {
        (*agenda) = (pAgenda2) malloc(sizeof (Agenda2));
        if ((*agenda) == NULL) {
            return FRACASSO;
        }
        (*agenda)->cod = cod;
        strcpy((*agenda)->nome, nome);
        strcpy((*agenda)->end, end);
        strcpy((*agenda)->fone, fone);
        (*agenda)->proximo = NULL;

    } else {
        //Aux apontando para agenda
        aux = *agenda;
        //Percorrendo lista para achar a ultima posição  
        //COMPLEXIDADE O(n) NO PIOR CASO           
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        aux->proximo = (pAgenda2) malloc(sizeof (Agenda2));
        if (aux->proximo == NULL) {
            return FRACASSO;
        }
        aux = aux->proximo;
        aux->cod = cod;
        strcpy(aux->nome, nome);
        strcpy(aux->end, end);
        strcpy(aux->fone, fone);
        aux->proximo = NULL;
    }
    return SUCESSO;
}

/******************************************************************************
 *  COMPLEXIDADE removerLista()
 *  PIOR CASO: O(n) 
 *      se lista tiver mais de 2 elementos
 *  MELHOR CASO O(1) 
 *      se lista tiver 1 elemento;
 *      se elemento estiver na primeira posicao
 */
int removerLista(ppAgenda2 agenda, int cod) {
    pAgenda2 aux, auxProximo;
    aux = *agenda;

    if (aux == NULL) {
        puts("Lista vazia.\n");
        return FRACASSO;
    }
    if (aux->proximo == NULL) { //Lista com 1 elemento
        if (aux->cod == cod) {
            free(agenda);
            agenda = NULL;
            return SUCESSO;
        }
    } else {
        if (aux->cod == cod) { //Lista com elemento na primeira posicao
            free(aux);
            return SUCESSO;
        } else {
            auxProximo = aux->proximo;
            while (auxProximo != NULL) {
                if (auxProximo->cod == cod) {
                    aux->proximo = auxProximo->proximo;
                    free(auxProximo);
                    return SUCESSO;
                }
                aux = auxProximo;
                auxProximo = auxProximo->proximo;
            }
        }
    }
    return FRACASSO;
}

/******************************************************************************
 * COMPLECIDADE buscarLista()
 *  PIOR CASO: O(n) 
 *      se lista tiver mais de 2 elementos
 *  MELHOR CASO O(1) 
 *      se lista tiver 1 elemento;
 *      se elemento estiver na primeira posicao
 */
int buscarLista(ppAgenda2 agenda, int cod) {
    pAgenda2 aux, auxProximo;
    aux = *agenda;

    //Lista vazia
    if (aux == NULL)
        return FRACASSO;

    //Lista com 1 elemento reducao da complexidade
    if (aux->proximo == NULL) {
        if (aux->cod == cod) {
            printf("Codigo: %d \nNome: %s Endereco: %s Fone: %s \n", 
                    aux->cod, aux->nome, aux->end, aux->fone);
            return SUCESSO;
        }
    }//Lista com mais de 1 elemento
    else {
        if (aux->cod == cod) {
            printf("Codigo: %d \nNome: %sEndereco: %sFone: %s\n", 
                    aux->cod, aux->nome, aux->end, aux->fone);
            return SUCESSO;
        } else {
            auxProximo = aux->proximo;
            while (auxProximo != NULL) {
                if (auxProximo->cod == cod) {
                    printf("Codigo: %d\nNome: %sEndereco: %sFone: %s\n", 
                            auxProximo->cod, auxProximo->nome, auxProximo->end, auxProximo->fone);
                    return SUCESSO;
                }
                aux = auxProximo;
                auxProximo = auxProximo->proximo;
            }
        }
    }
    return FRACASSO;
}

void questao2(void) {

    pAgenda2 agenda = NULL;
    int opc, cod;
    char nome[T_NOME],
            end[T_END],
            fone[T_FONE];
    do {
        system(LIMPA);
        printf("\tQ2 - LISTA ENCADEADA\n\n"
                "\t[1] Inserir na agenda\n "
                "\t[2] Buscar na agenda\n "
                "\t[3] Remover da agenda\n "
                "\t[0]Voltar  programa principal\n"
                "Opcao:__[");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
            {
                printf("Entre com:\nCodigo: ");
                scanf("%i*c", &cod);
                printf("Nome: ");
                __fpurge(stdin);
                fgets(nome, T_NOME * sizeof (char), stdin);
                printf("Rua: ");
                __fpurge(stdin);
                fgets(end, T_END * sizeof (char), stdin);
                printf("Fone: ");
                __fpurge(stdin);
                fgets(fone, T_FONE * sizeof (char), stdin);

                if (!inserirLista(&agenda, cod, nome, end, fone))
                    printf("Problema na insercao de %d!\n", cod);
                else
                    printf("%d Inserido com sucesso!\n", cod);
            }
                break;
            case 2:
            {
                printf("Qual codigo deseja buscar?\n");
                scanf("%d", &cod);

                if (!buscarLista(&agenda, cod))
                    printf("Contato %d nao encontrado!\n", cod);
            }
                break;
            case 3:
            {
                printf("Qual codigo quer remover?\n");
                scanf("%d", &cod);
                if (!removerLista(&agenda, cod))
                    printf("Problema ao remover %d!\n", cod);
                else
                    printf("Item %d Removido com sucesso!\n", cod);
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
    } while (opc != 0);
}
