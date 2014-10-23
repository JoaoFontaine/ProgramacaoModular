#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TAB.h"
#define LINHAS 8
#define COLUNAS 8
#define LINHAPEOESBRANCOS 2
#define LINHAPEOESPRETOS 7


typedef struct TAB_tagCasa {

	tpPeca *  Peca; 
	/* Ponteiro para a peca contida na casa */

	LIS_tppLista  pAmeacadas;
	/* Ponteiro para a cabeca da lista de ameacadas */

	LIS_tppLista  pAmeacantes;
	/* Ponteiro para a cabeca da lista de ameacantes */

}tpCasa ;



typedef struct TAB_tagLinhas {

	LIS_tppLista pLinha[LINHAS];
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
	TAB_tpTab * pTab;

	pTab =( TAB_tpTab * ) malloc(sizeof( TAB_tpTab )) ;
	pTab->pLinhas= (tpLinhas*)malloc(sizeof(tpLinhas));

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
		//printf("\n Casa Vazia");
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
		TAB_RetirarPeca(linhaDest, colunaDest, pTab);
		TAB_InserirPeca(linhaDest, colunaDest, peca->cor, peca->nome, pTab);
		TAB_RetirarPeca(linhaOrig, colunaOrig, pTab);
	}

	//AtualizarListaAmeacantes ( linhaDest, colunaDest, pTab);
	//AtualizarListaAmeacados ( linhaDest, colunaDest, pTab);
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
	for( i=0; i<LINHAS; i++){
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

	if( linha < 0 || linha > LINHAS  ){
		return TAB_CondRetCasaInvalida;
	}

	if( coluna < 'A' || coluna > 'H' ){
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
	LIS_IrInicioLista (pTab->pLinhas->pLinha[linha-1]);

	for( i=0; i<(coluna - 'A'); i++){
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


/***************************************************************************************************
*
*	$FC Fun��o:	ConferePercursoVazio
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o percurso percorrido por uma peca at� chegar em sua casa destino
*		possui uma casa que nao est� vazia. Caso a peca movimentada seja o cavalo inclui-se a opcao
*		de pular casas
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


TAB_tpCondRet ConferePercursoVazio(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab){

	int i;
	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;
	int sinalLinha= 1;
	int sinalColuna= 1;

	if(distanciaLinhas < 0){
		sinalLinha = -1;
	}

	if(distanciaColunas < 0){
		sinalColuna = -1;
	}

	if(distanciaLinhas == 0){
		for (i = 1; i <= abs(distanciaColunas); i++){
			if ( TAB_ObterPeca( linhaOrig,(char)(colunaOrig + (i*sinalColuna) ),pTab ) != NULL ){
				return TAB_CondRetPecaBloqueando;
			}
		}

	}
	else{
		if(distanciaColunas == 0){
			for (i = 1; i <= abs(distanciaLinhas); i++){
				if ( TAB_ObterPeca( linhaOrig + (i*sinalLinha), colunaOrig, pTab ) != NULL ){
					return TAB_CondRetPecaBloqueando;
				}
			}

		}
		else{
			for (i = 1; i <= abs(distanciaColunas); i++){
				if (TAB_ObterPeca( linhaOrig + (i*sinalLinha), (char)( colunaOrig + (i*sinalColuna) ), pTab ) != NULL ){
					return TAB_CondRetPecaBloqueando;
				}
			}
		}
	}

	if(TAB_ObterPeca(linhaDest,colunaDest,pTab) != NULL){
		return TAB_CondRetCasaCheia;
	}
	return TAB_CondRetOK;
	//return ConfereCaptura(linhaOrig, colunaOrig, linhaDest , colunaDest, pTab);
}
/* Fim fun��o: ConferePercursoVazio */


/***************************************************************************************************
*
*	$FC Fun��o:	ConfereCaptura
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se a casa a qual a peca sera movimentada esta sendo ocupada por
*		uma peca inimiga, nesse casa a peca inimiga � capturada e a movimentada ocupar seu lugar
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

TAB_tpCondRet ConfereCaptura(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab){

	TAB_tppPeca pecaOrig= TAB_ObterPeca(linhaOrig,colunaOrig,pTab);
	TAB_tppPeca pecaDest= TAB_ObterPeca(linhaDest,colunaDest,pTab);

	if ( pecaDest != NULL){
		if(pecaOrig->cor != pecaDest->cor){
			return TAB_CondRetCaptPeca;
		}
		return TAB_CondRetCasaCheia;
	}

	return TAB_CondRetOK;
}
/* Fim fun��o: ConfereCaptura */


/***************************************************************************************************
*
*	$FC Fun��o:	MoverPeao
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento requisitado para uma peca do tipo peao atende �s regras de 
*		movimentacao
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
			return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		}
		//Movimento pode ser de duas casas se for a partir da linha inicial dos pe�es
		if(linhaOrig == LINHAPEOESPRETOS && distanciaLinhas == nCasasEspecial && corPeao == 'P'){
			//Pe�o n�o pode capturar pe�a ao andar para frente
			return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		}
		if(linhaOrig == LINHAPEOESBRANCOS && distanciaLinhas == nCasasEspecial && corPeao == 'B'){
			//Pe�o n�o pode capturar pe�a ao andar para frente
			return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		}
	}
	//Confere se a movimenta��o � para a diagonal
	else if(ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Movimento de uma casa na diagonal
		if(distanciaLinhas == nCasasNormal){
			//Pe�o n�o pode andar na diagonal sem capturar uma pe�a
			if(ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab) == TAB_CondRetCaptPeca){
				return TAB_CondRetCaptPeca;
			}
			return TAB_CondRetMovInv;
		}
	}

	return TAB_CondRetMovInv;

}
/* Fim fun��o: MoverPeao */

/***************************************************************************************************
*
*	$FC Fun��o:	MoverTorre
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento requisitado para uma peca do tipo torre atende �s regras de 
*		movimentacao
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

TAB_tpCondRet MoverTorre ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	TAB_tpCondRet condRet;
	//Confere se a movimenta��o � horizontal ou vertical
	if(ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Confere se o caminho est� livre, bloqueado ou se haver� captura de pe�a
		condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		if( condRet == TAB_CondRetCasaCheia ){
			return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		}
		return condRet;
	}
	return TAB_CondRetMovInv;
}
/* Fim fun��o: MoverTorre */

/***************************************************************************************************
*
*	$FC Fun��o:	MoverBispo
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento requisitado para uma peca do tipo bispo atende �s regras de 
*		movimentacao
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

TAB_tpCondRet MoverBispo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	TAB_tpCondRet condRet;
	//Confere se a movimenta��o � diagonal
	if(ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Confere se o caminho est� livre, bloqueado ou se haver� captura de pe�a
		condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		if( condRet == TAB_CondRetCasaCheia ){
			return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
		}
		return condRet;
	}
	return TAB_CondRetMovInv;
}
/* Fim fun��o: MoverBispo */

/***************************************************************************************************
*
*	$FC Fun��o:	MoverCavalo
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento requisitado para uma peca do tipo cavalo atende �s regras de 
*		movimentacao
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

TAB_tpCondRet MoverCavalo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	//Confere se a movimenta��o � em "L"
	if(ConfereMovimentoCavaloValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
		//Confere se haver� captura de pe�a
		return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	}
	return TAB_CondRetMovInv;
}

/* Fim fun��o: MoverCavalo */

/***************************************************************************************************
*
*	$FC Fun��o:	MoverDama
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento requisitado para uma peca do tipo dama atende �s regras de 
*		movimentacao
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

TAB_tpCondRet MoverDama ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	TAB_tpCondRet condRet;
	//Confere se a movimenta��o � diagonal, vertical ou horizontal
	if( ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK ||
		ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK ){
			//Confere se o caminho est� livre, bloqueado ou se haver� captura de pe�a
			condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
			if( condRet == TAB_CondRetCasaCheia ){
				return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
			}
			return condRet;
	}
	return TAB_CondRetMovInv;


}/* Fim fun��o: MoverDama */


	/***************************************************************************************************
*
*	$FC Fun��o:	MoverRei
*
*	$ED Descri��o da fun��o
*		Fun��o que confere se o movimento requisitado para uma peca do tipo rei atende �s regras de 
*		movimentacao
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
}

TAB_tpCondRet MoverRei ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){

	int distanciaColunas= (int) colunaDest-colunaOrig;
	int distanciaLinhas= linhaDest-linhaOrig;
	TAB_tpCondRet condRet;

	if( abs(distanciaColunas) > 1 || abs(distanciaLinhas) > 1 ){
		return TAB_CondRetMovInv;
	}

	condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	if( condRet == TAB_CondRetCasaCheia ){
		return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
	}
	return condRet;

}
/* Fim fun��o: MoverRei */

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