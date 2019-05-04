#include "lista.h"

lista* criar_lista(){

    lista* l;
    l = (lista*) calloc(1,sizeof(lista));
    l->head = (no * ) calloc(1,sizeof(no));
    l->tamanho = 0;
    return l;
}

void adicionar_fim(lista* l, int elemento){

    if( l->head->next == NULL ){

        l->head->next = (no * ) calloc(1,sizeof(no));
        l->head->next->elemento = elemento;
        l->tamanho = 1;
    }else{

        no* cur;
        cur = (no*)calloc(1,sizeof(no));
        cur = l->head->next;
        while( cur->next != NULL){
            cur = cur->next;
        }
        cur->next = (no*)calloc(1,sizeof(no));
        cur->next->elemento = elemento;
        l->tamanho ++;
    }
}

void printar_lista(lista* l){

    no* cur = l->head->next;
    int id = 0;;
    if( l->head == NULL){

        printf("\n\t\tLista Vazia\n");
    }else{

        while( cur != NULL){
            printf("|ID%d|Elemento:%d\n",id,cur->elemento);
            cur = cur->next;
            id++;
        }
    }
}

void subistituir_em_ID(lista* l, int id, int elemento){

    no* cur = l->head;

    for(int buscar_id = 0; cur != NULL && buscar_id < id ; buscar_id++){

        cur = cur->next;
    }
    if( cur == NULL){

        printf("\n\t\tID INVALIDO!!!\n");

    }else{


        cur->next->elemento = elemento;
    }

}

void adicionar_em_ID(lista* l, int id, int elemento){

    no* cur = l->head;

    for( int buscar_id = 0 ; cur != NULL && buscar_id < id  ; buscar_id++){

        cur = cur->next;

    }

    if( cur == NULL ){

        printf("\n\t\tID INVALIDO!!!\n");

    }else{

        no* aux;
        aux = (no*)calloc(1,sizeof(no));
        aux->elemento = elemento;
        aux->next = cur->next;
        cur->next = aux;
        l->tamanho++;
    }
}

void buscar(lista* l, int id){

    no* cur = l->head;

    for( int buscar_id = 0 ; cur != NULL && buscar_id < id ; buscar_id++){

        cur = cur->next;

    }
    if( cur == NULL){

        printf("\n\t\tID NAO EXISTE\n");
    }else{

        printf("\n|ID:%d|Elemento:%d\n",id,cur->next->elemento);

    }
}

void deletar(lista* l, int id){

    no* cur = l->head;

    for( int buscar_id = 0 ; cur != NULL && buscar_id < id ; buscar_id ++){

        cur = cur->next;
    }
    if( cur == NULL ){

        printf("\n\t\tID INVALIDO!!!\n");
    }else{

        no* aux = cur->next->next;
        free(cur->next);
        cur->next = aux;
        l->tamanho--;
    }
}

void apagar_lista(lista* l){

    no* atual;
    while( l->head != NULL ){

        atual = l->head;
        l->head = l->head->next;
        free(atual);
    }
    free(l->head );
    free(l );
    printf("\n\t\tLista Apgada\n");
}
