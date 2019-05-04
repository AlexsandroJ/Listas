#include <stdio.h>
#include <stdlib.h>

typedef struct no{

    int elemento;
    struct no* next;

}no;

typedef struct lista{

    int tamanho;
    struct no* head;

}lista;

lista* criar_lista();

void adicionar_fim(lista* l, int elemento);

void printar_lista(lista* l);

void subistituir_em_ID(lista* l, int id, int elemento);

void adicionar_em_ID(lista* l, int id, int elemento);

void buscar(lista* l, int id);

void deletar(lista* l, int id);

void apagar_lista(lista* l);
