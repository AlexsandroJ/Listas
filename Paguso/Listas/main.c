#include "lista.h"

int main()
{
    lista* l;
    l = criar_lista();
    adicionar_fim(l,1);
    adicionar_fim(l,2);
    adicionar_fim(l,3);
    adicionar_fim(l,4);
    adicionar_fim(l,5);
    adicionar_fim(l,6);
    adicionar_fim(l,7);
    printar_lista(l);
    printf("_______________total %d\n",l->tamanho);
    subistituir_em_ID(l,1,0);
    subistituir_em_ID(l,10,0);
    printar_lista(l);
    printf("_______________total %d\n",l->tamanho);
    adicionar_em_ID(l,5,10);

    subistituir_em_ID(l,3,20);
    printar_lista(l);
    printf("_______________total %d\n",l->tamanho);
    deletar(l,0);
    printar_lista(l);
    printf("_______________total %d\n",l->tamanho);

    adicionar_em_ID(l,0,100);
    adicionar_em_ID(l,4,200);
    printar_lista(l);
    printf("_______________total %d\n",l->tamanho);
    buscar(l,5);
    buscar(l,0);

    apagar_lista(l);

    return 0;
}
