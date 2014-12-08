//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include "TABULEIRO.h"
//#include "LISTA.h"
//
//#define LINHAS 8
//#define COLUNAS 8
//#define LINHAPEOESBRANCOS 2
//#define LINHAPEOESPRETOS 7
//#define DIRECOESPOSSIVEIS 8
//#define AMEACANTESPOSSIVEIS 12
//
//typedef struct TAB_tagPeca {
//
//	char nome;
//	/* Nome da peca */
//	char cor;
//	/* Cor da peca */
//
//} tpPeca ;
//
//typedef struct TAB_tagCasa {
//
//	tpPeca *Peca; 
//	/* Ponteiro para a peca contida na casa */
//
//	LIS_tppLista  pAmeacadas;
//	/* Ponteiro para a cabeca da lista de ameacadas */
//
//	LIS_tppLista  pAmeacantes;
//	/* Ponteiro para a cabeca da lista de ameacantes */
//
//	int linha;
//	/* Linha do tabuleiro a qual a casa pertence */
//
//	char coluna;
//	/* Coluna do tabuleiro a qual a casa pertence */
//
//}tpCasa ;
//
//
//
//typedef struct TAB_tagLinhas {
//
//	LIS_tppLista pLinha[LINHAS];
//	/* Vetor de ponteiros para a cabeca da lista de linhas */
//
//}tpLinhas;
//
//
//
//typedef struct TAB_tagTab {
//
//	tpLinhas * pLinhas;
//	/* Ponteiro para o vetor de ponteiros de linhas */
//
//}TAB_tpTab;
//
//
///***** Protótipos das funções encapuladas no módulo *****/
//
//TAB_tpCondRet ConfereCasaValida(int linha , char coluna);
//tpCasa * ObterCasa(int linha , char coluna, TAB_tppTab pTab);
//
//TAB_tpCondRet ConfereMovimentoRetoValido(int linhaOrig, char colunaOrig, int linhaDest, char colunaDest);
//TAB_tpCondRet ConfereMovimentoDiagonalValido(int linhaOrig, char colunaOrig, int linhaDest, char colunaDest);
//TAB_tpCondRet ConfereMovimentoCavaloValido(int linhaOrig, char colunaOrig, int linhaDest, char colunaDest);
//
//TAB_tpCondRet ConferePercursoVazio(int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab);
//TAB_tpCondRet ConfereCaptura(int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, TAB_tppTab pTab);
//
//TAB_tpCondRet MoverPeao ( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, TAB_tppTab pTab );
//TAB_tpCondRet MoverTorre ( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab );
//TAB_tpCondRet MoverBispo ( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab );
//TAB_tpCondRet MoverCavalo ( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, TAB_tppTab pTab );
//TAB_tpCondRet MoverDama ( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab );
//TAB_tpCondRet MoverRei ( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, TAB_tppTab pTab );
//
//TAB_tpCondRet AtualizarAmeacasAposRemocao ( int linhaOrig , char colunaOrig, TAB_tppTab pTab );
//TAB_tpCondRet AtualizarAmeacasAposInsersao ( int linhaDest , char colunaDest, TAB_tppTab pTab );
//TAB_tpCondRet RemoverAmeacadas ( int linha, char coluna, TAB_tppTab pTab );
//TAB_tpCondRet AdicionarAmeacantes ( int linha, char coluna, TAB_tppTab pTab );
//TAB_tpCondRet InserirAmeacante ( tpCasa* pCasaAameacante, tpCasa*** pCasasAmeacadas, int nCasas );
//
//int DescobrirAmeacadas(tpCasa*** casasAmeacadas, tpCasa* pCasaAmeacante, TAB_tppTab pTab);
//int ObterLimitesDeMovimento( int linha, char coluna, tpCasa*** casasLimite, TAB_tppTab pTab );
//int ObterLimitesDeMovimentoPeao( int linha, char coluna, tpCasa*** casasLimite, TAB_tppTab pTab );
//int ObterLimitesDeMovimentoCavalo( int linha, char coluna, tpCasa*** casasLimite, TAB_tppTab pTab );
//int ObterLimitesDeMovimentoRei( int linha, char coluna, tpCasa*** casasLimite, TAB_tppTab pTab );
//
//int ObterCasasEntre( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, tpCasa*** casasEntre, TAB_tppTab pTab);
//
///*****  Código das funções exportadas pelo módulo  *****/
//
//
//
//TAB_tppTab TAB_CriarTab ( void ){
//
//	int i,j;
//	TAB_tpTab * pTab;
//
//	pTab =( TAB_tpTab * ) malloc(sizeof( TAB_tpTab )) ;
//	pTab->pLinhas= (tpLinhas*)malloc(sizeof(tpLinhas));
//
//	if ( pTab == NULL ) {  
//		printf("\n Faltou memória para criar tabuleiro");
//		return NULL;
//	}
//	/*if*/
//
//	for ( i=0; i<LINHAS; i++) {
//
//		pTab->pLinhas->pLinha[i] = LIS_CriarLista( NULL );
//
//		for( j=0; j<COLUNAS; j++){
//
//			tpCasa * pCasa = ( tpCasa * ) malloc( sizeof( tpCasa )) ;
//			if ( pCasa == NULL ) {  
//				printf("\n Faltou memória para criar casa");
//				return NULL;
//			}
//			/*if*/
//			pCasa->Peca = ( tpPeca * ) malloc( sizeof( tpPeca * )) ;
//			if ( pCasa->Peca == NULL ) {  
//				printf("\n Faltou memória para criar peca");
//				return NULL;
//			}
//			pCasa->Peca->nome = 'V';
//			pCasa->Peca->cor = 'V';
//			pCasa->pAmeacadas = LIS_CriarLista( NULL );
//			pCasa->pAmeacantes = LIS_CriarLista( NULL );
//			pCasa->linha = i + 1;
//			pCasa->coluna = (char)( j  + 'A' );
//
//			if(LIS_InserirNo(pTab->pLinhas->pLinha[i] , pCasa) != LIS_CondRetOK){
//				printf("\n Erro ao inserir casa");
//				return NULL;
//			}
//			/*if*/
//
//		}
//		/*for*/
//	}
//	/*for*/
//
//
//	return pTab;
//
//}
//
//TAB_tppPeca TAB_ObterPeca ( int linha , char coluna, TAB_tppTab pTab ){
//
//	tpCasa * pCasa;
//
//	if( pTab == NULL){
//		printf("Tabuleiro nao existe");
//		return NULL;
//	}
//
//	pCasa= ObterCasa(linha, coluna, pTab);
//	if(pCasa->Peca->nome == 'V'){
//		return NULL;
//	}
//	/*if*/
//	return pCasa->Peca;
//}
//
//TAB_tpCondRet TAB_RetirarPeca ( int linha , char coluna, TAB_tppTab pTab ){
//
//	TAB_tppPeca peca;
//
//	if( pTab == NULL){
//		return TAB_CondRetNaoExiste;
//	}
//	/*if*/
//	if( ConfereCasaValida(linha, coluna) != TAB_CondRetOK ){
//		return TAB_CondRetCasaInvalida;
//	}
//	/*if*/
//	peca= TAB_ObterPeca ( linha , coluna, pTab );
//
//	if(peca == NULL){
//		return TAB_CondRetCasaVazia;
//	}
//
//	peca->cor= 'V';
//	peca->nome= 'V';
//
//	AtualizarAmeacasAposRemocao( linha, coluna, pTab );
//
//	return TAB_CondRetOK;
//}
//
//TAB_tpCondRet TAB_MoverPeca ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
//
//	TAB_tppPeca peca;
//	TAB_tpCondRet condRet;
//
//	if( pTab == NULL){
//		return TAB_CondRetNaoExiste;
//	}
//	/*if*/
//	if( ConfereCasaValida(linhaOrig, colunaOrig) != TAB_CondRetOK ){
//		return TAB_CondRetCasaInvalida;
//	}
//	/*if*/
//	if( ConfereCasaValida(linhaDest, colunaDest) != TAB_CondRetOK ){
//		return TAB_CondRetCasaInvalida;
//	}
//	/*if*/
//	peca= TAB_ObterPeca ( linhaOrig , colunaOrig, pTab );
//
//	if(peca == NULL){
//		return TAB_CondRetCasaVazia;
//	}
//	/*if*/
//
//	switch (peca->nome)
//	{
//	case 'P':
//		condRet= MoverPeao ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
//		break;
//	case 'T':
//		condRet= MoverTorre ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest, NULL,  pTab );
//		break;
//	case 'B':
//		condRet= MoverBispo ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest, NULL,  pTab );
//		break;
//	case 'C':
//		condRet= MoverCavalo ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
//		break;
//	case 'D':
//		condRet= MoverDama ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest, NULL,  pTab );
//		break;
//	case 'R':
//		condRet= MoverRei ( linhaOrig , colunaOrig,  linhaDest ,  colunaDest,  pTab );
//		break;
//	default:
//		return TAB_CondRetPecaInvalida;
//		break;
//	}
//
//	if( condRet == TAB_CondRetOK || condRet == TAB_CondRetCaptPeca){
//		TAB_RetirarPeca(linhaDest, colunaDest, pTab);
//		TAB_InserirPeca(linhaDest, colunaDest, peca->cor, peca->nome, pTab);
//		TAB_RetirarPeca(linhaOrig, colunaOrig, pTab);
//	}
//
//	return condRet;
//}
//
//TAB_tpCondRet TAB_InserirPeca ( int linha , char coluna, char cor, char tipo, TAB_tppTab pTab ){
//
//	tpCasa* casa;
//
//	if( pTab == NULL){
//		return TAB_CondRetNaoExiste;
//	}
//	/*if*/
//
//	if( ConfereCasaValida(linha, coluna) != TAB_CondRetOK ){
//		return TAB_CondRetCasaInvalida;
//	}
//	/*if*/
//
//	casa= ObterCasa(linha, coluna, pTab);
//
//	if(casa->Peca->nome != 'V'){
//		return TAB_CondRetCasaCheia;
//	}
//
//	casa->Peca->nome= tipo;
//	casa->Peca->cor= cor;
//
//	AtualizarAmeacasAposInsersao( linha, coluna, pTab );
//
//	return TAB_CondRetOK;
//}
//
//TAB_tppLista TAB_ObterListaAmeacantes( int linha , char coluna, TAB_tppTab pTab ){
//
//	tpCasa * pCasa;
//
//	if( pTab == NULL){
//		printf("Tabuleiro nao existe");
//		return NULL;
//	}
//	/*if*/
//	pCasa= ObterCasa(linha, coluna, pTab);
//
//	return pCasa->pAmeacantes;
//
//}
//
//TAB_tppLista TAB_ObterListaAmeacados( int linha , char coluna, TAB_tppTab pTab ){
//
//	tpCasa * pCasa;
//
//	if( pTab == NULL){
//		printf("Tabuleiro nao existe");
//		return NULL;
//	}
//	/*if*/
//	pCasa= ObterCasa(linha, coluna, pTab);
//
//	return pCasa->pAmeacadas;
//
//}
//
//TAB_tpCondRet TAB_DestruirTab ( TAB_tppTab pTab ){
//
//	int i;
//
//	if( pTab == NULL){
//		printf("Tabuleiro nao existe");
//		return TAB_CondRetNaoExiste;
//	}
//	/*if*/
//	for( i=0; i<LINHAS; i++){
//		LIS_DestruirLista(pTab->pLinhas->pLinha[i]);
//	}
//	/*for*/
//	free(pTab);
//
//	return TAB_CondRetOK;
//}
//
//
///* Funções Encapsuladas no módulo */
//
//
///***************************************************************************************************
//*
//*	Função:	ConfereCasaValida
//*		Parâmetros
//*			linha (int contendo o numero da linha da casa de interesse)  
//*			coluna (char contendo o caractere da coluna da casa de interesse)  
//*
//*		Retorno: TAB_tpCondRet (condição de retorno)
//*
//*		Função auxiliar que confere se a casa especificada pelas coordenadas de linha e coluna é 
//*		válida.
//*
//****************************************************************************************************/
//TAB_tpCondRet ConfereCasaValida(int linha , char coluna){
//
//	if( linha < 1 || linha > LINHAS  ){
//		return TAB_CondRetCasaInvalida;
//	}
//
//	if( coluna < 'A' || coluna > 'H' ){
//		return TAB_CondRetCasaInvalida;
//	}
//
//	return TAB_CondRetOK ;
//}
//
///***************************************************************************************************
//*
//*	Função:	ObterCasa
//*		Parâmetros
//*			linha (int contendo o numero da linha da casa de interesse)  
//*			coluna (char contendo o caractere da coluna da casa de interesse) 
//*			pTab (ponteiro para o tabuleiro em questão)
//*
//*		Retorno: tpCasa * (ponteiro para a casa solicitada)
//*			
//*		Função auxiliar que retorna o ponteiro para a casa especificada pelas coordenadas de linha
//*		e coluna do tabuleiro passado como parâmetro.
//*
//****************************************************************************************************/
//tpCasa * ObterCasa(int linha , char coluna, TAB_tppTab pTab){
//
//	int i;
//	tpCasa * pCasa;
//
//	if( ConfereCasaValida( linha, coluna ) == TAB_CondRetCasaInvalida){
//		return NULL;
//	}
//
//	LIS_IrInicioLista (pTab->pLinhas->pLinha[linha-1]);
//
//	for( i=0; i<(coluna - 'A'); i++){
//		LIS_IrProx (pTab->pLinhas->pLinha[linha-1]);
//	}
//	/*for*/
//	pCasa = (tpCasa *) LIS_ObterNo( pTab->pLinhas->pLinha[linha-1] );
//
//	return pCasa;
//}
//
///***************************************************************************************************
//*
//*	Função:	ConfereMovimentoRetoValido
//*		Parâmetros
//*			linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*			colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*			linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*			colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		Função que confere se o movimento a ser executado é vertical ou horizontal. Para isso apenas
//*		uma das coordenadas pode ser alterada. Ou seja, se a o movimento for na vertical a colunaOrig
//*		será a mesma que a colunaDest. Se o movimento for na horizontal a linhaOrig será a mesma que
//*		a linhaDest.
//*		A Função também verifica se o destino é diferente da origem e retorna TAB_CondRetMovInv caso
//*		essa condição não seja satisfeita.
//*
//****************************************************************************************************/
//TAB_tpCondRet ConfereMovimentoRetoValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){
//
//	int distanciaColunas= (int) colunaDest-colunaOrig;
//	int distanciaLinhas= linhaDest-linhaOrig;
//
//	//Confere se o movimento é diagonal ou se não há movimento
//	if(distanciaColunas == distanciaLinhas){
//		return TAB_CondRetMovInv;
//	}
//	/*if*/
//	//Confere se a linha ou a coluna não serão alteradas.
//	if(distanciaColunas != 0 && distanciaLinhas != 0){
//		return TAB_CondRetMovInv;
//	}
//	/*if*/
//	return TAB_CondRetOK;
//}/* Fim função: ConfereMovimentoRetoValido */
//
//
///***************************************************************************************************
//*
//*	Função:	ConfereMovimentoDiagonalValido
//*		Parâmetros
//*			linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*			colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*			linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*			colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		Função que confere se o movimento a ser executado é diagonal. Para isso ambas as coordenadas 
//*		devem ser alteradas uma mesma quantidade de casas. Ou seja, o módulo da distância entre 
//*		linhaOrig e linhaDest deve ser igual ao módulo da distância entre colunaOrig e colunaDest.
//*		A Função também verifica se o destino é diferente da origem e retorna TAB_CondRetMovInv caso
//*		essa condição não seja satisfeita.
//*
//****************************************************************************************************/
//TAB_tpCondRet ConfereMovimentoDiagonalValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){
//
//	int distanciaColunas= (int) colunaDest-colunaOrig;
//	int distanciaLinhas= linhaDest-linhaOrig;
//
//	if( abs(distanciaColunas) != abs(distanciaLinhas) ){
//		return TAB_CondRetMovInv;
//	}
//	/*if*/
//	if(distanciaColunas == 0 && distanciaLinhas == 0){
//		return TAB_CondRetMovInv;
//	}
//	/*if*/
//	return TAB_CondRetOK;
//}/* Fim função: ConfereMovimentoDiagonalValido */
//
//
///***************************************************************************************************
//*
//*	$FC Função:	ConfereMovimentoCavaloValido
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento a ser executado é próprio da peça "Cavalo", ou seja é
//*		verificado se o movimento é em formato de "L". Para garantir esse movimento, a soma dos
//*		módulos das distâncias entre linhaOrig e linhaDest e entre colunaOrig e colunaDest deve ser
//*		igual a 3 e nenhuma das coordenadas pode permanecer a mesma.
//*		A Função também verifica se o destino é diferente da origem e retorna TAB_CondRetMovInv caso
//*		essa condição não seja satisfeita.
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//TAB_tpCondRet ConfereMovimentoCavaloValido(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest){
//
//	int distanciaColunas= (int) colunaDest-colunaOrig;
//	int distanciaLinhas= linhaDest-linhaOrig;
//
//	if( (abs(distanciaColunas) + abs(distanciaLinhas)) != 3){
//		return TAB_CondRetMovInv;
//	}
//	/*if*/
//	if(distanciaColunas == 0 || distanciaLinhas == 0){
//		return TAB_CondRetMovInv;
//	}
//	/*if*/
//	return TAB_CondRetOK;
//}/* Fim função: ConfereMovimentoCavaloValido */
//
//
///***************************************************************************************************
//*
//*	$FC Função:	ConferePercursoVazio
//*
//*	$ED Descrição da função
//*		Função que confere se o percurso percorrido por uma peca até chegar em sua casa destino
//*		possui uma casa que nao está vazia. Caso a peca movimentada seja o cavalo inclui-se a opcao
//*		de pular casas
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//
//TAB_tpCondRet ConferePercursoVazio(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab){
//
//	int i;
//	int distanciaColunas= (int) colunaDest-colunaOrig;
//	int distanciaLinhas= linhaDest-linhaOrig;
//	int sinalLinha= 1;
//	int sinalColuna= 1;
//
//	if(distanciaLinhas < 0){
//		sinalLinha = -1;
//	}
//
//	if(distanciaColunas < 0){
//		sinalColuna = -1;
//	}
//
//	if(distanciaLinhas == 0)
//	{
//		for (i = 1; i <= abs(distanciaColunas); i++)
//		{
//			if ( TAB_ObterPeca( linhaOrig,(char)(colunaOrig + (i*sinalColuna) ),pTab ) != NULL )
//			{
//				if(pCasaBloqueio != NULL) { 
//					*pCasaBloqueio = ObterCasa( linhaOrig,(char)(colunaOrig + (i*sinalColuna) ),pTab ); 
//				}
//				return TAB_CondRetPecaBloqueando;
//			}
//		}
//
//	}
//	else{
//		if(distanciaColunas == 0)
//		{
//			for (i = 1; i <= abs(distanciaLinhas); i++)
//			{
//				if ( TAB_ObterPeca( linhaOrig + (i*sinalLinha), colunaOrig, pTab ) != NULL )
//				{
//					if(pCasaBloqueio != NULL) { 
//						*pCasaBloqueio = ObterCasa( linhaOrig,(char)(colunaOrig + (i*sinalColuna) ),pTab ); 
//					}
//					return TAB_CondRetPecaBloqueando;
//				}
//			}
//
//		}
//		else{
//			for (i = 1; i <= abs(distanciaColunas); i++)
//			{
//				if (TAB_ObterPeca( linhaOrig + (i*sinalLinha), (char)( colunaOrig + (i*sinalColuna) ), pTab ) != NULL )
//				{
//					if(pCasaBloqueio != NULL) { 
//						*pCasaBloqueio = ObterCasa( linhaOrig,(char)(colunaOrig + (i*sinalColuna) ),pTab ); 
//					}
//					return TAB_CondRetPecaBloqueando;
//				}
//			}
//		}
//	}
//
//	if(TAB_ObterPeca(linhaDest,colunaDest,pTab) != NULL){
//		if(pCasaBloqueio != NULL) { 
//			*pCasaBloqueio = ObterCasa( linhaOrig,(char)(colunaOrig + (i*sinalColuna) ),pTab ); 
//		}
//		return TAB_CondRetCasaCheia;
//	}
//	return TAB_CondRetOK;
//}
///* Fim função: ConferePercursoVazio */
//
//
///***************************************************************************************************
//*
//*	$FC Função:	ConfereCaptura
//*
//*	$ED Descrição da função
//*		Função que confere se a casa a qual a peca sera movimentada esta sendo ocupada por
//*		uma peca inimiga, nesse casa a peca inimiga é capturada e a movimentada ocupar seu lugar
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//TAB_tpCondRet ConfereCaptura(int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab){
//
//	TAB_tppPeca pecaOrig= TAB_ObterPeca(linhaOrig,colunaOrig,pTab);
//	TAB_tppPeca pecaDest= TAB_ObterPeca(linhaDest,colunaDest,pTab);
//
//	if ( pecaDest != NULL){
//		if(pecaOrig->cor != pecaDest->cor){
//			return TAB_CondRetCaptPeca;
//		}
//		return TAB_CondRetCasaCheia;
//	}
//
//	return TAB_CondRetOK;
//}
///* Fim função: ConfereCaptura */
//
//
///***************************************************************************************************
//*
//*	$FC Função:	MoverPeao
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento requisitado para uma peca do tipo peao atende às regras de 
//*		movimentacao
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//TAB_tpCondRet MoverPeao ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
//
//	char corPeao= TAB_ObterPeca(linhaOrig,colunaOrig,pTab)->cor;
//	int distanciaLinhas= linhaDest-linhaOrig;
//	int nCasasNormal, nCasasEspecial;
//
//	if(corPeao == 'P'){
//		//Movimentação para os peões pretos
//		nCasasNormal= -1;
//		nCasasEspecial= -2;
//	}
//	else{
//		//Movimentação para os peões brancos
//		nCasasNormal= 1;
//		nCasasEspecial= 2;
//	}
//
//	//Confere se a movimentação é para frente
//	if(ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
//		//Movimento de uma casa
//		if(distanciaLinhas == nCasasNormal){
//			//Peão não pode capturar peça ao andar para frente
//			return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, NULL, pTab);
//		}
//		//Movimento pode ser de duas casas se for a partir da linha inicial dos peões
//		if(linhaOrig == LINHAPEOESPRETOS && distanciaLinhas == nCasasEspecial && corPeao == 'P'){
//			//Peão não pode capturar peça ao andar para frente
//			return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, NULL, pTab);
//		}
//		if(linhaOrig == LINHAPEOESBRANCOS && distanciaLinhas == nCasasEspecial && corPeao == 'B'){
//			//Peão não pode capturar peça ao andar para frente
//			return ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, NULL, pTab);
//		}
//	}
//	//Confere se a movimentação é para a diagonal
//	else if(ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
//		//Movimento de uma casa na diagonal
//		if(distanciaLinhas == nCasasNormal){
//			//Peão não pode andar na diagonal sem capturar uma peça
//			if(ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab) == TAB_CondRetCaptPeca){
//				return TAB_CondRetCaptPeca;
//			}
//			return TAB_CondRetMovInv;
//		}
//	}
//
//	return TAB_CondRetMovInv;
//
//}
///* Fim função: MoverPeao */
//
///***************************************************************************************************
//*
//*	$FC Função:	MoverTorre
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento requisitado para uma peca do tipo torre atende às regras de 
//*		movimentacao
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//TAB_tpCondRet MoverTorre ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab ){
//
//	TAB_tpCondRet condRet;
//	//Confere se a movimentação é horizontal ou vertical
//	if(ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
//		//Confere se o caminho está livre, bloqueado ou se haverá captura de peça
//		condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pCasaBloqueio, pTab);
//		if( condRet == TAB_CondRetCasaCheia ){
//			return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
//		}
//		return condRet;
//	}
//	return TAB_CondRetMovInv;
//}
///* Fim função: MoverTorre */
//
///***************************************************************************************************
//*
//*	$FC Função:	MoverBispo
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento requisitado para uma peca do tipo bispo atende às regras de 
//*		movimentacao
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//TAB_tpCondRet MoverBispo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab ){
//
//	TAB_tpCondRet condRet;
//	//Confere se a movimentação é diagonal
//	if(ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
//		//Confere se o caminho está livre, bloqueado ou se haverá captura de peça
//		condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pCasaBloqueio, pTab);
//		if( condRet == TAB_CondRetCasaCheia ){
//			return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
//		}
//		return condRet;
//	}
//	return TAB_CondRetMovInv;
//}
///* Fim função: MoverBispo */
//
///***************************************************************************************************
//*
//*	$FC Função:	MoverCavalo
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento requisitado para uma peca do tipo cavalo atende às regras de 
//*		movimentacao
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//TAB_tpCondRet MoverCavalo ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
//
//	//Confere se a movimentação é em "L"
//	if(ConfereMovimentoCavaloValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK){
//		//Confere se haverá captura de peça
//		return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
//	}
//	return TAB_CondRetMovInv;
//}
//
///* Fim função: MoverCavalo */
//
///***************************************************************************************************
//*
//*	$FC Função:	MoverDama
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento requisitado para uma peca do tipo dama atende às regras de 
//*		movimentacao
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//TAB_tpCondRet MoverDama ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, tpCasa** pCasaBloqueio, TAB_tppTab pTab ){
//
//	TAB_tpCondRet condRet;
//	//Confere se a movimentação é diagonal, vertical ou horizontal
//	if( ConfereMovimentoDiagonalValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK ||
//		ConfereMovimentoRetoValido(linhaOrig, colunaOrig, linhaDest, colunaDest) == TAB_CondRetOK ){
//			//Confere se o caminho está livre, bloqueado ou se haverá captura de peça
//			condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, pCasaBloqueio, pTab);
//			if( condRet == TAB_CondRetCasaCheia ){
//				return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
//			}
//			return condRet;
//	}
//	return TAB_CondRetMovInv;
//
//
//}/* Fim função: MoverDama */
//
///****************************************************************************************************
//*
//*	$FC Função:	MoverRei
//*
//*	$ED Descrição da função
//*		Função que confere se o movimento requisitado para uma peca do tipo rei atende às regras de 
//*		movimentacao
//*
//*	$EP Parâmetros
//*		linhaOrig (int contendo o numero da linha onde está a peça a ser movida)  
//*		colunaOrig (char contendo o caractere da coluna onde está a peça a ser movida)  
//*		linhaDest (int contendo o numero da linha para onde a peça deve ser movida)  
//*		colunaDest (char contendo o caractere da coluna para onde a peça deve ser movida)
//*			
//*		
//*
//****************************************************************************************************/
//
//
//TAB_tpCondRet MoverRei ( int linhaOrig , char colunaOrig, int linhaDest , char colunaDest, TAB_tppTab pTab ){
//
//	int distanciaColunas= (int) colunaDest-colunaOrig;
//	int distanciaLinhas= linhaDest-linhaOrig;
//	TAB_tpCondRet condRet;
//
//	if( abs(distanciaColunas) > 1 || abs(distanciaLinhas) > 1 ){
//		return TAB_CondRetMovInv;
//	}
//
//	condRet= ConferePercursoVazio(linhaOrig, colunaOrig, linhaDest, colunaDest, NULL, pTab);
//	if( condRet == TAB_CondRetCasaCheia ){
//		return ConfereCaptura(linhaOrig, colunaOrig, linhaDest, colunaDest, pTab);
//	}
//	return condRet;
//
//}
///* Fim função: MoverRei */
//
//TAB_tpCondRet AtualizarAmeacasAposRemocao ( int linhaOrig , char colunaOrig, TAB_tppTab pTab )
//{
//	int nAmeacadas, nAmeacantes;
//	int i;
//	tpCasa **casasAmeacadas[DIRECOESPOSSIVEIS/2 * LINHAS];
//	tpCasa **casasAmeacantes[AMEACANTESPOSSIVEIS + 1];
//	tpCasa *pCasaOrig;
//
//	for( i = 0; i < DIRECOESPOSSIVEIS/2 * LINHAS; i++){
//		casasAmeacadas[i] = (tpCasa**)malloc(sizeof(tpCasa*));
//	}
//	for( i = 0; i < AMEACANTESPOSSIVEIS + 1; i++){
//		casasAmeacantes[i] = (tpCasa**)malloc(sizeof(tpCasa*));
//	}
//
//	pCasaOrig = ObterCasa( linhaOrig ,colunaOrig, pTab);
//
//	// Remove as ameaçadas da casa que agora está vazia, removendo também as referencias nas ameacadas
//	RemoverAmeacadas( linhaOrig , colunaOrig, pTab);
//
//	// Insere as ameaças nas casas que agora não estão bloqueadas.
//	if( LIS_ObterNo( pCasaOrig->pAmeacantes ) != NULL )
//	{
//		LIS_IrInicioLista( pCasaOrig->pAmeacantes );
//		nAmeacantes = 0;
//		do
//		{
//			*casasAmeacantes[nAmeacantes] = (tpCasa*)LIS_ObterNo( pCasaOrig->pAmeacantes );
//			nAmeacantes++;
//		} while( LIS_IrProx(pCasaOrig->pAmeacantes) == LIS_CondRetOK );
//
//		for( i = 0; i < nAmeacantes; i++)
//		{
//			if( (*casasAmeacantes[i])->Peca->nome == 'T' || (*casasAmeacantes[i])->Peca->nome == 'B'
//				|| (*casasAmeacantes[i])->Peca->nome == 'D' )
//			{
//				nAmeacadas = DescobrirAmeacadas( casasAmeacadas, (*casasAmeacantes[i]), pTab);
//				InserirAmeacante( (*casasAmeacantes[i]), casasAmeacadas, nAmeacadas );
//			}
//		}
//	}
//
//	for( i = 0; i < DIRECOESPOSSIVEIS/2 * LINHAS; i++){
//		free(casasAmeacadas[i]);
//	}
//	for( i = 0; i < AMEACANTESPOSSIVEIS + 1; i++){
//		free(casasAmeacantes[i]);
//	}
//
//	return TAB_CondRetOK;
//}
//
//TAB_tpCondRet AtualizarAmeacasAposInsersao ( int linhaDest , char colunaDest, TAB_tppTab pTab )
//{
//	int nAmeacadas, nAmeacantes;
//	int i;
//	tpCasa **casasAmeacadas[DIRECOESPOSSIVEIS/2 * LINHAS];
//	tpCasa **casasAmeacantes[AMEACANTESPOSSIVEIS + 1];
//	tpCasa *pCasaDest;
//
//	for( i = 0; i < DIRECOESPOSSIVEIS/2 * LINHAS; i++){
//		casasAmeacadas[i] = (tpCasa**)malloc(sizeof(tpCasa*));
//	}
//	for( i = 0; i < AMEACANTESPOSSIVEIS + 1; i++){
//		casasAmeacantes[i] = (tpCasa**)malloc(sizeof(tpCasa*));
//	}
//
//	pCasaDest = ObterCasa( linhaDest ,colunaDest, pTab);
//
//	// Remove as ameaçadas que já existiam na casa destino, removendo também as referencias nas ameacadas
//	RemoverAmeacadas( linhaDest , colunaDest, pTab);
//
//	// Atualiza as ameaças de todas as casas que ameaçam a casa que agora está ocupada.
//	if( LIS_ObterNo( pCasaDest->pAmeacantes ) != NULL )
//	{
//		LIS_IrInicioLista( pCasaDest->pAmeacantes );
//		nAmeacantes = 0;
//		do
//		{
//			*casasAmeacantes[nAmeacantes] = (tpCasa*)LIS_ObterNo( pCasaDest->pAmeacantes );
//			nAmeacantes++;
//		} while( LIS_IrProx(pCasaDest->pAmeacantes) == LIS_CondRetOK );
//
//		for( i = 0; i < nAmeacantes; i++)
//		{
//			if( (*casasAmeacantes[i])->Peca->nome == 'T' || (*casasAmeacantes[i])->Peca->nome == 'B'
//				|| (*casasAmeacantes[i])->Peca->nome == 'D' )
//			{
//				RemoverAmeacadas( (*casasAmeacantes[i])->linha, (*casasAmeacantes[i])->coluna, pTab);
//				nAmeacadas = DescobrirAmeacadas( casasAmeacadas, (*casasAmeacantes[i]), pTab);
//				InserirAmeacante( (*casasAmeacantes[i]), casasAmeacadas, nAmeacadas );
//			}
//		}
//	}
//
//	// Insere as novas ameaças da casa que agora está ocupada.
//	nAmeacadas = DescobrirAmeacadas( casasAmeacadas, pCasaDest, pTab);
//	InserirAmeacante( pCasaDest, casasAmeacadas, nAmeacadas );
//
//	for( i = 0; i < DIRECOESPOSSIVEIS/2 * LINHAS; i++){
//		free(casasAmeacadas[i]);
//	}
//	for( i = 0; i < AMEACANTESPOSSIVEIS + 1; i++){
//		free(casasAmeacantes[i]);
//	}
//	return TAB_CondRetOK;
//}
//
//int DescobrirAmeacadas(tpCasa ***casasAmeacadas, tpCasa *pCasaAmeacante, TAB_tppTab pTab)
//{
//	int nEntre, nCasas, nDirecoes;
//	int i, j;
//	tpCasa **casasLimite[DIRECOESPOSSIVEIS];
//	tpCasa **casasEntre[LINHAS];
//
//	for( i = 0; i < LINHAS; i++){
//		casasLimite[i] = (tpCasa**)malloc(sizeof(tpCasa*));
//		casasEntre[i] = (tpCasa**)malloc(sizeof(tpCasa*));
//	}
//
//	nCasas = 0;
//
//	nDirecoes = ObterLimitesDeMovimento(pCasaAmeacante->linha , pCasaAmeacante->coluna, casasLimite, pTab);
//	for(i = 0; i < nDirecoes; i++)
//	{
//		if( LIS_ProcurarValor((*casasLimite[i])->pAmeacantes, pCasaAmeacante) != LIS_CondRetOK )
//		{
//			nEntre = ObterCasasEntre(pCasaAmeacante->linha, pCasaAmeacante->coluna, (*casasLimite[i])->linha, 
//										(*casasLimite[i])->coluna, casasEntre, pTab);
//
//			for( j = 0; j < nEntre; j++, nCasas++){
//				*casasAmeacadas[nCasas] = *casasEntre[j];
//			}
//			*casasAmeacadas[nCasas] = *casasLimite[i];
//			nCasas++;
//		}
//	}
//
//	for( i = 0; i < LINHAS; i++){
//		free(casasLimite[i]);
//		free(casasEntre[i]);
//	}
//	return nCasas;
//}
//
//TAB_tpCondRet RemoverAmeacadas ( int linha , char coluna , TAB_tppTab pTab )
//{
//	tpCasa* pCasaAlterada;
//	tpCasa* pCasaRemover;
//
//	pCasaAlterada = ObterCasa(linha , coluna, pTab);
//	LIS_IrInicioLista( pCasaAlterada->pAmeacadas );
//
//	pCasaRemover = ( tpCasa* ) LIS_ObterNo( pCasaAlterada->pAmeacadas );
//	while(pCasaRemover != NULL)
//	{
//		if( LIS_ProcurarValor( pCasaRemover->pAmeacantes, pCasaAlterada ) == LIS_CondRetOK )
//		{ LIS_ExcluirNoCorr(pCasaRemover->pAmeacantes); }
//
//		LIS_ExcluirNoCorr(pCasaAlterada->pAmeacadas);
//		pCasaRemover = ( tpCasa* ) LIS_ObterNo( pCasaAlterada->pAmeacadas );
//	}
//	return TAB_CondRetOK;
//}
//
//TAB_tpCondRet RemoverAmeacantes ( int linha , char coluna , TAB_tppTab pTab )
//{
//	tpCasa* pCasaAlterada;
//	tpCasa* pCasaRemover;
//
//	pCasaAlterada = ObterCasa(linha , coluna, pTab);
//	LIS_IrInicioLista( pCasaAlterada->pAmeacantes );
//
//	pCasaRemover = ( tpCasa* ) LIS_ObterNo( pCasaAlterada->pAmeacantes );
//	while(pCasaRemover != NULL){
//		RemoverAmeacadas ( pCasaRemover->linha, pCasaRemover->coluna, pTab );
//		pCasaRemover = ( tpCasa* ) LIS_ObterNo( pCasaAlterada->pAmeacantes );
//	}
//	return TAB_CondRetOK;
//}
//
//TAB_tpCondRet InserirAmeacante ( tpCasa *pCasaAameacante, tpCasa ***pCasasAmeacadas, int nCasas )
//{
//	int i;
//
//	LIS_IrInicioLista( pCasaAameacante->pAmeacantes );
//
//	for( i = 0; i < nCasas && pCasasAmeacadas[i] != NULL; i++)
//	{
//		if( LIS_ProcurarValor( pCasaAameacante->pAmeacadas, *pCasasAmeacadas[i] ) != LIS_CondRetOK ){
//			LIS_InserirNo(pCasaAameacante->pAmeacadas, *pCasasAmeacadas[i]);
//		}
//		
//		if( LIS_ProcurarValor( (*pCasasAmeacadas[i])->pAmeacantes, pCasaAameacante ) != LIS_CondRetOK ){
//			LIS_InserirNo((*pCasasAmeacadas[i])->pAmeacantes, pCasaAameacante);
//		}
//	} 
//
//	return TAB_CondRetOK;
//}
//
//int ObterLimitesDeMovimento( int linha, char coluna, tpCasa ***casasLimite, TAB_tppTab pTab )
//{
//	int linhaDest, colunaDest, nCasas;
//	TAB_tppPeca pPeca;
//	TAB_tpCondRet condRet;
//	TAB_tpCondRet (*pTesteMovimento)( int, char, int, char, tpCasa**, TAB_tppTab );
//
//
//	nCasas = 0;
//	pPeca= TAB_ObterPeca( linha, coluna , pTab );
//	
//	switch (pPeca->nome)
//	{
//		case 'T':
//			pTesteMovimento = &MoverTorre;
//			break;
//		case 'B':
//			pTesteMovimento = &MoverBispo;
//			break;
//		case 'D':
//			pTesteMovimento = &MoverDama;
//			break;
//		case 'P':
//			return ObterLimitesDeMovimentoPeao( linha, coluna, casasLimite, pTab );
//			break;
//		case 'C':
//			return ObterLimitesDeMovimentoCavalo( linha, coluna, casasLimite, pTab );
//			break;
//		case 'R':
//			return ObterLimitesDeMovimentoRei( linha, coluna, casasLimite, pTab );
//			break;
//		default:
//			return 0;
//			break;
//	}
//
//	for(linhaDest = 1, colunaDest = 1; colunaDest < 9; colunaDest++)
//	{
//		condRet = pTesteMovimento( linha, coluna,  linhaDest,  (char)(colunaDest-1+'A'), casasLimite[nCasas],  pTab);
//		if( ( condRet == TAB_CondRetPecaBloqueando || condRet == TAB_CondRetCasaCheia || condRet == TAB_CondRetCaptPeca ) 
//			&& ( nCasas == 0 || ( *casasLimite[nCasas] != *casasLimite[nCasas-1] ) ) ){
//			nCasas++;
//		}
//		if( condRet == TAB_CondRetOK )
//		{
//			if( linha != linhaDest || colunaDest == 1 || colunaDest == 8){
//				*casasLimite[nCasas] = ObterCasa(linhaDest, (char)(colunaDest-1+'A'), pTab);
//				nCasas++;
//			}
//		}
//	}
//
//	for(linhaDest = 8, colunaDest = 1; colunaDest < 9; colunaDest++)
//	{
//		condRet = pTesteMovimento( linha, coluna,  linhaDest,  (char)(colunaDest-1+'A'), casasLimite[nCasas],  pTab);
//		if( ( condRet == TAB_CondRetPecaBloqueando || condRet == TAB_CondRetCasaCheia || condRet == TAB_CondRetCaptPeca ) 
//			&& ( nCasas == 0 || ( *casasLimite[nCasas] != *casasLimite[nCasas-1] ) ) ){
//			nCasas++;
//		}
//		if( condRet == TAB_CondRetOK )
//		{
//			if( linha != linhaDest || colunaDest == 1 || colunaDest == 8){
//				*casasLimite[nCasas] = ObterCasa(linhaDest, (char)(colunaDest-1+'A'), pTab);
//				nCasas++;
//			}
//		}
//	}
//
//	for(linhaDest = 2, colunaDest = 1; linhaDest < 8; linhaDest++)
//	{
//		condRet = pTesteMovimento( linha, coluna,  linhaDest,  (char)(colunaDest-1+'A'), casasLimite[nCasas],  pTab);
//		if( ( condRet == TAB_CondRetPecaBloqueando || condRet == TAB_CondRetCasaCheia || condRet == TAB_CondRetCaptPeca ) 
//			&& ( nCasas == 0 || ( *casasLimite[nCasas] != *casasLimite[nCasas-1] ) ) ){
//			nCasas++;
//		}
//		if( condRet == TAB_CondRetOK )
//		{
//			if( (int)(coluna-'A'+1) != colunaDest ){
//				*casasLimite[nCasas] = ObterCasa(linhaDest, (char)(colunaDest-1+'A'), pTab);
//				nCasas++;
//			}
//		}
//	}
//
//	for(linhaDest = 2, colunaDest = 8; linhaDest < 8; linhaDest++)
//	{
//		condRet = pTesteMovimento( linha, coluna,  linhaDest,  (char)(colunaDest-1+'A'), casasLimite[nCasas],  pTab);
//		if( ( condRet == TAB_CondRetPecaBloqueando || condRet == TAB_CondRetCasaCheia || condRet == TAB_CondRetCaptPeca ) 
//			&& ( nCasas == 0 || ( *casasLimite[nCasas] != *casasLimite[nCasas-1] ) ) ){
//			nCasas++;
//		}
//		if( condRet == TAB_CondRetOK )
//		{
//			if( (int)(coluna-'A'+1) != colunaDest ){
//				*casasLimite[nCasas] = ObterCasa(linhaDest, (char)(colunaDest-1+'A'), pTab);
//				nCasas++;
//			}
//		}
//	}
//	return nCasas;
//}
//
//int ObterLimitesDeMovimentoPeao( int linha, char coluna, tpCasa ***casasLimite, TAB_tppTab pTab )
//{
//	TAB_tppPeca pPeca;
//	int linhaDest, i, nCasas;
//	char colunaDest[2] = {coluna-1, coluna+1};
//
//	pPeca = TAB_ObterPeca( linha, coluna, pTab );
//	if( pPeca->cor == 'B'){
//		linhaDest = linha + 1;
//	}
//	else{
//		linhaDest = linha - 1;
//	}
//
//	for( i = 0, nCasas = 0; i < 2; i++)
//	{
//		if( ConfereCasaValida( linhaDest, colunaDest[i] ) == TAB_CondRetOK){
//			*casasLimite[nCasas] = ObterCasa( linhaDest, colunaDest[i], pTab );
//			nCasas++;
//		}
//	}
//
//	return nCasas;
//}
//
//int ObterLimitesDeMovimentoCavalo( int linha, char coluna, tpCasa ***casasLimite, TAB_tppTab pTab )
//{
//	int i, nCasas;
//	int linhaDest[8] = { linha-2, linha-2, linha-1, linha-1, linha+1, linha+1, linha+2, linha+2 };
//	char colunaDest[8] = { coluna-1, coluna+1, coluna-2, coluna+2, coluna-2, coluna+2, coluna-1, coluna+1 };
//
//	for( i = 0, nCasas = 0; i < 8; i++)
//	{
//		if( ConfereCasaValida( linhaDest[i], colunaDest[i] ) == TAB_CondRetOK ){
//			*casasLimite[nCasas] = ObterCasa( linhaDest[i], colunaDest[i], pTab );
//			nCasas++;
//		}
//	}
//
//	return nCasas;
//}
//
//int ObterLimitesDeMovimentoRei( int linha, char coluna, tpCasa ***casasLimite, TAB_tppTab pTab )
//{
//	int i, nCasas;
//	int linhaDest[8] = { linha-1, linha-1, linha-1, linha, linha, linha+1, linha+1, linha+1 };
//	char colunaDest[8] = { coluna-1, coluna, coluna+1, coluna-1, coluna+1, coluna-1, coluna, coluna+1 };
//
//	for( i = 0, nCasas = 0; i < 8; i++)
//	{
//		if( ConfereCasaValida( linhaDest[i], colunaDest[i] ) == TAB_CondRetOK ){
//			*casasLimite[nCasas] = ObterCasa( linhaDest[i], colunaDest[i], pTab );
//			nCasas++;
//		}
//	}
//
//	return nCasas;
//}
//
//int ObterCasasEntre( int linhaOrig, char colunaOrig, int linhaDest, char colunaDest, tpCasa*** casasEntre, TAB_tppTab pTab)
//{
//	int nCasas;
//	int distanciaColunas= (int) colunaDest-colunaOrig;
//	int distanciaLinhas= linhaDest-linhaOrig;
//	int sinalLinha= 1;
//	int sinalColuna= 1;
//
//	if(distanciaLinhas < 0){
//		sinalLinha = -1;
//	}
//
//	if(distanciaColunas < 0){
//		sinalColuna = -1;
//	}
//
//	if( abs(distanciaColunas) < 2 && abs(distanciaLinhas) < 2 ){
//		return 0;
//	}
//
//	if(distanciaLinhas == 0)
//	{
//		for (nCasas = 1; nCasas < abs(distanciaColunas); nCasas++){
//			*casasEntre[nCasas-1] = ObterCasa( linhaOrig,(char)(colunaOrig + (nCasas*sinalColuna) ),pTab );
//		}
//	}
//	else{
//		if(distanciaColunas == 0)
//		{
//			for (nCasas = 1; nCasas < abs(distanciaLinhas); nCasas++){
//				*casasEntre[nCasas-1] = ObterCasa( linhaOrig + (nCasas*sinalLinha), colunaOrig, pTab );
//			}
//		}
//		else{
//			for (nCasas = 1; nCasas < abs(distanciaColunas); nCasas++){
//				*casasEntre[nCasas-1] = ObterCasa( linhaOrig + (nCasas*sinalLinha), (char)( colunaOrig + (nCasas*sinalColuna) ), pTab );
//			}
//		}
//	}
//	nCasas--;
//	return nCasas;
//}
