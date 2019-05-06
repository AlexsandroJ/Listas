#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Tam_Rips 1000
#define Tam_Array_Angentes 1000000

typedef struct Tab_Agentes{
    int ID;
    int Esquad;
    int ID_Heap;

}Tab_Agentes;

typedef struct Agente{

    int ID;
    int T;
    int R;
    int Esquad;

}Agente;

Tab_Agentes Agentes_ID[Tam_Array_Angentes];

typedef struct heap{

    int function;
    int total;
    struct Agente* Agentes;
    
}heap;

int get_pai(int n){

    return (int)(n/2);
}

int get_filho(int n){

	return (2*n);
}

void show_heap( heap heap){
    int i = 1,n = 1, resultado = 0, num;
    printf("\n");
    switch(heap.function){
        
        case 0:{
            printf(" Menor T\n");
            
            for( i = 1 ; i <= heap.total  ; i++){

                printf(" |%d|ID:%d|%d ",i,heap.Agentes[i].ID,heap.Agentes[i].T);
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
        }break;
        case 1:{
            
            printf(" Maior T\n");
            for( i = 1 ; i <= heap.total  ; i++){

                printf(" |%d|%d|%d ",i,heap.Agentes[i].ID,heap.Agentes[i].T);
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
        }break;
        case 2:{
            printf(" Menor R\n");
            for( i = 1 ; i <= heap.total  ; i++){

                printf(" |%d|%d|%d ",i,heap.Agentes[i].ID,heap.Agentes[i].R);
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
        }break;
        case 3:{
            printf(" Maior T\n");
            for( i = 1 ; i <= heap.total  ; i++){

                 printf(" |%d|%d|%d ",i,heap.Agentes[i].ID,heap.Agentes[i].R);
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

        }break;
    }

    printf("\n");
}

void swap(Agente* Agente1, Agente* Agente2, int ID1, int ID2){

    Agente* temp = (Agente*)malloc(1*sizeof(Agente));
    *temp = *Agente2;
    *Agente2 = *Agente1;
    *Agente1 = *temp;

    Agentes_ID[Agente1->ID].ID_Heap =  ID1;
    Agentes_ID[Agente2->ID].ID_Heap =  ID2;
}

int function_heap(int Criterio, Agente filho, Agente pai){
    if(filho.ID == 0 || pai.ID == 0){
        return -1;
    }else{

        switch(Criterio){
            case 0:{
                if( filho.T < pai.T){

                    return 1;

                }else if( filho.T == pai.T ){

                    if( filho.R > pai.R){

                        return 1;

                    }else if( filho.R == pai.R ){

                        if(filho.ID < pai.ID  ){

                            return 1;

                        }else return -1;

                    }else return -1;

                }else return -1;

            }break;

            case 1:{

                if( filho.T > pai.T){

                    return 2;

                }else if( filho.T == pai.T ){

                    if( filho.R < pai.R){

                        return 2;

                    }else if( filho.R == pai.R ){

                        if(filho.ID < pai.ID  ){

                            return 2;

                        }else return -1;

                    }else return -1;

                }else return -1;

            }break;

            case 2:{

                if( filho.R < pai.R){

                    return 1;

                }else if( filho.R == pai.R ){

                    if( filho.T > pai.T){

                        return 1;

                    }else if( filho.T == pai.T ){

                        if(filho.ID < pai.ID  ){

                            return 1;

                        }else return -1;

                    }else return -1;

                }else return -1;
            }break;

            case 3:{

                if( filho.R > pai.R){

                    return 2;

                }else if( filho.R == pai.R ){

                    if( filho.T < pai.T){

                        return 2;

                    }else if( filho.T == pai.T ){

                        if(filho.ID < pai.ID  ){

                            return 2;

                        }else return -1;

                    }else return -1;

                }else return -1;
            }break;  
        }
    }
}

int bubble_up(heap *heap, int ID){
	int ID_Pai;

    if( ID == 1){

        return ID;

    }else{

        ID_Pai = get_pai(ID);
        //printf("pai %d %d %d\n",ID_Pai,heap->Agentes[ ID_Pai ].R,heap->function);
        int Criterio = function_heap( heap->function, heap->Agentes[ ID ], heap->Agentes[ ID_Pai ]);
        //printf("\n\t criterio porraa %d\n", Criterio);
        if( Criterio == -1 )
        {   
            //printf("\n\tOK\n");
            return ID;

        }else{


            /*
            switch(heap->function){
                case 0:{
                    printf("Menor T %d < %d \n",heap->Agentes[ ID ].T, heap->Agentes[ ID_Pai ].T);
                }break;
                case 1:{
                    printf("Maior T %d > %d \n",heap->Agentes[ ID ].T, heap->Agentes[ ID_Pai ].T);
                }break;
                case 2:{
                    printf("Menor R %d < %d \n",heap->Agentes[ ID ].R, heap->Agentes[ ID_Pai ].R);
                }break;
                case 3:{
                    printf("Maior T %d > %d \n",heap->Agentes[ ID ].R, heap->Agentes[ ID_Pai ].R);
                }break;
            }*/

            swap( &heap->Agentes[ ID ], &heap->Agentes[ID_Pai], ID, ID_Pai);
            //printf("Apos Swap ID:%d %d - %d ID:%d \n",ID,heap->Agentes[ ID ].R, heap->Agentes[ ID_Pai ].R,ID_Pai);
            
            bubble_up(heap, get_pai(ID));
            
        }
    }
}

int Insert_heap( heap *heaps,  Agente Agentes){
	
	if( heaps->total >= Tam_Rips)
		printf("OVERFLOW\n");

	else{
		
		heaps->total += 1;
        
		//printf("\n\tTotal na Heap:%d\n",heaps->total);
		heaps->Agentes[heaps->total] = Agentes;

		return bubble_up(heaps, heaps->total);
	}
    
}

void bubble_down(heap *heap, int ID){

    if( ID*2 + 1<= heap->total ){

        int ID_Filho1, ID_Filho2; 
        
        int min_ou_max_ID; 

        ID_Filho1 = 2*ID;
        ID_Filho2 = ID_Filho1 + 1;

       
        int Criterio = function_heap( heap->function, heap->Agentes[ ID_Filho1 ], heap->Agentes[ ID_Filho2 ]);
        
        if( Criterio == -1 ){
            
            Criterio = function_heap( heap->function, heap->Agentes[ ID ], heap->Agentes[ ID_Filho2 ]);
            min_ou_max_ID = ID_Filho2;

            
        }else if( Criterio != -1){

            Criterio = function_heap( heap->function, heap->Agentes[ ID ], heap->Agentes[ ID_Filho1 ]);
            min_ou_max_ID = ID_Filho1;
        }

        if( Criterio == -1){

            swap( &heap->Agentes[ID] , &heap->Agentes[min_ou_max_ID] , ID, min_ou_max_ID);
            //printf("\tTrocando\n");
            bubble_down( heap, min_ou_max_ID );
        }
    }
}

int Remove_da_heap( heap* heaps, int ID){
    Agente Agentes;
    int ID_Che;
    if( ID > heaps->total){
        return -1;
    }else {

        if( Agentes_ID[ID].ID == ID ){

            heaps->Agentes[ID] = heaps->Agentes[heaps->total];
            heaps->Agentes[heaps->total] = Agentes;// apagar
            heaps->total -=1;
            //printf("\t\tTotal %d",heaps->total);
            ID_Che = bubble_up(heaps, ID);
            if( ID_Che == ID){
                //printf("\tDencendo\n");
                bubble_down(heaps, ID);
            }
            
            return ID;

        }else{

            return -1;
        }
    }
}

void UDP( heap* heaps, int ID_na_Heap, Agente Agentes ){
    int ID;
    heaps->Agentes[   ID_na_Heap  ] =  Agentes;
    ID = bubble_up(heaps, ID_na_Heap);

    

    if( ID == ID_na_Heap ){
        
        bubble_down(heaps, ID_na_Heap);
    }
    

}


int main(){
    register int i,j;
    int S, ID, Q, P, Esqu_i, Esqu_j;
    char Op[4];
    struct heap* heaps;
    struct Agente Agentes;
    
    scanf("%d",&S);
    heaps = (heap*)malloc(S*sizeof(heap));
    
    for( i = 0; i < S ; i++){
        scanf(" %d %d ",&Q, &P);
        heaps[i].function = P;
        heaps[i].Agentes = (Agente*)malloc(Tam_Rips*sizeof(Agente));
        
        Agentes.Esquad = i;

        for( j = 0 ; j < Q ; j++){
            
            scanf(" %d %d %d ", &Agentes.ID, &Agentes.T, &Agentes.R );
            //printf(" ID: %d T:%d R:%d \n", Agentes.ID,Agentes.T,Agentes.R );
            ID = Insert_heap(&heaps[i],Agentes);
            Agentes_ID[Agentes.ID].ID =  Agentes.ID;
            Agentes_ID[Agentes.ID].Esquad =  i;
            Agentes_ID[Agentes.ID].ID_Heap =  ID;
            //printf("\n\t\tId %d Ret da heap na list / ID dele %d / ID na Lista: %d comp %d\n",ID , heaps[i].Agentes[ID].ID, Agentes_ID[Agentes.ID].ID, Agentes.ID);
            
        }
        //printf("\n Esquadrao %d",i);
        //show_heap(heaps[i]);

    }

    //printf(" \n\t\t ID Na Heap %d R %d\n",heaps[1].Agentes[10].ID, heaps[1].Agentes[10].R);
    //printf(" \n\t\t ID Na Heap pela lista  %d\n",Agentes_ID[3].ID_Heap);
    //printf(" \n\t\t Esquad  %d OK\n",Agentes_ID[3].Esquad);

    do{
        scanf(" %s",Op);
        //printf("\n\t\t\tEssa porra:%d \n",heaps[   1 ].total);
        if( strcmp(Op, "ADD") == 0 ){
            scanf(" %d %d %d %d",&Agentes.Esquad, &Agentes.ID, &Agentes.T, &Agentes.R);


            if( Agentes_ID[ Agentes.ID  ].ID_Heap  == 0){

                ID = Insert_heap(&heaps[Agentes.Esquad],Agentes);
                Agentes_ID[ Agentes.ID  ].ID =  Agentes.ID;
                Agentes_ID[ Agentes.ID  ].Esquad =  Agentes.Esquad;
                Agentes_ID[ Agentes.ID  ].ID_Heap =  ID;

            }else{
                
                ID = Agentes_ID[ Agentes.ID  ].ID_Heap;
                UDP( &heaps[Agentes.Esquad],ID, Agentes );
            }
        
            printf("%d %d %d\n",
                heaps[   Agentes.Esquad ].Agentes[   1  ].ID,
                heaps[   Agentes.Esquad ].Agentes[   1  ].T,
                heaps[   Agentes.Esquad ].Agentes[   1  ].R);
        
        }else if( strcmp(Op, "UPD") == 0 ){

            scanf(" %d %d %d", &Agentes.ID, &Agentes.T, &Agentes.R);
            ID = Agentes_ID[    Agentes.ID  ].ID_Heap;
            Agentes.Esquad = Agentes_ID[    Agentes.ID  ].Esquad;

            UDP( &heaps[Agentes.Esquad], ID, Agentes );
            
            printf("%d %d %d\n",
                heaps[   Agentes.Esquad ].Agentes[   1  ].ID,
                heaps[   Agentes.Esquad ].Agentes[   1  ].T,
                heaps[   Agentes.Esquad ].Agentes[   1  ].R);
        
        }else if( strcmp(Op, "MOV") == 0 ){

            scanf(" %d %d", &Esqu_i, &Esqu_j);
            
            if( heaps[   Esqu_i ].total > 0){

                Agente Agentes_i;
                Agentes_i = heaps[   Esqu_i ].Agentes[   1  ];
               
                Remove_da_heap( &heaps[Esqu_i], 1 );
                
                ID = Insert_heap(&heaps[Esqu_j],Agentes_i);
                Agentes_ID[ Agentes_i.ID  ].Esquad =  Esqu_j;
                Agentes_ID[ Agentes_i.ID  ].ID_Heap =  ID;

                if( heaps[   Esqu_i ].total > 0 ){

                    printf("%d %d %d ",
                    heaps[   Esqu_i ].Agentes[   1  ].ID,
                    heaps[   Esqu_i ].Agentes[   1  ].T,
                    heaps[   Esqu_i ].Agentes[   1  ].R);

                }else{
                    printf("-1 -1 -1 ");

                }

                printf("%d %d %d\n",
                    heaps[   Esqu_j ].Agentes[   1  ].ID,
                    heaps[   Esqu_j ].Agentes[   1  ].T,
                    heaps[   Esqu_j ].Agentes[   1  ].R);
            }
                
                        
        }else if( strcmp(Op, "CHG") == 0 ){
            
            scanf(" %d %d %d %d", &Esqu_i, &Esqu_j, &Q, &P);
            
            Agente Agentes_i;  
            
            for( i = 0 ; i < Q && heaps[   Esqu_i ].total >= 0 ; i++){

                Agentes_i = heaps[   Esqu_i ].Agentes[   1  ];
               
                Remove_da_heap( &heaps[Esqu_i], 1 );
                
                ID = Insert_heap(&heaps[Esqu_j],Agentes_i);
                Agentes_ID[ Agentes_i.ID  ].Esquad =  Esqu_j;
                Agentes_ID[ Agentes_i.ID  ].ID_Heap =  ID;

            }
            
            
            if( heaps[Esqu_i].function != P ){

                heaps[Esqu_i].function = P;

                for( i = heaps[   Esqu_i ].total ; i >= 1 ; i-- ){
                        printf("\t\tfoi\n");
                    ID = bubble_up(&heaps[   Esqu_i ], i  );
                    Agentes_ID[ heaps[   Esqu_i ].Agentes[   i  ].ID ].ID_Heap =  ID;

                }
            }

            if( heaps[   Esqu_i ].total > 0 ){
               
                
                printf("%d %d %d ",
                heaps[   Esqu_i ].Agentes[   1  ].ID,
                heaps[   Esqu_i ].Agentes[   1  ].T,
                heaps[   Esqu_i ].Agentes[   1  ].R);

            }else{
                printf("-1 -1 -1 ");

            }
            printf("%d %d %d\n",
                heaps[   Esqu_j ].Agentes[   1  ].ID,
                heaps[   Esqu_j ].Agentes[   1  ].T,
                heaps[   Esqu_j ].Agentes[   1  ].R);


            // Atualizar Criterio de Pioridade de  Esqu_i para P
        }else if( strcmp(Op, "KIA") == 0 ){

            scanf(" %d ", &Agentes.ID);

            Esqu_i = Agentes_ID[Agentes.ID].Esquad;
            //show_heap(heaps[Esqu_i]);

            ID = Agentes_ID[Agentes.ID].ID_Heap;
            
            Remove_da_heap( &heaps[Esqu_i], ID );
            //show_heap(heaps[Esqu_i]);

            printf("%d %d %d\n",
                heaps[   Agentes.Esquad ].Agentes[   1  ].ID,
                heaps[   Agentes.Esquad ].Agentes[   1  ].T,
                heaps[   Agentes.Esquad ].Agentes[   1  ].R);
        
        }

    }while( strcmp(Op, "END") != 0 );
    
    //show_heap(heaps[]);
    return 0;
}