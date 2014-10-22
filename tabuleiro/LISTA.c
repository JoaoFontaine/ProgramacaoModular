/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 Jogo de Xadrez
*  Autores: avs
*  Coautores: Guilherme Araujo e João Pedro Fontaine
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*	  0       Gui   10/out/2014 acréscimo de algumas funções
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
               /* Ponteiro para o valor contido no nó */

         struct tagNoLista * pAnt ;
               /* Ponteiro para o nó predecessor */

         struct tagNoLista * pProx ;
               /* Ponteiro para o nó sucessor */

   } tpNoLista ;



 /***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/
    
 typedef struct LIS_tagLista {

         tpNoLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpNoLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpNoLista * pNoCorr ;
               /* Ponteiro para o nó corrente da lista */
		
		 char idLista[4];
		      /* Estrutura identificadora da lista */

   } LIS_tpLista ;



 /***** Protótipos das funções encapuladas no módulo *****/


	tpNoLista * CriarNo( void * pValor);  
	void LimparCabeca( LIS_tppLista pLista );

	/*****  Código das funções exportadas pelo módulo  *****/



/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/
	
	LIS_tppLista LIS_CriarLista( char * idLista ) {

	  LIS_tpLista * pLista =( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
     
	  if ( pLista == NULL ){
		  printf("\n Faltou memória para criar lista");
		  return NULL;
	  }
	  /*if*/
	  /*if ( strlen(idLista) > 4) printf("\n Só serão utilizados os 4 primeiros caracteres para identificar a lista");

	  strncpy(pLista->idLista , idLista, 4);*/
	  LimparCabeca( pLista ) ;

	  return pLista;

	} /* Fim função: LIS  &Criar lista */



	/***************************************************************************
*
*  Função: LIS  &Orbter Id Lista
*  ****/

	void * LIS_ObterIdLista( LIS_tppLista pLista ) {

		/* Tratar lista vazia */

		if ( pLista == NULL ) return NULL;
		

		return pLista->idLista;

	}/* Fim função: LIS  &Orbter Id Lista */



	/***************************************************************************
*
*  Função: LIS  &Inserir nó
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

   } /* Fim função: LIS  &Inserir nó */



	/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no nó
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

	}/* Fim função: LIS  &Obter referência para o valor contido no nó */



	/***************************************************************************
*
*  Função: LIS  &Excluir nó corrente
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

      /* Desencadeia à esquerda */

         if ( pNo->pAnt != NULL )
         {
            pNo->pAnt->pProx   = pNo->pProx ;
            pLista->pNoCorr    = pNo->pAnt ;
         } else {
            pLista->pNoCorr    = pNo->pProx ;
            pLista->pOrigemLista = pLista->pNoCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pNo->pProx != NULL )
         {
            pNo->pProx->pAnt = pNo->pAnt ;
         } else
         {
            pLista->pFimLista = pNo->pAnt ;
         } /* if */

      free(pNo) ;

      return;

   } /* Fim função: LIS  &Excluir nó corrente */



	/***************************************************************************
*
*  Função: LIS  &Ir para o proximo nó da lista
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

	} /* Fim função: LIS &Ir para o proximo nó da lista */



    	/***************************************************************************
*
*  Função: LIS  &Ir para o nó anterior da lista
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

	}/* Fim função: LIS &Ir para o nó anterior da lista */



	   	/***************************************************************************
*
*  Função: LIS  &Alterar valor do nó corrente
*  ****/

	LIS_tpCondRet LIS_AlterarNoCorr( LIS_tppLista pLista , void * pValor ){

		/* Tratar lista vazia ou inexistente */

		if(pLista==NULL) return LIS_CondRetNaoExiste;

		if(pLista->pNoCorr==NULL) return LIS_CondRetListaVazia;

		pLista->pNoCorr->pValor=pValor;

		return LIS_CondRetOK;

	}/* Fim função: LIS &Alterar valor do nó corrente */



/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {
      assert( pLista != NULL ) ;

	  pLista->pNoCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

         assert( pLista != NULL ) ;
 

		 pLista->pNoCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */




	/***************************************************************************
*
*  Função: LIS  &Destruir lista
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

	}/* Fim função: LIS  &Destruir lista */



	/*****  Código das funções encapsuladas no módulo  *****/

   /***********************************************************************
*
*  $FC Função: LIS  -Criar o nó
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

   }/* Fim função: LIS  -Criar o nó */


	/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pNoCorr = NULL ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/