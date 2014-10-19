#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "LISTA.h"
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

TAB_tpCondRet ConfereCasaValida(int linha , char coluna, TAB_tppTab pTab);
tpCasa * ObterCasa(int linha , char coluna, TAB_tppTab pTab);

TAB_tpCondRet ConfereMovimentoRetoValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest);
TAB_tpCondRet ConfereMovimentoDiagonalValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest);
TAB_tpCondRet ConfereMovimentoCavaloValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest);

TAB_tpCondRet ConferePercursoVazio(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab);
TAB_tpCondRet ConfereCaptura(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab);

TAB_tpCondRet MoverPeao ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );
TAB_tpCondRet MoverTorre ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );
TAB_tpCondRet MoverBispo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );
TAB_tpCondRet MoverCavalo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );
TAB_tpCondRet MoverDama ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );
TAB_tpCondRet MoverRei ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab );

/*****  Código das funções exportadas pelo módulo  *****/



TAB_tppTab TAB_CriarTab ( void ){

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

TAB_tppPeca TAB_ObterPeca ( int linha , char coluna, TAB_tppTab pTab ){

	int i;
	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	/*if*/
	for( i=0; i<=(coluna - 'A'); i++){
		LIS_IrProx (pTab->pLinhas->pLinha[linha-1]);
	}
	/*for*/
	pCasa = (tpCasa *) LIS_ObterNo( pTab->pLinhas->pLinha[linha-1] );
	if(pCasa->Peca->nome == 'V'){
		printf("\n Casa Vazia");
		return NULL;
	}
	/*if*/
	return pCasa->Peca;
}

TAB_tpCondRet TAB_RetirarPeca ( int linha , char coluna, TAB_tppTab pTab ){

	TAB_tppPeca peca;

	if( pTab == NULL){
		return TAB_CondRetNaoExiste;
	}
	/*if*/
	peca= TAB_ObterPeca ( linha , coluna, pTab );

	if(peca == NULL){
		return TAB_CondRetCasaVazia;
	}

	peca->cor= 'V';
	peca->nome= 'V';

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_MoverPeca ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	TAB_tppPeca peca;
	tpCasa * pCasaOrig;
	tpCasa * pCasaDest;

	if( pTab == NULL){
		return TAB_CondRetNaoExiste;
	}
	/*if*/
	if( ConfereCasaValida(linhaOrig, colunaOrig, pTab) != TAB_CondRetOK ){
		return TAB_CondRetCasaInvalida;
	}
	/*if*/
	if( ConfereCasaValida(linhaDest, colunaDest, pTab) != TAB_CondRetOK ){
		return TAB_CondRetCasaInvalida;
	}
	/*if*/
	peca= TAB_ObterPeca ( linhaOrig , colunaOrig, pTab );

	if(peca == NULL){
		return TAB_CondRetCasaVazia;
	}
	/*if*/

	switch (peca->nome)
	{
	case 'P':
		return MoverPeao ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'T':
		return MoverTorre ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'B':
		return MoverBispo ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'C':
		return MoverCavalo ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'D':
		return MoverDama ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'R':
		return MoverRei ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	default:
		return TAB_CondRetPecaInvalida;
		break;
	}

}

TAB_tpCondRet TAB_InserirPeca ( int linha , char coluna, char cor, char tipo, TAB_tppTab pTab ){

	tpCasa* casa;

	if( pTab == NULL){
		return TAB_CondRetNaoExiste;
	}
	/*if*/

	if( ConfereCasaValida(linha, coluna, pTab) != TAB_CondRetOK ){
		return TAB_CondRetCasaInvalida;
	}
	/*if*/

	casa= ObterCasa(linha, coluna, pTab);

	if(casa->Peca->nome != 'V'){
		return TAB_CondRetCasaCheia;
	}

	casa->Peca->nome= tipo;
	casa->Peca->cor= cor;

	return TAB_CondRetOK;

}

LIS_tppLista TAB_ObterListaAmeacantes( int linha , char coluna, TAB_tppTab pTab ){

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

LIS_tppLista TAB_ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab ){

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

TAB_tpCondRet TAB_DestruirTab ( TAB_tppTab pTab ){

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


/* Funções Encapsuladas no módulo */


TAB_tpCondRet ConfereCasaValida(int linha , char coluna, TAB_tppTab pTab){

	int numColuna= (int)(coluna-'A');

	if( 0 <= linha && linha < LINHAS ){
		return TAB_CondRetCasaInvalida;
	}

	if( (0 <= numColuna) && (numColuna < COLUNAS) ){
		return TAB_CondRetCasaInvalida;
	}

	return TAB_CondRetOK ;
}


tpCasa * ObterCasa(int linha , char coluna, TAB_tppTab pTab){

	int i;
	tpCasa * pCasa;

	for( i=0; i<=(coluna - 'A'); i++){
		LIS_IrProx (pTab->pLinhas->pLinha[linha-1]);
	}
	/*for*/
	pCasa = (tpCasa *) LIS_ObterNo( pTab->pLinhas->pLinha[linha-1] );

	return pCasa;
}

TAB_tpCondRet ConfereMovimentoRetoValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){

	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;

	if(distanciaColunas == distanciaLinhas){
		return TAB_CondRetMovInv;
	}
	/*if*/
	if(distanciaColunas != 0 && distanciaLinhas != 0){
		return TAB_CondRetMovInv;
	}
	/*if*/
	return TAB_CondRetOK;
}

TAB_tpCondRet ConfereMovimentoDiagonalValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){

	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;

	if(distanciaColunas != distanciaLinhas){
		return TAB_CondRetMovInv;
	}
	/*if*/
	if(distanciaColunas == 0 && distanciaLinhas == 0){
		return TAB_CondRetMovInv;
	}
	/*if*/
	return TAB_CondRetOK;
}

TAB_tpCondRet ConfereMovimentoCavaloValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){

	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;

	if( (abs(distanciaColunas) + abs(distanciaLinhas)) != 3){
		return TAB_CondRetMovInv;
	}
	/*if*/
	if(distanciaColunas == 0 || distanciaLinhas == 0){
		return TAB_CondRetMovInv;
	}
	/*if*/
	return TAB_CondRetOK;
}

TAB_tpCondRet ConferePercursoVazio(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab){

	int i;
	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;
	int primeiraLinha= linhaOrig;
	int primeiraColuna= (int) colunaOrig - 'A';

	if(distanciaLinhas == 0){
		if (distanciaColunas < 0){
			primeiraColuna= (int) colunaDest - 'A';
		}
		for (i = 1; i < (primeiraColuna+distanciaColunas); i++){
			if (TAB_ObterPeca(primeiraLinha,(char)(primeiraColuna+i + 'A'),pTab) != NULL){
				return TAB_CondRetPecaBloqueando;
			}
		}

	}
	else if(distanciaColunas == 0){
		if (distanciaLinhas < 0){
			primeiraLinha= linhaDest;
		}
		for (i = 1; i < (primeiraLinha+distanciaLinhas); i++){
			if (TAB_ObterPeca(primeiraLinha+i,(char)(primeiraColuna + 'A'),pTab) != NULL){
				return TAB_CondRetPecaBloqueando;
			}
		}

	}
	else{
		if (distanciaLinhas < 0){
			primeiraColuna= (int) colunaDest - 'A';
		}
		if (distanciaColunas < 0){
			primeiraColuna= colunaDest;
		}
		for (i = 1; i < (primeiraColuna+distanciaColunas); i++){
			if (TAB_ObterPeca(primeiraLinha+i,(char)(primeiraColuna+i + 'A'),pTab) != NULL){
				return TAB_CondRetPecaBloqueando;
			}
		}
	}

	return ConfereCaptura(linhaOrig, colunaOrig, linhaDest , colunaDest, pTab);
}

TAB_tpCondRet ConfereCaptura(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab){

	TAB_tppPeca pecaOrig= TAB_ObterPeca(linhaDest,colunaDest,pTab);
	TAB_tppPeca pecaDest= TAB_ObterPeca(linhaDest,colunaDest,pTab);

	if ( pecaDest != NULL){
		if(pecaOrig->cor == pecaDest->cor){
			return TAB_CondRetPecaBloqueando;
		}
		return TAB_CondRetCaptPeca;
	}

	return TAB_CondRetOK;
}
TAB_tpCondRet MoverPeao ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	return TAB_CondRetOK;
}

TAB_tpCondRet MoverTorre ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	return TAB_CondRetOK;
}

TAB_tpCondRet MoverBispo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	return TAB_CondRetOK;
}

TAB_tpCondRet MoverCavalo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	return TAB_CondRetOK;
}

TAB_tpCondRet MoverDama ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	return TAB_CondRetOK;
}

TAB_tpCondRet MoverRei ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	return TAB_CondRetOK;
}