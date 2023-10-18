/*
    Lista duplamente encadeada.
*/
#include <stdio.h>
#include <stdlib.h>

typedef int TipoItem;

typedef struct no{ //estrutura para lista duplamente encadeada
    TipoItem info;
    struct no * ant; //ponteiro para o elemento anterior
    struct no * prox; //ponteiro para o próximo elemento;
}Lista;

int vazia(Lista * l){
    return (l == NULL);
}

void limpar_lista(Lista * l){
    if(!vazia(l)){
        Lista * aux = l->prox;
        free(l);
        limpar_lista(aux);
    }
}

void imprimir(Lista * l){
    if(!vazia(l)){
        printf("%d ", l->info);
        imprimir(l->prox);
    }
}

Lista * inserir_cabeca(Lista * l, TipoItem info){
    Lista * aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    aux->ant = NULL;
    aux->prox = l;
    
    if(!vazia(l)){
        l->ant = aux;
    }
    
    return aux;
}

Lista * inserir_cauda(Lista * l, TipoItem info){
    if(vazia(l)){
        Lista * aux= (Lista*) malloc(sizeof(Lista));
        aux->info = info;
        aux->ant = l;
        aux->prox = NULL;
        l = aux;
        return l;
    }
    l->prox = inserir_cauda(l->prox, info);
    return l;
}

Lista * remover(Lista * l, TipoItem info){
    if(vazia(l)) return NULL;
    
    if(l->info == info){ //Quando encontra a info a ser retirada da lista
        Lista * temp = l->prox; //guarda o proximo nó
        free(l); //libera o nó atual (o que contem a info que queremos remover)
        
        if(!vazia(temp)){ 
            temp->ant = l-> ant;
        }
        
        temp = remover(temp, info); //caso queira excluir todos as ocorrencias de uma info
        return temp;
    }
    
    l->prox = remover(l->prox, info);
    
    if(!vazia(l->prox)){
        l->prox->ant = l;
    }
    
    return l;
}

int main()
{
    Lista * l1 = NULL;
    Lista * l2 = NULL;
    
    l1 = inserir_cabeca(l1, 1);
    l1 = inserir_cabeca(l1, 2);
    l1 = inserir_cabeca(l1, 3);
    l1 = inserir_cabeca(l1, 4);
    l1 = inserir_cabeca(l1, 4);
    l1 = inserir_cabeca(l1, 4);
    l1 = inserir_cabeca(l1, 5);
    
    printf("Lista 1: ");
    imprimir(l1);
    printf("\n");
    
    l2 = inserir_cauda(l2, 5);
    l2 = inserir_cauda(l2, 6);
    l2 = inserir_cauda(l2, 7);
    l2 = inserir_cauda(l2, 8);
    
    printf("Cabeca de l2: %d\n\n", l2->info);
    printf("Lista 2: ");
    imprimir(l2);
    printf("\n");
    
    l1 = remover(l1, 5);
    l1 = remover(l1, 4);
    l1 = remover(l1, 1);
    //l1 = remover(l1, 3);
    
    l2 = remover(l2, 8);
    l2 = remover(l2, 6);
    
    printf("Lista 1: ");
    imprimir(l1);
    printf("\n");
    
    printf("Lista 2: ");
    imprimir(l2);
    printf("\n");
    
    limpar_lista(l1);
    limpar_lista(l2);
    l1 = NULL;
    l2 = NULL;
    
    return 0;
}

