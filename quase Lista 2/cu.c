#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct elemento{

    bool ocupado;
    int ocu;
    char key[12];
	int valor_de_ordem;
}elemento;

typedef struct localizacao{

    int estante;
    int andar;
    int copias;
	int nucleo;
	int andares_com_copias;
	int ultimo_andar;
	int ultima_posicao;
    char key[12];
    bool existe;


}localizacao;

typedef struct hash{

    elemento** armario;
    int quantidade_andares;
    int espacos_por_andar;
    bool andares_ocupados[11];
}hash;

hash* criar_hash(int quantidade_andares, int espacos_por_andar){

    hash* h;
    register int i,j;
    localizacao* l;
    h = (hash*)calloc(1,sizeof(hash));
    h->armario = (elemento**)calloc(quantidade_andares,sizeof(elemento*));
    h->espacos_por_andar = espacos_por_andar;
    h->quantidade_andares = quantidade_andares;
    for( i = 0 ; i < quantidade_andares ; i++){

        h->armario[i] = (elemento*)calloc(espacos_por_andar,sizeof(elemento));
        h->andares_ocupados[i] = false;
        for( j = 0 ; j < espacos_por_andar ; j++){
            h->armario[i][j].ocupado = false;
            h->armario[i][j].ocu = 0;
            strcpy( h->armario[i][j].key , "XXXXXXXXXX" );
			//h->armario[i][j].valor_de_ordem = 99999;
        }
    }
    return h;
}
hash** criar_armarios(int quantidade_de_armarios , int espacos_por_andar){
    hash** h;
    register int i;
    h = (hash**)calloc(quantidade_de_armarios,sizeof(hash*));
    for( i = 0 ; i < quantidade_de_armarios ; i++){

        h[i] = criar_hash(11,espacos_por_andar);
    }
    return h;
}
void printar_hash(hash* h){

    register int i, j;
    for( i = 0 ; i < h->quantidade_andares ; i ++){
        printf("|Andar %d -%d",i, h->andares_ocupados[i]);
        for( j = 0 ; j < h->espacos_por_andar ; j++){
            printf("|%d-%s-%d|",j,h->armario[i][j].key ,h->armario[i][j].ocu );
        }
        printf("|\n");
    }
}
void printar_armarios(hash** h, int quantidade_de_armarios){

    register int i;
    for( i = 0 ; i < quantidade_de_armarios ; i ++){
        printf("\n\t\t|   Armario |%d|   |\n",i);
        printar_hash(h[i]);
        //printf("______________________________________________________________________________________________________________________________________________________\n");
    }
}
localizacao* localizar(char key[10], int quantidade_de_armarios){
    register int i; 
    int nucleo = 0;
    int salvar_indice;
    int calculo;
    bool erro = false;
    localizacao* local;
    local = (localizacao*)calloc(1,sizeof(localizacao));
    if( key[9] == 120){
        key[9] = 58;
        //printf("%c %d\n",key[9],key[9]-48);

    }
    for( i = 0 ; i < 9 ; i++){
        //printf("%d*%d + ",(key[i] - 48),(10 - i));
        if( key[i] == 63 ){
            erro = true;
            //printf("Erro ");
            salvar_indice = i;
        }else{
            nucleo = (key[i] - 48)*(10 - i) + nucleo;
        }
    }
    for( i = 0 ; erro == true  ; i++){

        calculo = (10 - salvar_indice)*i + nucleo;

        //printf(" calculo: %d DV:%d Modulo: %d nucleo:%d \n",calculo, key[9] - 48, (11 - calculo%11)%11, nucleo );
        
        if( (11 - calculo%11)%11 == ( key[9] - 48 ) || i == 9){
            //printf("Caracter que falta é o %d\n", i);
            nucleo = calculo;
            erro = false;
			key[salvar_indice] = i + 48;

        }
    }
	if( key[9] == 58){
		key[9] = 120;
	}
	
	
	local->nucleo = nucleo;
    local->estante = nucleo%quantidade_de_armarios;
	
	if( key[9] == 63){
		
		key[9] = ( (11 - nucleo%11)%11 ) + 48 ;

		if( key[9] == 58){
		key[9] = 120;
		}
		//printf("DV atual:%c no key:%s\n",key[9],key);
	}
	strcpy( local->key , key );
    local->andar = (11 - nucleo%11)%11;
    //printf("Localizar:\tEstante: %d Andar: %d Nucleo:%d\n",local->estante,local->andar,local->nucleo);
    return local;
}
void ordenar( hash* h,localizacao* l, int andar, int fim ){
	elemento aux;
	int caracter = 0;
	bool iguais = false;
	
				
	for(int i = 0; i <  h->espacos_por_andar  ; i++) {

        for(int j = i + 1; j <  h->espacos_por_andar ; j++) {


			if ( strcmp( h->armario[andar][i].key, h->armario[andar][j].key ) > 0 ) {
				
				aux = h->armario[andar][i];
				h->armario[andar][i] = h->armario[andar][j];
				h->armario[andar][j] = aux;
				
	        }
        }
    }
}
void adicionar(hash* h, localizacao* l){
    int copias = l->copias;
    bool estado_inicial_do_primeiro_livro = h->armario[l->andar][0].ocu ;
    int id_andar = l->andar;
	
    while( l->copias != 0 ){ 

    	while(  h->andares_ocupados[id_andar] == true ){

    		ordenar(h,l,id_andar,0);
    		id_andar++;
    		if( id_andar > 10){
    			id_andar = 0;
    		}

    	}
    	
    	for( int i = 0 ; i < h->espacos_por_andar && l->copias != 0 ; i++){

    		if( h->armario[id_andar][i].ocu == 0){
    			
    			strcpy( h->armario[id_andar][i].key, l->key );
    			h->armario[id_andar][i].ocu = 1;
    			h->armario[id_andar][i].valor_de_ordem = l->nucleo;
    			ordenar(h,l,id_andar,0);
    			l->copias--;
    			//printf("\t\tAchou livre: andar:%d Posicao:%d posicao ocupada:%d\n",id_andar,i,h->armario[id_andar][i].ocu); 
    			if( i == h->espacos_por_andar -1 ){
    			
    				h->andares_ocupados[id_andar] = true;
    				//printf("\t\t andar:%d cheio\n",id_andar,i);

    	
    			}
    		}
    		if( l->copias == 0){
    			//ordenar(h,l,id_andar,0);
    		}

    	}
    	ordenar(h,l,id_andar,0);
    }

}
int buscar(hash* h, char v[], int andar) {
   int e, m, d;
   e = 0; d = h->espacos_por_andar -1 ;

   while (e <= d) { 
      m = (e + d)/2; 
	  
	  //printf("m:%d e:%d d:%d Valor:%s \n",m,e,d,h->armario[l->andar][m].key);
	  
      if ( strcmp( v, h->armario[andar][m].key ) == 0)
	  {
		  //printf("\t\tAchou\n"); 
		  //printf("Valor:%d Andar:%d Posicao:%d\n",v[m].valor_de_ordem,l->andar,m);
		  return m;
	  }else if ( strcmp( v , h->armario[andar][m].key ) > 0  ){
			
			e = m + 1;
	  }
      else d = m - 1;
   }
   //printf("nao achou\n");
   return -1;
}


int buscar_na_hash(hash* h, localizacao* l){
	int indice_da_busca = buscar(h,l->key, l->andar);
	int espacos_por_andar = h->espacos_por_andar;
	int ponteiro_anteriores;
	int ponteiro_posteriores;
	int andar_base = l->andar;
	int andar_com_copias;
	int total_de_elementos = 0;
	

	char aux_elemento[11] ;
	strcpy( aux_elemento, l->key);

	if( indice_da_busca != - 1){

		total_de_elementos = 1;
		andar_com_copias = l->andar;
		l->andares_com_copias = 1;

	}
	if( strcmp( l->key , "7214437155") == 0 ){

        	//printf("Busca Na Hash:\tAndar:|%d| Indice:|%d| Elemento:|%s| total:|%d|\n",andar_base ,indice_da_busca, aux_elemento,total_de_elementos );
        	//printf("ordenacao\n" );
        	//ordenar( h[l->estante],  l, 0, 11 );
        	//printar_hash(h[l->estante]);

     }

	//printf("Busca Na Hash:\tAndar:|%d| Indice:|%d| Elemento:|%s| total:|%d|\n",andar_base ,indice_da_busca, aux_elemento,total_de_elementos );
	// se achou algum elemento
	ponteiro_anteriores = indice_da_busca - 1;
	ponteiro_posteriores = indice_da_busca + 1;
	// Ordem de laço:
	// achou elemento
	// elemento igual faz contagem
	// ponteiros estremos
	

	while( indice_da_busca != -1 || h->andares_ocupados[andar_base] == true ){

		//printf("\n\t\tEstado andar atual:%d ocupacao= %d indice %d\n",andar_base,h->andares_ocupados[andar_base],indice_da_busca);


		for( int i = ponteiro_anteriores ; (indice_da_busca != -1) && (strcmp( aux_elemento, h->armario[andar_base][i].key) == 0) && (i > -1) ; i-- ){
			
			total_de_elementos++;

			//printf("|%d %s",i, h->armario[andar_base][i].key);

			
			if( andar_base != andar_com_copias ){
				l->andares_com_copias++;
				andar_com_copias = andar_base;
			}

		}
		//printf("\n");
		for( int i = ponteiro_posteriores ; indice_da_busca != -1 &&  strcmp( aux_elemento, h->armario[andar_base][i].key) == 0  && i < espacos_por_andar ; i++){
			
			total_de_elementos++;

			//printf("|%d %s",i, h->armario[andar_base][i].key);

			if( andar_base != andar_com_copias ){
				l->andares_com_copias++;
				andar_com_copias = andar_base;
			}
		}

		if( indice_da_busca <= -1){

			//printf("\n\t\telemento nao encontrado no andar atual:%d, proximo Andar\n",andar_base);
		}

		if( indice_da_busca != -1 || h->andares_ocupados[andar_base] == false ){
			//printf("\n\t\tFinalizado no andar |%d| Status:%d \n",andar_base, h->andares_ocupados[andar_base ] );
			l->ultimo_andar = andar_base;
			l->ultima_posicao = ponteiro_posteriores ;
		}

		andar_base++;

		if( andar_base > 10){

			andar_base = 0;

		}

		indice_da_busca = buscar(h,aux_elemento,andar_base );
		//printf("\n\t\tbusca no proximo Andar:ID:%d Status|%d|\n",andar_base, h->andares_ocupados[andar_base ]);
		if( indice_da_busca > -1 ){
			total_de_elementos++;
			l->andares_com_copias++;;
			andar_com_copias =andar_base;

		}
		
		ponteiro_anteriores = indice_da_busca - 1;
		ponteiro_posteriores = indice_da_busca + 1;
	}
	return total_de_elementos;
}


int remover( hash* h, localizacao* l ){
	int total = buscar_na_hash(h,l);
	int andar = l->ultimo_andar;
	int copias = l->copias;
	int id = l->ultima_posicao;
	int andares_ocupados_antes = l->andares_com_copias;


	//printf("total de andar com copias antes:%d total:%d copias para deletar:%d\n",l->andares_com_copias , total, copias);
	



	if( total > 0  &&  total >= copias ){
		//printf("ultima_posicao:%d ultimo_andar:%d copias:%d\n",l->ultima_posicao,l->ultimo_andar ,l->copias);
		while( copias > 0){

			for( int i = id, j = id + 1; ( i > -1 || j < h->espacos_por_andar ) && copias > 0 ; i-- , j++){

				if( strcmp( h->armario[andar][i].key , l->key ) == 0 ){

					copias--;

					
					if( h->andares_ocupados[andar] == true ){

						h->andares_ocupados[andar] = false;

					}
					h->armario[ andar ][ i ].valor_de_ordem = 1000;
					h->armario[ andar ][ i ].ocu = 0;
					strcpy( h->armario[ andar ][ i ].key , "XXXXXXXXXX" );
					//printf("Apagado I: Posicao:%d Andar:%d\n",i,andar );
					if( buscar(h , l->key , andar) == -1 && copias == 0){
						
					}
					
				}
				if( strcmp( h->armario[andar][j].key , l->key ) == 0 && copias > 0 ){

					h->armario[ andar ][ j ].valor_de_ordem = 1000;
					h->armario[ andar ][ j ].ocu = 0;
					strcpy( h->armario[ andar ][ j ].key , "XXXXXXXXXX" );

					

					//printf("Apagado J: Posicao:%d Andar:%d\n",j,andar );
					copias--;
					if( h->andares_ocupados[andar] == true ){
						
						h->andares_ocupados[andar] = false;

					}

					
					
				}else{
					j = h->espacos_por_andar;
				}
			}
			
			//printf("ordenar adnar:%d\n",andar);
			ordenar(h,l,andar,0);
		
			id = buscar(h , l->key , andar);
			if( id == -1 && copias == 0 && l->andares_com_copias > 1  ){
				l->andares_com_copias--;
			}
			//printf("total de andar com copias depois:%d e total de copias:%d\n",l->andares_com_copias,copias );

			while( id == -1 && copias > 0 ){
				//printf("\t\t\tpulo\n");
				andar--;
				l->andares_com_copias--;
				if( andar < 0){
					andar = 10;
					//printf("\t\t\tpulo\n");

				}
				id = buscar(h , l->key , andar);
				//printf("\t\t\tpulo\n");
				//printf("\n\t\t\tandar:%d valor da busca busca:%d key:%s \n",andar, id ,l->key);
			}
			
			
		}

		if( total - l->copias == 0){
			l->andares_com_copias--;
		}

	}

		
	
	return (total - l->copias);
}


int main()
{
    char operacao[4], ISBNs[10];
    register int i, j;
    int  m, q, aux;
    int copias;
    hash** h;
    localizacao* l;
    //m = 5;
    scanf(" %d %d",&m,&q);
    h = criar_armarios(m,q);
    while( strcmp( operacao, "END") != 0 ){

        scanf(" %s %s %d",operacao,ISBNs, &copias);

        l = localizar(ISBNs, m);
        l->copias = copias;
		
        if(strcmp( operacao, "ADD") == 0 ){

        	

            adicionar( h[l->estante], l);

			int total = buscar_na_hash( h[l->estante] , l);

            printf("%d %d %d\n",l->estante, total, l->andares_com_copias);

        }else if( strcmp( operacao, "REM") == 0){

        

			int total = remover( h[l->estante], l);
			printf("%d %d %d\n",l->estante, total,l->andares_com_copias);

        }else if( strcmp( operacao, "QRY") == 0){
			
			if( strcmp( ISBNs , "2124208551") == 0 && strcmp( operacao, "END") != 0  ){
	        	//printf("armario %d andar %d nucleo %d key:%s\n",l->estante, l->andar , l->nucleo, l->key);
	        	//printf("ordenacao\n" );
	        	//ordenar( h[l->estante],  l, 0, 11 );
	        	//printar_hash(h[l->estante]);

        	}

			int total = buscar_na_hash(h[l->estante],l);
			printf("%d %d %d\n",l->estante, total, l->andares_com_copias );
			

        }
        
        
        if( strcmp( ISBNs , "9362250063") == 0 && strcmp( operacao, "END") != 0  ){
        	//printf("\t\tarmario %d andar %d nucleo %d key:%s\n",l->estante, l->andar , l->nucleo, l->key);
        	//printf("ordenacao\n" );
        	//ordenar( h[l->estante],  l, 0, 11 );
        	//printar_hash(h[l->estante]);

        }
        
    }
	//printar_armarios(h,m);
    //
	//printar_hash(h[0]);
    //local = localizar("7039110555",m );

    return 0;
}
