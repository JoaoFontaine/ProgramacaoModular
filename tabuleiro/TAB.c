#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Lista.h"
#include "TAB.h"
#define LINHAS 8
#define COLUNAS 8

typedef struct TAB_tagPeca {

	char nome;
	    /* Nome da peca */
	char cor;
		/* Cor da peca */

} tpPeca ;
	

typedef struct TAB_tagCasa {

    tpPeca *  Peca; 
		/* Ponteiro para a peca contida na casa */

	LIS_tppLista  pAmeacadas;
		/* Ponteiro para a cabeca da lista de ameacadas */

	LIS_tppLista  pAmeacantes;
		/* Ponteiro para a cabeca da lista de ameacantes */

}tpCasa ;



typedef struct TAB_tagLinhas {

	LIS_tppLista  pLinha[LINHAS];
		/* Vetor de ponteiros para a cabeca da lista de linhas */

}tpLinhas;



typedef struct TAB_tagTab {
	
	tpLinhas * pLinhas;
		/* Ponteiro para o vetor de ponteiros de linhas */

}TAB_tpTab;


/***** Protótipos das funções encapuladas no módulo *****/


	


/*****  Código das funções exportadas pelo módulo  *****/



TAB_tppTab CriarTab ( void ){

	int i,j;

	TAB_tpTab * pTab =( TAB_tpTab * ) malloc( sizeof( TAB_tpTab )) ;

	if ( pTab == NULL ) {  
		printf("\n Faltou memória para criar tabuleiro");
		return NULL;
	}
	/*if*/

	for ( i=0; i<LINHAS; i++) {

		pTab->pLinhas->pLinha[i] = LIS_CriarLista( NULL );

		for( j=0; j<COLUNAS; j++){

			tpCasa * pCasa = ( tpCasa * ) malloc( sizeof( tpCasa )) ;
			if ( pTab == NULL ) {  
		    printf("\n Faltou memória para criar peca");
		    return NULL;
	        }
	        /*if*/
			pCasa->Peca->nome = 'V';
			pCasa->Peca->cor = 'V';
			pCasa->pAmeacadas = LIS_CriarLista( NULL );
			pCasa->pAmeacantes = LIS_CriarLista( NULL );
			if(LIS_InserirNo(pTab->pLinhas->pLinha[i] , pCasa) != LIS_CondRetOK){
				printf("\n Erro ao inserir casa");
				return NULL;
			}
			/*if*/

		}
		/*for*/
	}
	/*for*/

	
	return pTab;

}

TAB_tppPeca ObterPeca ( int linha , char coluna, TAB_tppTab pTab ){

	int i;
	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	/*if*/
	for( i=0; i<=(coluna - 'A'); i++){
		LIS_IrProx (pTab->pLinhas->pLinha[i]);
	}
	/*for*/
	pCasa = (tpCasa *) LIS_ObterNo( pTab->pLinhas->pLinha[i] );
	if(pCasa->Peca->nome == 'V'){
		printf("\n Casa Vazia");
		return NULL;
	}
	/*if*/
	return pCasa->Peca;
}
	

LIS_tppLista ObterListaAmeacantes( int linha , char coluna, TAB_tppTab pTab ){

	int i;
	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	/*if*/
	for( i=0; i<=(coluna - 'A'); i++){
		LIS_IrProx (pTab->pLinhas->pLinha[i]);
	}
	/*for*/

	pCasa = (tpCasa *) LIS_ObterNo( pTab->pLinhas->pLinha[i] );

	return pCasa->pAmeacantes;

}

LIS_tppLista ObterListaAmeacadas( int linha , char coluna, TAB_tppTab pTab ){

	int i;
	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	/*if*/
	for( i=0; i<=(coluna - 'A'); i++){
		LIS_IrProx (pTab->pLinhas->pLinha[i]);
	}
	/*for*/

	pCasa = (tpCasa *) LIS_ObterNo( pTab->pLinhas->pLinha[i] );

	return pCasa->pAmeacadas;

}

TAB_tpCondRet DestruirTab ( TAB_tppTab pTab ){

	int i;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return TAB_CondRetNaoExiste;
	}
	/*if*/
	for( i=0; i<=LINHAS; i++){
		LIS_DestruirLista(pTab->pLinhas->pLinha[i]);
	}
	/*for*/
	free(pTab);
}

	