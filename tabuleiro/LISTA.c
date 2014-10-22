/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 Jogo de Xadrez
*  Autores: avs
*  Coautores: Guilherme Araujo e Jo�o Pedro Fontaine
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*	  0       Gui   10/out/2014 acr�scimo de algumas fun��es
*
***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "LISTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/


 typedef struct tagNoLista {

         void * pValor ;
               /* Ponteiro para o valor contido no n� */

         struct tagNoLista * pAnt ;
               /* Ponteiro para o n� predecessor */

         struct tagNoLista * pProx ;
               /* Ponteiro para o n� sucessor */

   } tpNoLista ;



 /***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/
    
 typedef struct LIS_tagLista {

         tpNoLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpNoLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpNoLista * pNoCorr ;
               /* Ponteiro para o n� corrente da lista */
		
		 char idLista[4];
		      /* Estrutura identificadora da lista */

   } LIS_tpLista ;



 /***** Prot�tipos das fun��es encapuladas no m�dulo *****/


	tpNoLista * CriarNo( void * pValor);  
	void LimparCabeca( LIS_tppLista pLista );

	/*****  C�digo das fun��es exportadas pelo m�dulo  *****/



/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/
	
	LIS_tppLista LIS_CriarLista( char * idLista ) {

	  LIS_tpLista * pLista =( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
     
	  if ( pLista == NULL ){
		  printf("\n Faltou mem�ria para criar lista");
		  return NULL;
	  }
	  /*if*/
	  /*if ( strlen(idLista) > 4) printf("\n S� ser�o utilizados os 4 primeiros caracteres para identificar a lista");

	  strncpy(pLista->idLista , idLista, 4);*/
	  LimparCabeca( pLista ) ;

	  return pLista;

	} /* Fim fun��o: LIS  &Criar lista */



	/***************************************************************************
*
*  Fun��o: LIS  &Orbter Id Lista
*  ****/

	void * LIS_ObterIdLista( LIS_tppLista pLista ) {

		/* Tratar lista vazia */

		if ( pLista == NULL ) return NULL;
		

		return pLista->idLista;

	}/* Fim fun��o: LIS  &Orbter Id Lista */



	/***************************************************************************
*
*  Fun��o: LIS  &Inserir n�
*  ****/

	LIS_tpCondRet LIS_InserirNo( LIS_tppLista pLista , void * pValor ) {

		tpNoLista* pNo = CriarNo( pValor ) ;

         if ( pNo == NULL ) return LIS_CondRetFaltouMemoria ;
		 /* if */
         if ( pLista->pNoCorr == NULL )
         {
            pLista->pOrigemLista = pNo ;
            pLista->pFimLista = pNo ;
         } else
         {
            if ( pLista->pNoCorr->pProx != NULL )
            {
               pNo->pProx  = pLista->pNoCorr->pProx ;
               pLista->pNoCorr->pProx->pAnt = pNo ;
            } else
            {
               pLista->pFimLista = pNo ;
            } /* if */

            pNo->pAnt = pLista->pNoCorr ;
            pLista->pNoCorr->pProx = pNo ;

         } /* if */
                  
         pLista->pNoCorr = pNo ;
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir n� */



	/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no n�
*  ****/

	void * LIS_ObterNo( LIS_tppLista pLista ){

		if ( pLista == NULL )
		{
			printf(" \n Lista inexistente");
      		 return NULL;
		}
		
		if( pLista->pNoCorr == NULL )
		{
			printf(" \n Lista Vazia");
			return NULL;
		}

		return pLista->pNoCorr->pValor;

	}/* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no n� */



	/***************************************************************************
*
*  Fun��o: LIS  &Excluir n� corrente
*  ****/

	void LIS_ExcluirNoCorr( LIS_tppLista pLista ){

		tpNoLista * pNo ;

		/* Tratar lista vazia */

      if ( pLista->pNoCorr == NULL )
      {
		 printf("\n Erro ao excluir no corrente, lista vazia");
         return;
      } 

      pNo = pLista->pNoCorr ;

      /* Desencadeia � esquerda */

         if ( pNo->pAnt != NULL )
         {
            pNo->pAnt->pProx   = pNo->pProx ;
            pLista->pNoCorr    = pNo->pAnt ;
         } else {
            pLista->pNoCorr    = pNo->pProx ;
            pLista->pOrigemLista = pLista->pNoCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pNo->pProx != NULL )
         {
            pNo->pProx->pAnt = pNo->pAnt ;
         } else
         {
            pLista->pFimLista = pNo->pAnt ;
         } /* if */

      free(pNo) ;

      return;

   } /* Fim fun��o: LIS  &Excluir n� corrente */



	/***************************************************************************
*
*  Fun��o: LIS  &Ir para o proximo n� da lista
*  ****/


	LIS_tpCondRet LIS_IrProx( LIS_tppLista pLista ){

      tpNoLista * pNo ;

      /* Tratar lista vazia */

         if ( pLista->pNoCorr == NULL ) return LIS_CondRetListaVazia;

		 if(pLista->pNoCorr==pLista->pFimLista) return LIS_CondRetFimLista ;
		 /* if */

		 pNo=pLista->pNoCorr;

		 pLista->pNoCorr=pNo->pProx;

		 return LIS_CondRetOK;

	} /* Fim fun��o: LIS &Ir para o proximo n� da lista */



    	/***************************************************************************
*
*  Fun��o: LIS  &Ir para o n� anterior da lista
*  ****/

	LIS_tpCondRet LIS_IrAnt( LIS_tppLista pLista ) {

		tpNoLista * pNo ;

      /* Tratar lista vazia */

         if ( pLista->pNoCorr == NULL ) return LIS_CondRetListaVazia;

		 if(pLista->pNoCorr==pLista->pOrigemLista) return LIS_CondRetNoCorrPrim;
		 /* if */

		 pNo=pLista->pNoCorr;

		 pLista->pNoCorr=pNo->pAnt;

		 return LIS_CondRetOK;

	}/* Fim fun��o: LIS &Ir para o n� anterior da lista */



	   	/***************************************************************************
*
*  Fun��o: LIS  &Alterar valor do n� corrente
*  ****/

	LIS_tpCondRet LIS_AlterarNoCorr( LIS_tppLista pLista , void * pValor ){

		/* Tratar lista vazia ou inexistente */

		if(pLista==NULL) return LIS_CondRetNaoExiste;

		if(pLista->pNoCorr==NULL) return LIS_CondRetListaVazia;

		pLista->pNoCorr->pValor=pValor;

		return LIS_CondRetOK;

	}/* Fim fun��o: LIS &Alterar valor do n� corrente */



/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {
      assert( pLista != NULL ) ;

	  pLista->pNoCorr = pLista->pOrigemLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

         assert( pLista != NULL ) ;
 

		 pLista->pNoCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */




	/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

	LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ){

		/* Tratar lista inexistente */
		tpNoLista * pProx;

        tpNoLista * pNo = pLista->pOrigemLista ;

		if(pLista==NULL) return LIS_CondRetNaoExiste;

        while ( pNo != NULL )
        {
           pProx = pNo->pProx ;
           free(pNo);
           pNo = pProx ;
        } /* while */
		
        pLista->pOrigemLista = NULL ;
        pLista->pFimLista = NULL ;
        pLista->pNoCorr = NULL ;
		free(pLista);
		return LIS_CondRetOK;

	}/* Fim fun��o: LIS  &Destruir lista */



	/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

   /***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o n�
*
***********************************************************************/


	tpNoLista * CriarNo( void * pValor){
	
      tpNoLista * pNo ;

      pNo = ( tpNoLista * ) malloc( sizeof( tpNoLista )) ;
      if ( pNo == NULL )
      {
		printf("/n Falta de memoria para criar no");
         return NULL ;
      } /* if */

      pNo->pValor = pValor ;
      pNo->pAnt   = NULL  ;
      pNo->pProx  = NULL  ;

      return pNo ;

   }/* Fim fun��o: LIS  -Criar o n� */


	/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pNoCorr = NULL ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/