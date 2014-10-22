#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "LISTA.h"
#include "TAB.h"
#define LINHAS 8
#define COLUNAS 8
#define LINHAPEOESBRANCOS 2
#define LINHAPEOESPRETOS 7


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


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

TAB_tpCondRet ConfereCasaValida(int linha , char coluna);
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

TAB_tpCondRet AtualizarListaAmeacantes (int linha , char coluna, TAB_tppTab pTab);
TAB_tpCondRet AtualizarListaAmeacados (int linha , char coluna, TAB_tppTab pTab);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/



TAB_tppTab TAB_CriarTab ( void ){

	int i,j;

	TAB_tpTab * pTab =( TAB_tpTab * ) malloc( sizeof( TAB_tpTab )) ;

	if ( pTab == NULL ) {  
		printf("\n Faltou mem�ria para criar tabuleiro");
		return NULL;
	}
	/*if*/

	for ( i=0; i<LINHAS; i++) {

		pTab->pLinhas->pLinha[i] = LIS_CriarLista( NULL );

		for( j=0; j<COLUNAS; j++){

			tpCasa * pCasa = ( tpCasa * ) malloc( sizeof( tpCasa )) ;
			if ( pCasa == NULL ) {  
				printf("\n Faltou mem�ria para criar casa");
				return NULL;
			}
			/*if*/
			pCasa->Peca = ( tpPeca * ) malloc( sizeof( tpPeca * )) ;
			if ( pCasa->Peca == NULL ) {  
				printf("\n Faltou mem�ria para criar peca");
				return NULL;
			}
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

	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	
	pCasa= ObterCasa(linha, coluna, pTab);
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
	if( ConfereCasaValida(linha, coluna) != TAB_CondRetOK ){
		return TAB_CondRetCasaInvalida;
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
	TAB_tpCondRet condRet;

	if( pTab == NULL){
		return TAB_CondRetNaoExiste;
	}
	/*if*/
	if( ConfereCasaValida(linhaOrig, colunaOrig) != TAB_CondRetOK ){
		return TAB_CondRetCasaInvalida;
	}
	/*if*/
	if( ConfereCasaValida(linhaDest, colunaDest) != TAB_CondRetOK ){
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
		condRet= MoverPeao ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'T':
		condRet= MoverTorre ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'B':
		condRet= MoverBispo ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'C':
		condRet= MoverCavalo ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'D':
		condRet= MoverDama ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	case 'R':
		condRet= MoverRei ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
		break;
	default:
		return TAB_CondRetPecaInvalida;
		break;
	}

	if( condRet == TAB_CondRetOK || condRet == TAB_CondRetCaptPeca){
		TAB_RetirarPeca(linhaOrig, colunaOrig, pTab);
		TAB_RetirarPeca(linhaDest, colunaDest, pTab);
		TAB_InserirPeca(linhaDest, colunaDest, peca->cor, peca->nome, pTab);
	}

	AtualizarListaAmeacantes ( linhaDest, colunaDest, pTab);
	AtualizarListaAmeacados ( linhaDest, colunaDest, pTab);
	return condRet;
}

TAB_tpCondRet TAB_InserirPeca ( int linha , char coluna, char cor, char tipo, TAB_tppTab pTab ){

	tpCasa* casa;

	if( pTab == NULL){
		return TAB_CondRetNaoExiste;
	}
	/*if*/

	if( ConfereCasaValida(linha, coluna) != TAB_CondRetOK ){
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

	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	/*if*/
	pCasa= ObterCasa(linha, coluna, pTab);

	return pCasa->pAmeacantes;

}

LIS_tppLista TAB_ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab ){

	tpCasa * pCasa;

	if( pTab == NULL){
		printf("Tabuleiro nao existe");
		return NULL;
	}
	/*if*/
	pCasa= ObterCasa(linha, coluna, pTab);

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

	return TAB_CondRetOK;
}


/* Fun��es Encapsuladas no m�dulo */


/***************************************************************************************************
*
*	Fun��o:	ConfereCasaValida
*		Par�metros
*			linha (int contendo o numero da linha da casa de interesse)  
*			coluna (char contendo o caractere da coluna da casa de interesse)  
*
*		Retorno: TAB_tpCondRet (condi��o de retorno)
*
*		Fun��o auxiliar que confere se a casa especificada pelas coordenadas de linha e coluna � 
*		v�lida.
*
****************************************************************************************************/
TAB_tpCondRet ConfereCasaValida(int linha , char coluna){

	int numColuna= (int)(coluna-'A');

	if( 0 <= linha && linha < LINHAS ){
		return TAB_CondRetCasaInvalida;
	}

	if( (0 <= numColuna) && (numColuna < COLUNAS) ){
		return TAB_CondRetCasaInvalida;
	}

	return TAB_CondRetOK ;
}

/***************************************************************************************************
*
*	Fun��o:	ObterCasa
*		Par�metros
*			linha (int contendo o numero da linha da casa de interesse)  
*			coluna (char contendo o caractere da coluna da casa de interesse) 
*			pTab (ponteiro para o tabuleiro em quest�o)
*
*		Retorno: tpCasa * (ponteiro para a casa solicitada)
*			
*		Fun��o auxiliar que retorna o ponteiro para a casa especificada pelas coordenadas de linha
*		e coluna do tabuleiro passado como par�metro.
*
****************************************************************************************************/
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

/***************************************************************************************************
*
*	Fun��o:	ConfereMovimentoRetoValido
*		Par�metros
*			linhaOrig (int contendo o numero da linha onde est� a pe�a a ser movida)  
*			colunaOrig (char contendo o caractere da coluna onde est� a pe�a a ser movida)  
*			linhaDest (int contendo o numero da linha para onde a pe�a deve ser movida)  
*			colunaDest (char contendo o caractere da coluna para onde a pe�a deve ser movida)
*			
*		Fun��o que confere se o movimento a ser executado � vertical ou horizontal. Para isso apenas
*		uma das coordenadas pode ser alterada. Ou seja, se a o movimento for na vertical a colunaOrig
*		ser� a mesma que a colunaDest. Se o movimento for na horizontal a linhaOrig ser� a mesma que
*		a linhaDest.
*		A Fun��o tamb�m verifica se o destino � diferente da origem e retorna TAB_CondRetMovInv caso
*		essa condi��o n�o seja satisfeita.
*
****************************************************************************************************/
TAB_tpCondRet ConfereMovimentoRetoValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){

	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;

	//Confere se o movimento � diagonal ou se n�o h� movimento
	if(distanciaColunas == distanciaLinhas){
		return TAB_CondRetMovInv;
	}
	/*if*/
	//Confere se a linha ou a coluna n�o ser�o alteradas.
	if(distanciaColunas != 0 && distanciaLinhas != 0){
		return TAB_CondRetMovInv;
	}
	/*if*/
	return TAB_CondRetOK;
}/* Fim fun��o: ConfereMovimentoRetoValido */


/***************************************************************************************************
*
*	Fun��o:	ConfereMovimentoDiagonalValido
*		Par�metros
*			linhaOrig (int contendo o numero da linha onde est� a pe�a a ser movida)  
*			colunaOrig (char contendo o caractere da coluna onde est� a pe�a a ser movida)  
*			linhaDest (int contendo o numero da linha para onde a pe�a deve ser movida)  
*			colunaDest (char contendo o caractere da coluna para onde a pe�a deve ser movida)
*			
*		Fun��o que confere se o movimento a ser executado � diagonal. Para isso ambas as coordenadas 
*		devem ser alteradas uma mesma quantidade de casas. Ou seja, o m�dulo da dist�ncia entre 
*		linhaOrig e linhaDest deve ser igual ao m�dulo da dist�ncia entre colunaOrig e colunaDest.
*		A Fun��o tamb�m verifica se o destino � diferente da origem e retorna TAB_CondRetMovInv caso
*		essa condi��o n�o seja satisfeita.
*
****************************************************************************************************/
TAB_tpCondRet ConfereMovimentoDiagonalValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){

	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;

	if( abs(distanciaColunas) != abs(distanciaLinhas) ){
		return TAB_CondRetMovInv;
	}
	/*if*/
	if(distanciaColunas == 0 && distanciaLinhas == 0){
		return TAB_CondRetMovInv;
	}
	/*if*/
	return TAB_CondRetOK;
}/* Fim fun��o: ConfereMovimentoDiagonalValido */


/***************************************************************************************************
*
*	$FC Fun��o:	ConfereMovimentoCavaloValido
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento a ser executado � pr�prio da pe�a "Cavalo", ou seja �
*		verificado se o movimento � em formato de "L". Para garantir esse movimento, a soma dos
*		m�dulos das dist�ncias entre linhaOrig e linhaDest e entre colunaOrig e colunaDest deve ser
*		igual a 3 e nenhuma das coordenadas pode permanecer a mesma.
*		A Fun��o tamb�m verifica se o destino � diferente da origem e retorna TAB_CondRetMovInv caso
*		essa condi��o n�o seja satisfeita.
*
*	$EP Par�metros
*		linhaOrig (int contendo o numero da linha onde est� a pe�a a ser movida)  
*		colunaOrig (char contendo o caractere da coluna onde est� a pe�a a ser movida)  
*		linhaDest (int contendo o numero da linha para onde a pe�a deve ser movida)  
*		colunaDest (char contendo o caractere da coluna para onde a pe�a deve ser movida)
*			
*		
*
****************************************************************************************************/
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
}/* Fim fun��o: ConfereMovimentoCavaloValido */


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

	char corPeao= TAB_ObterPeca(linhaOrig,colunaOrig,pTab)->cor;
	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;
	int nCasasNormal, nCasasEspecial;

	if(corPeao == 'P'){
		//Movimenta��o para os pe�es pretos
		nCasasNormal= -1;
		nCasasEspecial= -2;
	}
	else{
		//Movimenta��o para os pe�es brancos
		nCasasNormal= 1;
		nCasasEspecial= 2;
	}

	//Confere se a movimenta��o � para frente
	if(ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Movimento de uma casa
		if(distanciaLinhas == nCasasNormal){
			//Pe�o n�o pode capturar pe�a ao andar para frente
			if(ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab) == TAB_CondRetOK){
				return TAB_CondRetOK;
			}
			return TAB_CondRetPecaBloqueando;
		}
		//Movimento pode ser de duas casas se for a partir da linha inicial dos pe�es
		if(linhaOrig == LINHAPEOESPRETOS && distanciaLinhas == nCasasEspecial ){
			//Pe�o n�o pode capturar pe�a ao andar para frente
			if(ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab) == TAB_CondRetOK){
				return TAB_CondRetOK;
			}
			return TAB_CondRetPecaBloqueando;
		}
	}
	//Confere se a movimenta��o � para a diagonal
	else if(ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Movimento de uma casa na diagonal
		if(distanciaLinhas == nCasasNormal){
			//Pe�o n�o pode andar na diagonal sem capturar uma pe�a
			if(ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab) == TAB_CondRetCaptPeca){
				return TAB_CondRetCaptPeca;
			}
			return TAB_CondRetMovInv;
		}
	}

	return TAB_CondRetMovInv;
}

TAB_tpCondRet MoverTorre ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	
	//Confere se a movimenta��o � horizontal ou vertical
	if(ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Confere se o caminho est� livre, bloqueado ou se haver� captura de pe�a
		return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	}
	return TAB_CondRetMovInv;
}

TAB_tpCondRet MoverBispo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	
	//Confere se a movimenta��o � diagonal
	if(ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Confere se o caminho est� livre, bloqueado ou se haver� captura de pe�a
		return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	}
	return TAB_CondRetMovInv;
}

TAB_tpCondRet MoverCavalo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
	
	//Confere se a movimenta��o � em "L"
	if(ConfereMovimentoCavaloValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Confere se haver� captura de pe�a
		return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	}
	return TAB_CondRetMovInv;
}

TAB_tpCondRet MoverDama ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	//Confere se a movimenta��o � diagonal, vertical ou horizontal
	if( ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK ||
		ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK ){
		//Confere se o caminho est� livre, bloqueado ou se haver� captura de pe�a
		return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	}
	return TAB_CondRetMovInv;
}

TAB_tpCondRet MoverRei ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	int i;
	char corRei= TAB_ObterPeca(linhaOrig,colunaOrig,pTab)->cor;
	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;

	if( abs(distanciaColunas) > 1 || abs(distanciaLinhas) > 1 ){
		return TAB_CondRetMovInv;
	}
		
	return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);

}
/***************************************************************************************************
*
*	$FC Fun��o:	AtualizarListaAmeacantes
*
*	$ED Descri��o da fun��o
*		Funcao que atualiza a lista de amecantes a casa especificada
*
*
*	$EP Par�metros
*		linha (int contendo o numero da linha da casa)  
*		coluna (char contendo o caractere da coluna da casa)  
*			
*		
*
****************************************************************************************************/


TAB_tpCondRet AtualizarListaAmeacantes ( int linha , char coluna , TAB_tppTab pTab) {

	tpCasa * pCasa;
	tpPeca * pPeca;

	pPeca = TAB_ObterPeca(linha,coluna,pTab);
	pCasa = ObterCasa ( linha  , coluna , pTab);

	while ( pCasa->pAmeacadas != NULL){
		pPeca = (tpPeca *)LIS_ObterNo ( pCasa->pAmeacadas);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor) { 
			LIS_InserirNo( pCasa->pAmeacantes, pPeca);
		}
		LIS_IrProx(pCasa->pAmeacadas);
	}
	/*while*/

	while ( pCasa->pAmeacadas != NULL){
		pPeca = (tpPeca *)LIS_ObterNo ( pCasa->pAmeacadas);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor) { 
			LIS_InserirNo( pCasa->pAmeacantes, pPeca);
		}
		LIS_IrAnt(pCasa->pAmeacadas);
	}

	return TAB_CondRetOK;
}

/***************************************************************************************************
*
*	$FC Fun��o:	AtualizarListaAmeacados
*
*	$ED Descri��o da fun��o
*		Funcao que atualiza a lista de amecados a casa especificada
*
*
*	$EP Par�metros
*		linha (int contendo o numero da linha da casa)  
*		coluna (char contendo o caractere da coluna da casa)  
*			
*		
*
****************************************************************************************************/

TAB_tpCondRet AtualizarListaAmeacados ( int linha , char coluna , TAB_tppTab pTab) {
	
	tpCasa * pCasa;
	tpPeca * pPeca;
	int i;

	pPeca = TAB_ObterPeca(linha,coluna,pTab);
	pCasa = ObterCasa ( linha  , coluna , pTab);

	switch (pPeca->nome)
	{
	case 'P':

		pCasa = ObterCasa ( linha + 1 , coluna - 1 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha + 1 , coluna + 1 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		break;

	case 'T':

		for ( i=0; i<8 ; i++) {

			pCasa = ObterCasa ( i , coluna , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha , 'A' + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
		}
		/*for*/

		break;
	case 'B':

		for ( i=0; i<8 ; i++) {

			pCasa = ObterCasa (linha + i , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa (linha + i , coluna - i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa (linha - i , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa (linha - i , coluna - i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
		}
		/*for*/

		break;

	case 'C':

		pCasa = ObterCasa ( linha + 2 , coluna + 1 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha + 2 , coluna - 1 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha - 2 , coluna + 1 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha - 2 , coluna - 1 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha + 1 , coluna + 2 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha + 1 , coluna - 2 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha - 1 , coluna + 2 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/
		pCasa = ObterCasa ( linha - 1 , coluna - 2 , pTab);
		if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
			LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
		}
		/*if*/

		break;

	case 'D':
		for ( i=0; i<8 ; i++) {

			pCasa = ObterCasa ( linha + i , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha - i , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha - i , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha - i , coluna - i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/

		}
		/*for*/
		break;

	case 'R':

		for ( i=-1; i<2 ; i++) {

			pCasa = ObterCasa ( linha , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha + 1 , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha + 2 , coluna + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( i , coluna , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
			pCasa = ObterCasa ( linha , 'A' + i , pTab);
			if(pCasa->Peca->nome != 'V' && pCasa->Peca->cor != pPeca->cor){
				LIS_InserirNo( pCasa->pAmeacadas , pCasa->Peca);
			}
			/*if*/
		}
		/*for*/

		break;

	default:
		return TAB_CondRetPecaInvalida;
		break;

	}

	return TAB_CondRetOK;
}