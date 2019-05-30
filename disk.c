#include <stdlib.h>
#include <stdio.h>

typedef struct no{

    struct no* next;
    int v;
    int d;
}no;

typedef struct graf{
    int v;
    struct no* adj;
    struct no* tail;
    int size_v;
    int size_arest;
}graf;

typedef struct vertis{
    int d;
    int v;
}vertis;

typedef struct heap{
    vertis* vertis;
    int total;
}heap;

void show_heap( heap* heap){
    int i = 1,n = 1, resultado = 0;
    printf("\n");

    for( i = 1 ; i <= heap->total  ; i++){

        printf(" |%d|V:%d|D:%d ",i,heap->vertis[i].v,heap->vertis[i].d);
        n++;
        if( n >= resultado){
            
            if( resultado == 0){
                //printf("-%d-",resultado);
                resultado = 2;
            }else{
                resultado = (resultado*resultado);
            }
            
            n = 0;
            printf("\n");
        }  
    }
    printf("\n");
}

int get_pai(int n){
    return (int)(n/2);
}

int get_filho(int n){
	return (2*n);
}

heap* criar_heap(int v){
    heap* h = (heap*)malloc(sizeof(heap));
    h->vertis = (vertis*)malloc(sizeof(vertis));
    h->total = 0;
}

void swap(heap* heap, int ID1, int ID2){
    vertis temp = heap->vertis[ID1];
    heap->vertis[ID1] = heap->vertis[ID2];
    heap->vertis[ID2] = temp;
}

int bubble_up(heap *heap, int ID){
	int ID_Pai, Criterio;
    if( ID == 1){
        return ID;
    }else{
        ID_Pai = get_pai(ID);
        
        if( heap->vertis[ID_Pai].d > heap->vertis[ID].d )
        {   
            swap( heap, ID, ID_Pai);
            bubble_up(heap, ID_Pai);
        }
    }
}

int Insert_heap( heap *heap, vertis v){
    heap->total += 1;
    heap->vertis[heap->total ] = v;
    return bubble_up(heap, heap->total);
}

void bubble_down(heap *heap, int ID){
    int ID_Filho1, ID_Filho2, min_ou_max_ID; 
    ID_Filho1 = 2*ID;
    ID_Filho2 = ID_Filho1 + 1;
    if( ID*2 < heap->total   ){
        if( heap->vertis[ID_Filho1].d > heap->vertis[ID_Filho2].d ){
            min_ou_max_ID = ID_Filho1;
        }else{
            min_ou_max_ID = ID_Filho2;
        }
        swap( heap, ID, min_ou_max_ID);
        bubble_down( heap, min_ou_max_ID );
    }else if(ID < heap->total){
        if( heap->vertis[1].d > heap->vertis[2].d ){
            swap( heap, 1, 2);
        }
    }
}

vertis min_heap( heap* heap){
    int ID_Che;
    vertis valor;
    if( heap->total > 0 ){
        valor = heap->vertis[heap->total];
        heap->total -=1;
        heap->vertis[1] = heap->vertis[heap->total];
        bubble_down(heap, 1);
        return valor;
    }
}

no* cria_no(){
    no* n = (no*)malloc(sizeof(no));
    return n;
}

graf* criar_grap(graf* g, int v){
    g = (graf*)malloc(sizeof(graf));
    g->adj = (no*)malloc(v*sizeof(no));
    g->tail = (no*)malloc(v*sizeof(no));
    for( int i = 0 ; i < v ; i++){
        g->adj[i].next = NULL;
        g->tail[i].next = cria_no();
    }
    g->size_v = v;
    g->size_arest= 0;
}

void add_arest(graf* g, int v1, int v2, int peso){
    no* aux1;

    if( g->adj[v1].next ==  NULL ){
        g->adj[v1].next = cria_no();
        aux1 = g->adj[v1].next;
        aux1->v = v2;
        aux1->d = peso;
        g->tail[v1].next =  aux1;
        g->size_arest++;

    }else{

        aux1 = g->tail[v1].next;
        aux1->next  = cria_no();
        aux1->next->v = v2;
        aux1->next->d = peso;
        g->tail[v1].next =  aux1->next;
    }
}

void print_adj(graf* g){
    no* cur;

    for(int i = 0 ; i < g->size_v ; i++){
        if( g->adj[i].next != NULL){
            cur = g->adj[i].next ;
        }
        printf("|%d|",i);
        while ( cur != NULL)
        {
            printf("--%d-->|%d|",cur->d,cur->v);
            cur = cur->next;
        }
        printf("\n");
    }
}

void dikst(graf* g, heap* heap, int inicio, int fim){

    vertis dist[g->size_v], aux, v_atual, v_anterior;
    no* cur = g->adj[inicio].next;
    int mark[g->size_v];
    
    for (int i = 0; i < g->size_v; i++)
    {
        dist[i].d       = 0x3f3f3f;
        dist[i].v       = -1;
        mark[i]         = 0;
    }
    dist[inicio].d      = 0;
    v_atual.v           = inicio;
    v_atual.d           = 0;
    v_anterior          = v_atual;
    Insert_heap(heap, v_atual );
    while (heap->total > 0)
    {
        v_atual = min_heap(heap);
        
        
        if( mark[v_atual.v] == 0){
            mark[v_atual.v] == 1;
            
            for( no* cur = g->adj[v_atual.v].next ; cur != NULL ; cur = cur->next){
                v_atual.v = cur->v;
                v_atual.d = cur->d;
                if( dist[v_atual.v].d > v_atual.d + v_anterior.d ){
                    dist[v_atual.v].d = v_atual.d + v_anterior.d;
                    dist[v_atual.v].v = v_atual.v;
                    Insert_heap(heap,v_atual);
                    printf("D:%d V:%d\n",dist[v_atual.v].d, dist[v_atual.v].v);
                }
            }
        }
        show_heap(heap);
    }  
    printf("%d\n",dist[fim].d);
}
int main(){

    graf* g = criar_grap(g, 10);
    heap* h = criar_heap(10);
    add_arest(g,3,6,8);
    add_arest(g,1,3,9);
    add_arest(g,5,2,2);
    add_arest(g,4,3,2);
    add_arest(g,0,4,2);
    add_arest(g,6,5,1);
    add_arest(g,1,5,20);
    print_adj(g);
    
    dikst(g,h,1,5);

    return 0;
}