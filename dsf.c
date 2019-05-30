#include <stdlib.h>
#include <stdio.h>

enum mark{n_visitado = 0, visitado = 1 };

typedef struct no{
    int vertice;
    int custo;
    struct no* next;
}no;

typedef struct grafro{   
    struct no* adj;
    struct no* tail;
    int t_vertices;
    int t_arestas;

}grafro;

no* criar_no(){
    no* n = (no*)malloc(sizeof(no));
    return n;
}

grafro* criar_grafro(int t_vertices){
    grafro* g               = (grafro*)malloc(sizeof(grafro));
    g->adj                  = (no*)malloc(t_vertices*sizeof(no));
    g->tail                 = (no*)malloc(t_vertices*sizeof(no));
    g->t_arestas            = 0;
    g->t_vertices           = t_vertices;
    return g;
}

void add_aresta(grafro* g, int origem, int destino, int custo){
    no* temp;
    if( g->adj[origem].next == NULL ){
        g->adj[origem].next     = criar_no();
        temp                    = g->adj[origem].next;
        temp->vertice           = destino;
        temp->custo             = custo;
        g->t_arestas            ++;
        g->tail[origem].next    = criar_no();
        g->tail[origem].next    = temp;
    }else
    {
        temp                    = g->tail[origem].next;
        temp->next              = criar_no();
        temp->next->vertice     = destino;
        temp->next->custo       = custo;
        g->tail[origem].next    = temp->next;         
        g->t_arestas++; 
    }
    
}

void show_grafro(grafro* g){
    for( int i = 0 ; i < g->t_vertices ; i++){
        printf("|%d|->",i);
        for (no* cur = g->adj[i].next; cur != NULL ; cur = cur->next)
        {
            printf("|%d|--%d-->",cur->vertice,cur->custo);
        }
        printf("\n");
    }
}

int main(){

    grafro* g = criar_grafro(10);
    add_aresta(g,1,2,10);
    add_aresta(g,1,3,10);
    add_aresta(g,1,5,10);
    add_aresta(g,6,3,10);
    add_aresta(g,8,3,10);




    show_grafro(g);
    return 0;
}