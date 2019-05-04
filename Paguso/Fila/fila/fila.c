#include "fila.h"

fila* criar_fila(){

    fila* f;
    f = (fila*)calloc(1,sizeof(fila));
    f->head = (no*)calloc(1,sizeof(no));
    f->tail = (no*)calloc(1,sizeof(no));
    f->tamanho = 0;
    return f;
}

void adicionar_na_fila(fila* f, int elemento){

    no* cur = f->head;
    if( cur->next == NULL){

        cur->next = (no*)calloc(1,sizeof(no));
        cur->next->elemento = elemento;
        f->tamanho = 1;
        f->tail = cur->next;

    }else{

        while( cur->next != NULL){

            cur = cur->next;
        }
        cur->next = (no*)calloc(1,sizeof(no));
        cur->next->elemento = elemento;
        f->tail = cur->next;
        f->tamanho++;
    }
}

void retirar_da_fila(fila* f){

    no* primeiro = f->head->next;
    f->head->next = primeiro->next;
    free(primeiro);
    f->tamanho--;

}

void printar_a_fila(fila* f){

    if( f == NULL )
    {
        printf("\n\t\tFILA NAO EXISTE!!!\n");

    }else{

        if( f->head == NULL)
        {
            printf("\n\t\tFILA VAZIA!!!\n");
        }else{
            no* cur = f->head;
            printf("\n");
            while( cur->next != NULL ){
                cur = cur->next;
                printf("|%d|->",cur->elemento);
            }
            printf("NULL\n");
        }
    }
}

void apagar_a_fila(fila* f){

    no* cur = f->head;
    while( cur->next != NULL){
        cur = cur->next;
        f->head = cur->next;
        free(cur);
        free(f->head);
        free(f->tail);
        free(f);
    }
    printf("\n\t\tFILA APAGADA.\n");
}

int tamanho_da_fila(fila* f){

    return f->tamanho;
}
