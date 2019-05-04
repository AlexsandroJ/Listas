#include <stdlib.h>
#include <stdio.h>
typedef struct no{
    int valor;
    struct no* esq;
    struct no* dir;
}no;

typedef struct arv{

    int altura;
    struct no* raiz;

}arv;

void em_ordem(no* folha){
    if( folha != NULL){
        em_ordem(folha->esq);
        printf("%d",folha->valor);
        printf(">");
        em_ordem(folha->dir);
    }
}
void pre_ordem(no* folha){
    if( folha != NULL){
        printf("%d",folha->valor);
        printf(">");
        pre_ordem(folha->esq);
        pre_ordem(folha->dir);
    }
    
}
void pos_ordem(no* folha){
    if( folha != NULL){
        
        pos_ordem(folha->esq);
        pos_ordem(folha->dir);
        printf("%d",folha->valor);
        printf(">");
    } 
}
arv* criar_arvore(){
    arv* a = (arv*)calloc(1,sizeof(arv));
    a->raiz = NULL;
    a->altura = 0;
    return a;
}
no* novo_no(int valor){
    no* new = (no*)calloc(1,sizeof(no));
    new->valor = valor;
    new->esq = NULL;
    new->dir = NULL;
    return new;
}
no* busca( no* atual, int valor){

    if( atual == NULL){
        printf("\t\Nao existe\n");
    }else{
        if( valor == atual->valor ){
            printf("\t%d\n",valor);
            return atual;
        }
        else if(  valor < atual->valor ){
            busca(atual->esq, valor);
        }else{
            busca(atual->dir, valor);
        }
    }
    return NULL;
}
void adicionar( arv* a, int valor){
    no* cur = a->raiz;
    no* aux;
    if( cur == NULL){
        cur = novo_no(valor);
        a->raiz = cur;
    }else{
        while( cur != NULL){
            aux = cur;
            if( valor < cur->valor ){
                cur = cur->esq;
            }else{
                cur = cur->dir;
            }
        }
        cur = novo_no(valor);
        if( valor < aux->valor){
            
            aux->esq = cur;
        }else{
            
            aux->dir = cur;
        }
    }
}
void remover( arv* a, int valor){
    no* cur = a->raiz;
    no* anterior;
    if( cur != NULL){
        while( cur->valor != valor && cur->esq != NULL && cur->dir != NULL){
            anterior = cur;
            if( valor < cur->valor ){
                cur = cur->esq;
            }else{
                cur = cur->dir;
            }
        }

        if( cur->esq == NULL && cur->dir == NULL){
            free(cur);
        }else if( cur->esq == NULL ){
            anterior->esq = cur->dir;
            free(cur);
        }else{
            no* aux = cur;
            while( aux->esq != NULL){
                anterior = aux;
                aux = aux->esq;
            }
            cur->valor = aux->valor;
            anterior->esq = aux->dir;
            free(aux); 
            
        }
    }
}

int main(){

    arv* arv = criar_arvore();

    adicionar(arv, 50);
    adicionar(arv, 100);
    adicionar(arv, 30);
    adicionar(arv, 40);
    adicionar(arv, 20);
    adicionar(arv, 35);
    adicionar(arv, 45);
    adicionar(arv, 37);
    adicionar(arv, 36);

    em_ordem(arv->raiz);
    printf("\n");
   // pre_ordem(arv->raiz);
    //printf("\n");
    //pos_ordem(arv->raiz);
    //printf("\n");

    remover(arv,35);

    em_ordem(arv->raiz);
    printf("\n");

    remover(arv,30);
    em_ordem(arv->raiz);
    printf("\n");

    return 0;
}