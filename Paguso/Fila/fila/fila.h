#include <stdio.h>
#include <stdlib.h>

typedef struct no{

    int elemento;
    struct no* next;

}no;

typedef struct fila{

    int tamanho;
    struct no* head;
    struct no* tail;

}fila;

fila* criar_fila();

void adicionar_na_fila(fila* f, int elemento);

void retirar_da_fila(fila* f);

void printar_a_fila(fila* f);

void apagar_a_fila(fila* f);

int tamanho_da_fila(fila* f);
