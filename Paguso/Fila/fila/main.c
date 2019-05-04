#include "fila.h"

int main()
{
    fila* f;
    f = criar_fila();
    adicionar_na_fila(f,1);
    adicionar_na_fila(f,2);
    adicionar_na_fila(f,3);
    adicionar_na_fila(f,4);
    printf("\nTamanho:%d",tamanho_da_fila(f));
    printar_a_fila(f);
    adicionar_na_fila(f,10);
    adicionar_na_fila(f,20);
    adicionar_na_fila(f,30);
    adicionar_na_fila(f,40);
    printf("\nTamanho:%d",tamanho_da_fila(f));
    printar_a_fila(f);
    retirar_da_fila(f);
    retirar_da_fila(f);
    retirar_da_fila(f);
    retirar_da_fila(f);
    retirar_da_fila(f);
    retirar_da_fila(f);
    retirar_da_fila(f);
    printf("\nTamanho:%d",tamanho_da_fila(f));
    printar_a_fila(f);
    apagar_a_fila(f);
    printar_a_fila(f);


    return 0;
}
