#include "main.h"
#include "questao3.h"

/******************************************************************************
 * COMPLEXIDADE criaABB()
 *  PIOR E MELHOR CASO: O(1) 
 */
int criaABB(ppABB pp, int tinfo) {
    if ((*pp) != NULL)
        return FRACASSO;
    (*pp) = (pABB) malloc(sizeof (ABB));
    if ((*pp) == NULL)
        return FRACASSO;
    (*pp)->tinfo = tinfo;
    (*pp)->raiz = NULL;
    return SUCESSO;
}

int vazia(pABB p) {
    if (p->raiz != NULL)
        return FRACASSO;
    else
        return SUCESSO;
}

/******************************************************************************
 * COMPLEXIDADE insereABB()
 *  PIOR CASO: O(n) 
 *      se arvore degenerada em lista (não balanceada)
 *  MELHOR CASO O(h)  
 *      sendo h a altura da arvore
 * 
 * A inserção requer uma busca pelo lugar da chave, portanto, com custo 
 * de uma busca qualquer (tempo proporcional à altura da árvore).
 * O custo da inserção, após a localização do lugar, é constante; 
 * não depende do número de nós.
 */
int insereABB(pABB p, void *elemento, int (*compara)(void *dado1, void *dado2)) {
    if (p == NULL)
        return FRACASSO;
    pNoABB novo = (pNoABB) malloc(sizeof (NoABB));
    novo->dado = malloc(p->tinfo);
    memcpy(novo->dado, elemento, p->tinfo);
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL; //formato de raiz;
    if (vazia(p)) { //se vazia complexidade constante O(1)
        p->raiz = novo;
        return SUCESSO;
    } else { //se não for raiz complexidade O()
        pNoABB temp = p->raiz;
        int comparacao;
        while (temp != NULL && temp->dado != NULL) { //temp->dado é para garantir que a comparação ocorrerá normalmente
            comparacao = compara(novo->dado, temp->dado);
            if (comparacao == MENOR) { //novo->dado é menor que temp->dado
                if (temp->esq != NULL)
                    temp = temp->esq;
                else { //caso não haja elemento no lado desejado, inserir
                    novo->pai = temp;
                    temp->esq = novo;
                    return SUCESSO;
                }
            } else if (comparacao == MAIOR) {
                if (temp->dir != NULL)
                    temp = temp->dir;
                else { //caso não haja elemento no lado desejado, inserir
                    novo->pai = temp;
                    temp->dir = novo;
                    return SUCESSO;
                }
            } else { //se comparacao==IGUAL então dado já foi inserido
                free(novo->dado);
                free(novo);
                novo = NULL;
                return FRACASSO;
            }
        } //se sair do while é porque ocorreu um erro, portanto deve retornar fracasso
    }
    return FRACASSO;
}

/******************************************************************************
 * COMPLEXIDADE sucessor()
*/
pNoABB sucessor(pNoABB p) {
    pNoABB temp = NULL;
    if (p->esq != NULL) {
        temp = p->esq;
    }
    if (p->dir != NULL) {
        temp = p->dir;
    }
    while (temp->esq != NULL) {
        temp = temp->esq;
    }
    return temp;
}

int nfilhos(pNoABB p, int *pos) { //recebe o endereço do nó que deseja verificar o número de filhos que possui
    int num = 0;
    if (p->esq != NULL) {
        num++;
        if (pos != NULL) {
            *pos = ESQUERDA;
        } //pos vai ser NULL quando a função for chamada por percursoOrdem
    } //pos=0 = filho à esquerda, pos=1 = filho à direita, pos=2 = 2 filhos (esq e dir)
    if (p->dir != NULL) {
        num++; //num == numero de filhos
        if (*pos == ESQUERDA) {
            *pos = AMBOS;
        }//se tiver filho à esquerda, então tem filho nos 2 lados
        else if (pos != NULL) {
            *pos = DIREITA;
        } //se não, tem apenas à direita
    } //não tem problema pos retornar sem receber valor, pois só será necessário nos casos onde recebe valor
    return num;
}

/******************************************************************************
 * COMPLEXIDADE removeRecursivo()
 *  PIOR CASO: O(n) 
 *      se arvore degenerada ou nao balanceada
 *  MELHOR CASO O(log n) 
 *      se arvore balanceada
 */
pNoABB removeRecursivo(pNoABB temp, void *elemento, int (*compara)(void *dado1, void *dado2)) {
    int comp = compara(elemento, temp->dado);
    if (comp == MAIOR) {
        return removeRecursivo(temp->dir, elemento, compara);
    }
    if (comp == MENOR) {
        return removeRecursivo(temp->esq, elemento, compara);
    }
    if (comp == IGUAL) {
        return temp;
    } //se comparacao==IGUAL então dado existe, portanto remover

    return temp;
}

/******************************************************************************
 * COMPLEXIDADE removeRecABB()
 *  PIOR E MELHOR CASO: 
 *  Constante tirando a chamada do removeRecursivo()
 */
int removeRecABB(pABB p, void *elemento, int (*compara)(void *dado1, void *dado2)) {
    pNoABB pNo = NULL, //pNo: endereco do elemento a ser retirado;
            sub = NULL; //sub: endereco do substituto (caso tenha 2 filhos)
    int num, pos; //num=numero de filhos; pos=dir/esq/ambos (em abb_publico)
    if (vazia(p))
        return FRACASSO;
    pNo = removeRecursivo(p->raiz, elemento, compara); //ao final, pno ter  o endere o do elemento a ser removido
    if (pNo == NULL) {
        free(pNo->dado);
        free(pNo);
        pNo = NULL; //Ao final, remove o elemento
        return FRACASSO;
    }
    memcpy(elemento, pNo->dado, p->tinfo); //recebe um dado que tem apenas o rotulo, retorna o dado completo
    num = nfilhos(pNo, &pos); //para saber quantos filhos possui o elemento a ser removido e a localiza  o do(s) mesmo(s)
    if (num == 0) { //se nao tiver filhos
        if (pNo == p->raiz) {
            p->raiz = NULL;
        } else {
            if (pNo->pai->dir == pNo) {
                pNo->pai->dir = NULL;
            }
            if (pNo->pai->esq == pNo) {
                pNo->pai->esq = NULL;
            }
        }
    } else if (num == 1) {
        if (pNo == p->raiz) {
            if (pos == DIREITA) {
                p->raiz = pNo->dir;
            }
            if (pos == ESQUERDA) {
                p->raiz = pNo->esq;
            }
        } else {
            if (pNo->pai->dir == pNo) {
                if (pos == DIREITA) {
                    pNo->pai->dir = pNo->dir;
                } else {
                    pNo->pai->dir = pNo->esq;
                } //mesmo que: if (pos==ESQUERDA){
            }
            if (pNo->pai->esq == pNo) {
                if (pos == DIREITA) {
                    pNo->pai->esq = pNo->dir;
                } else {
                    pNo->pai->esq = pNo->esq;
                } //mesmo que: if (pos==ESQUERDA){
            }
        }
    } else if (num == 2) {
        sub = sucessor(pNo); //sucessor do elemento a ser removido
        if (sub->pai != pNo) {
            sub->pai->esq = sub->dir;
        } //se substituto n o for o filho a direita do elemento a ser removido
        sub->esq = pNo->esq;
        if (pNo->dir != sub) {
            sub->dir = pNo->dir;
        }
        sub->pai = pNo->pai; //Passar para o substituto os elementos de pno (esq, dir, pai, etc)
        if (pNo != p->raiz) {
            if (pNo->pai->dir == pNo) {
                pNo->pai->dir = sub;
            } else {
                pNo->pai->esq = sub;
            }
        } else {
            p->raiz = sub;
            sub->pai = NULL;
        }
        if (pNo->dir != NULL) {
            if (pNo->dir != sub) {
                pNo->dir->pai = sub;
            }
        }
        if (pNo->esq != NULL) {
            if (pNo->esq != sub) {
                pNo->esq->pai = sub;
            }
        }
    }
    free(pNo->dado);
    free(pNo);
    pNo = NULL; //Ao final, remove o elemento
    return SUCESSO;
}

/************************* REMOCAO SEM RECURSAO ******************************/
/******************************************************************************
 * COMPLEXIDADE removeABB()
 *  PIOR CASO: O(n) 
 *      se degenerada ou nao balanceada
 *  MELHOR CASO O(log n) 
 *      se 
 * Seja uma árvore binária de busca de n nós e de altura h.
 * A remoção precisa primeiro localizar o nó que contém a chave a ser removida.
 * Durante a remoção (caso 2) é necessário localizar o nó mais à esquerda 
 *      (ou mais à direita) de uma subárvore.
 * A complexidade de remoção é O(h).
 * No pior caso, a altura de uma árvore binária de busca pode ser O(n).
 */
int removeABB(pABB p, void *chave, int (*compara)(void *dado1, void *dado2)) {
    pNoABB aux, ant, suc, pai_suc, x;
    
    ant = NULL;
    if (p == NULL) //se a arvore nao foi criada
        return FRACASSO;
    if (vazia(p)) //se a arvore estiver vazia
        return FRACASSO;
    
    aux = p->raiz;
    while (aux != NULL && compara(chave, aux->dado) != IGUAL) {
        ant = aux;
        if (compara(chave, aux->dado) == MENOR)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    
    if (aux == NULL) //nao encontrou
        return FRACASSO;
    if (aux->esq == NULL && aux->dir == NULL) { //Remocao de um no sem filhos
        if (ant == NULL)
            p->raiz = NULL;
        else {
            if (compara(chave, ant->dado) == MENOR)
                ant->esq = NULL;
            else
                ant->dir = NULL;
        }
    } else {//Se nao for o caso 1
        if (aux->esq == NULL || aux->dir == NULL) {//Remocao de um no com um unico filho(esquerdo ou direito)
            if (ant == NULL) { //remocao da raiz
                if (aux->esq == NULL)
                    p->raiz = aux->dir;
                else
                    p->raiz = aux->esq;
            } else {
                if (aux->esq == NULL)
                    x = aux->dir;
                else
                    x = aux->esq;

                if (ant->esq == aux)
                    ant->esq = x;
                else
                    ant->dir = x;
            }
        } else { //Remocao de um no com dois filhos substituido pelo no Sucessor(ou Antecessor) vem na sequencia da ordenacao.
            suc = aux->dir;
            pai_suc = aux; //Atual - elemento a ser removido

            //Procurar sucessor, a direita do removido, a sempre a esquerda
            //(esse elemento nao tera elemento a esquerda, visto que esse elemento seria o que estou removendo
            while (suc->esq != NULL) {
                pai_suc = suc;
                suc = suc->esq;
            }

            if (pai_suc != aux) {
                pai_suc->esq = suc->dir; //Incluindo NULL (O sucesso e uma folha)
                suc->esq = aux->esq;
                suc->dir = aux->dir;
            } else {
                suc->esq = aux->esq; //Nao pegou nenhuma esquerda
            }
            if (ant == NULL) { //remocao da raiz com dois filhos
                p->raiz = suc;
            } else {
                if (ant->esq == aux)
                    ant->esq = suc;
                else
                    ant->dir = suc;
            }
        }
    }
    free(aux->dado);
    free(aux);
    return SUCESSO;
}

/******************************************************************************
 * COMPLEXIDADE pop()
 *  PIOR E MELHOR CASO: O(1) 
 */
NoABB pop(pSTACK pStack) {

    NoABB retorno;
    if (pStack->topo == -1) {
        printf("Pilha esta vazia!\n");
        return retorno;
    } else {
        pStack->topo -= 1;
        return pStack->s[pStack->topo + 1];
    }
    return retorno;
}

/******************************************************************************
 * COMPLEXIDADE push()
 *  PIOR E MELHOR CASO: O(1) 
 */
void push(pSTACK pStack, pNoABB elem) {

    if ((pStack)->topo == (MAXSTACKSIZE - 1)) {
        printf("ERROR: Pilha esta cheia!\n");
    } else {
        (pStack)->topo = (pStack)->topo + 1;
        memcpy(&(pStack)->s[(pStack)->topo], elem, sizeof (NoABB));
    }
}

//esta versao  assume que nao tera mais de 100 elemtnos na arvore
/******************************************************************************
 * COMPLEXIDADE OrdemNaoRecursivo()
 *  PIOR e MELHOR CASO: O(log n * log n) 
 */
void OrdemNaoRecursivo(pNoABB raiz, int (*exibe)(void *dado)) {

    int topo = 0;
    STACK stack;
    stack.topo = -1;
    pNoABB iterator = malloc(sizeof (NoABB));
    NoABB exibirTmp;

    //push(&stack,raiz);
    iterator = raiz;
    //enquanto na estiver vazia
    do {
        //percorre e empilha tudo a esquerda
        while (iterator != NULL) {          //(LOG N)
            push(&stack, iterator);
            iterator = iterator->esq;
        }

        if (stack.topo != -1) {
            //quando subarvore esquerda esta vazia
            exibirTmp = pop(&stack);
            exibe(exibirTmp.dado);
            iterator = &exibirTmp;
            iterator = iterator->dir;
        }

    } while (stack.topo != -1 || iterator != NULL); //(LOG N)
}

/******************************************************************************
 * COMPLEXIDADE percursoOrdemNaoRecursivo()
*/
int percursoOrdemNaoRecursivo(pABB p, int (*exibe)(void *dado)) { //desce esquerda, mostra, desce direita
    if (p == NULL)
        return FRACASSO;
    if (vazia(p))
        return FRACASSO;
    OrdemNaoRecursivo(p->raiz, exibe);
    return SUCESSO;
}

/******************************************************************************
 * COMPLEXIDADE OrdemRecursivo()
 */
void OrdemRecursivo(pNoABB temp, int (*exibe)(void *dado)) {
    if (temp->esq != NULL)
        OrdemRecursivo(temp->esq, exibe);
    exibe(temp->dado);
    if (temp->dir != NULL)
        OrdemRecursivo(temp->dir, exibe);
}

/******************************************************************************
 * COMPLEXIDADE percursoOrdem()
 */
int percursoOrdem(pABB p, int (*exibe)(void *dado)) { //desce esquerda, mostra, desce direita
    if (p == NULL)
        return FRACASSO;
    if (vazia(p))
        return FRACASSO;
    OrdemRecursivo(p->raiz, exibe);
    return SUCESSO;
}


int compara(void *dado1, void *dado2) {
    Agendaa *cod1 = (Agendaa*) dado1;
    Agendaa *cod2 = (Agendaa*) dado2;
    if (cod1->cod < cod2->cod)
        return MENOR;
    if (cod1->cod > cod2->cod)
        return MAIOR;
    else
        return IGUAL;
}


int exibe(void *dado) {
    Agendaa *contato = (Agendaa *) dado;
    printf("[%i], ", contato->cod);
    return SUCESSO;
}

void questao3(void) {
    pABB arvore = NULL;
    Agendaa temp;
    int escolha, qtd, i;

    do {
        system(LIMPA);
        printf("\tQ3 - ARVORE BINARIA DE PESQUISA\n\n"
                "\t[1] Criar arvore\n"
                "\t[2] Inserir contato na arvore\n"
                "\t[3] Remover contato da arvore SEM Recursao\n"
                "\t[4] Remover contato da arvore COM Recursao\n"
                "\t[5] Exibir todos os contatos na arvore COM Recursao\n"
                "\t[6] Exibir todos os contatos na arvore SEM Recursao\n"
                "\t[0] Voltar programa principal\n"
                "Opcao:__[");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
            {
                if (arvore != NULL)
                    printf("Voce ja criou a arvore!\n");
                else {
                    if (!criaABB(&arvore, sizeof (Agendaa)))
                        printf("Erro ao criar arvore.\n");
                    else
                        printf("\nArvore criada com sucesso.\n");
                }
            }
                break;
            case 2:
            {
                if (arvore == NULL)
                    puts("Voce deve primeiro criar uma arvore!");
                else {
                    puts("Deseja inserir qntos elementos?");
                    scanf(" %d", &qtd);
                    for (i = 0; i < qtd; i++) {
                        puts("-----------------------------------");
                        printf("\tCodigo:__");
                        scanf("%d", &temp.cod);
                        //fflush(stdin);
                        //__fpurge(stdin);
                        puts("\tNome: Fulano Default");
                        strcpy(temp.nome, "Fulano Default");
                        // fgets(temp.nome, T_NOME * sizeof (char), stdin);
                        //fflush(stdin);
                        //__fpurge(stdin);
                        puts("\tEndereco: Av. M. Metzner");
                        strcpy(temp.end, "Av. M. Metzner");
                        //fgets(temp.end, T_END * sizeof (char), stdin);
                        //fflush(stdin);
                        //__fpurge(stdin);
                        puts("\tFone: 4732345678\n");
                        strcpy(temp.fone, "4732345678");
                        //fgets(temp.fone, T_FONE * sizeof (char), stdin);
                        //fflush(stdin);
                        //__fpurge(stdin);
                        if (insereABB(arvore, &temp, compara))
                            printf("Contato %d inserido com sucesso!\n\n", temp.cod);
                        else printf("\nERRO! Problema de insercao na Arvore ou ja existe!\n");
                    }
                }
            }
                break;
            case 3:
            {
                if (arvore == NULL)
                    printf("Voce deve primeiro criar uma arvore e inserir um Contato!\n");
                else {
                    printf("Digite um codigo: ");
                    scanf("%d", &temp.cod);
                    if (!removeABB(arvore, &temp, compara))
                        printf("Erro ao remover elemento.\n");
                    else
                        printf("Contato %d removido.\n", temp.cod);
                }
            }
                break;
            case 4:
            {
                if (arvore == NULL)
                    printf("Voce deve primeiro criar uma arvore e inserir um Contato!\n");
                else {
                    printf("Digite um codigo: ");
                    scanf("%d", &temp.cod);
                    if (!removeRecABB(arvore, &temp, compara))
                        printf("Erro ao remover elemento.\n");
                    else
                        printf("Contato %d removido.\n", temp.cod);
                }
            }
                break;
            case 5:
            {
                if (arvore == NULL)
                    printf("Voce deve primeiro criar uma arvore!\n");
                else {
                    printf("\n//------------------------------//"
                            "\nPercurso Em Ordem COM Recursao\n");
                    percursoOrdem(arvore, exibe);
                }
                break;
            }
            case 6:
            {
                if (arvore == NULL)
                    printf("Voce deve primeiro criar uma arvore!\n");
                else {
                    printf("\n//------------------------------//"
                            "\nPercurso Ordem SEM Recursao\n");
                    percursoOrdemNaoRecursivo(arvore, exibe);
                }
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
    } while (escolha != 0);
}
