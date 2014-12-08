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

#ifdef _DEBUG
   #include   "Generico.h"
   #include   "Conta.h"
   #include   "CESPDIN.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/


 typedef struct tagNoLista {

	 #ifdef _DEBUG

         struct LIS_tagLista * pCabeca ;
               /* Ponteiro para cabeca */
			
     #endif

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

	 #ifdef _DEBUG

         int numNo ;
               /* Numero de nos */
     #endif

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

	#ifdef _DEBUG
	LIS_tpCondRet VerificarNo( tpNoLista * pNo );
	#endif

	/*****  Dados encapsulados no módulo  *****/

      #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

      #endif


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

	   #ifdef _DEBUG
	  pLista->numNo = 0;
         CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
      #endif

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

		#ifdef _DEBUG
		 pLista->numNo ++;
		 CED_DefinirTipoEspaco( pNo , LIS_TipoEspacoNo ) ;
		#endif   

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
			//printf(" \n Lista Vazia");
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

	    #ifdef _DEBUG
	  pLista->numNo--;
      #endif

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

   void LIS_IrInicioLista( LIS_tppLista pLista )
   {
      assert( pLista != NULL ) ;

	  pLista->pNoCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void LIS_IrFinalLista( LIS_tppLista pLista )
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

	/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpNoLista * pNo ;
      tpNoLista * pProx ;

      pNo = pLista->pOrigemLista ;
      while ( pNo != NULL )
      {
         pProx = pNo->pProx ;
         free(pNo) ;
         pNo = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

   /***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista, void* pValor )
   {

      tpNoLista * pNo ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pNoCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pNo = pLista->pNoCorr; pNo != NULL; pNo = pNo->pProx )
      {
         if ( pNo->pValor == pValor )
         {
            pLista->pNoCorr = pNo ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou;
	} /* Fim função: LIS  &Procurar elemento contendo valor */

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar uma lista
*  ****/


   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista pLista) {

	  LIS_tpLista * pListaAux = NULL ;

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_VerificarLista" ) ;
      #endif

      if ( LIS_VerificarCabeca( pLista) != LIS_CondRetOK )
      {
		 #ifdef _DEBUG
         CNT_CONTAR( "LIS_VerificarCabecaErro" ) ;
         #endif

         return LIS_CondRetErroEstrutura ;
      } /* if */

	  #ifdef _DEBUG
         CNT_CONTAR( "LIS_VerificarCabecaOK" ) ;
      #endif

      CED_MarcarEspacoAtivo( pLista ) ;

      pListaAux = ( LIS_tpLista * ) ( pLista ) ;

	  if(pListaAux->pOrigemLista != NULL){

		  #ifdef _DEBUG
         CNT_CONTAR( "pOrigem nao NULL" ) ;
          #endif

		  return LIS_VerificarNo(pListaAux->pOrigemLista);
	  
	  }/* if */
	  else{
		  
		  if(pListaAux->pNoCorr != NULL){

			  #ifdef _DEBUG
			 CNT_CONTAR( "pNoCorr nao NULL" ) ;
			#endif

			  return LIS_VerificarNo(pListaAux->pNoCorr);
	  
		  }/* if */
		  else {

			  if(pListaAux->pFimLista != NULL){

				   #ifdef _DEBUG
					CNT_CONTAR( "pFim nao NULL" ) ;
					#endif

				 return LIS_VerificarNo(pListaAux->pFimLista);
			  
			  }/* if */

		  }/* else */

	  }/* else */

	   #ifdef _DEBUG
		CNT_CONTAR( "Lista vazia" ) ;
	   #endif

	  return LIS_CondRetOK;
	 

   } /* Fim função: LIS  &Verificar uma lista */

 #endif



 #ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar cabeca de lista
*  ****/


   LIS_tpCondRet LIS_VerificarCabeca( void * pLista) {

	   LIS_tpLista * pListaAux = NULL ;

	   tpNoLista * pNoAux = NULL ;

	   int numDeNo = 0;

	    #ifdef _DEBUG
			 CNT_CONTAR( "LIS_VerificarCabeca" ) ;
			#endif

	   /* Verifica o tipo do espaço */

         if ( pLista == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "pLista NULL" ) ;
			#endif

            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

		 if ( ! CED_VerificarEspaco( pLista , NULL ))
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Erro verificar espaco cabeca" ) ;
			#endif

            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

		   if ( TST_CompararInt( LIS_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pLista) ,
              "Tipo do espaço de dados não é cabeça de lista." ) != TST_CondRetOK )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Nao e cabeca de lista" ) ;
			#endif

            return LIS_CondRetErroEstrutura ;
         } /* if */

		   #ifdef _DEBUG
			 CNT_CONTAR( "Cabeca OK" ) ;
			#endif

		   pListaAux = ( LIS_tpLista * )( pLista ) ;

      /* Verifica no corrente */

		   if ( pListaAux->pNoCorr != NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Verifica corrente" ) ;
			#endif

			 if ( TST_CompararPonteiro( pLista , pListaAux->pNoCorr->pCabeca ,
                 "Nó corrente não aponta para cabeça." ) != TST_CondRetOK )
            {
				#ifdef _DEBUG
			 CNT_CONTAR( "No corrrente nao aponta cabeca" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
			 if ( TST_CompararPonteiro( NULL , pListaAux->pNoCorr ,
                 "Lista vazia tem nó corrente não NULL." ) != TST_CondRetOK )
            {
				#ifdef _DEBUG
			 CNT_CONTAR( "Lista vazia tem no corrente nao NULL" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */


		/* Verifica comeco lista */

		   if ( pListaAux->pOrigemLista!= NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Verifica Origem" ) ;
			#endif

			 if ( TST_CompararPonteiro( pLista , pListaAux->pOrigemLista->pCabeca ,
                 "Primeiro no não aponta para cabeça." ) != TST_CondRetOK )
            {

				#ifdef _DEBUG
			 CNT_CONTAR( "Primeiro no nao aponta para cabeca" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
			 if ( TST_CompararPonteiro( NULL , pListaAux->pOrigemLista ,
                 "Lista vazia tem primeiro no não NULL." ) != TST_CondRetOK )
            {
				#ifdef _DEBUG
			 CNT_CONTAR( "Lista vazia tem primeiro no nao NULL" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

	 /* Verifica fim lista */

		   if ( pListaAux->pFimLista != NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Verifica Fim" ) ;
			#endif

			 if ( TST_CompararPonteiro( pLista , pListaAux->pFimLista->pCabeca,
                 "Ultimo no não aponta para cabeça." ) != TST_CondRetOK )
            {
				#ifdef _DEBUG
			 CNT_CONTAR( "Ultimo no nao aponta para cabeca" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else {
			 if ( TST_CompararPonteiro( NULL , pListaAux->pFimLista ,
                 "Lista vazia tem ultimo no não NULL." ) != TST_CondRetOK )
            {

				#ifdef _DEBUG
			 CNT_CONTAR( "Lista vazia tem ultimo no nao NULL" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */


		   #ifdef _DEBUG
			 CNT_CONTAR( "Lista vazia" ) ;
			#endif

		   pNoAux = (tpNoLista *) (pListaAux->pOrigemLista);

		/* Verfica veracidade do numero de nos */

		   while (pNoAux != NULL){

			   numDeNo ++;
			   pNoAux = pNoAux->pProx;

		   }/* while */


		   if (pListaAux->numNo != numDeNo) {
			   
			   #ifdef _DEBUG
			 CNT_CONTAR( "Erro numero de nos" ) ;
			#endif

			   TST_NotificarFalha( "Numero de nos informado pela cabeca diferente do real." ) ;
            return LIS_CondRetErroEstrutura ;

		   }/* if */


		   #ifdef _DEBUG
			 CNT_CONTAR( "Numero de nos OK" ) ;
			#endif

		   return LIS_CondRetOK ;
	 

   } /* Fim função: LIS  &Verificar cabeca de lista */

 #endif


 #ifdef _DEBUG

   /***************************************************************************
*
*  Função: LIS &Verificar um nó da lista
*  ****/

   LIS_tpCondRet LIS_VerificarNo( void * pNo )
   {

	   #ifdef _DEBUG
			 CNT_CONTAR( "LIS_VerificarNo" ) ;
			#endif

      tpNoLista * pNoAux     = NULL ;
      LIS_tpLista * pListaAux = NULL ;

      /* Verificar se é nó estrutural */

         if ( pNo == NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "No NULL" ) ;
			#endif

            TST_NotificarFalha( "Tentou verificar nó inexistente." ) ;
            return LIS_CondRetErroEstrutura ;

         } /* if */

         if ( ! CED_VerificarEspaco( pNo , NULL ))
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Erro verificar espaco no" ) ;
			#endif

            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return LIS_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( LIS_TipoEspacoNo ,
              CED_ObterTipoEspaco( pNo ) ,
              "Tipo do espaço de dados não é nó de lista." ) != TST_CondRetOK )
         {
			  #ifdef _DEBUG
			 CNT_CONTAR( "Nao e no" ) ;
			#endif

            return LIS_CondRetErroEstrutura ;
         } /* if */

		  #ifdef _DEBUG
			 CNT_CONTAR( "No OK" ) ;
			#endif

         pNoAux     = ( tpNoLista * )( pNo ) ;
         pListaAux = pNoAux->pCabeca ;

      /* Verificar cabeça */

		 if ( pListaAux->pNoCorr != NULL  )
         {
			  #ifdef _DEBUG
			 CNT_CONTAR( "Verifica cabeca" ) ;
			#endif

			 if ( TST_CompararPonteiro( pListaAux , pListaAux->pNoCorr->pCabeca,
                 "Nó não pertence à lista." ) != TST_CondRetOK )
            {
				 #ifdef _DEBUG
			 CNT_CONTAR( "No nao pertence a lista" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "No pertence a lista vazia" ) ;
			#endif

            TST_NotificarFalha( "Nó pertence a lista vazia." ) ;
			return LIS_CondRetErroEstrutura ;
         } /* if */

      /* Verificar anterior */

		 if ( pNoAux->pAnt != NULL )
         {

			  #ifdef _DEBUG
			 CNT_CONTAR( "Verifica anterior" ) ;
			#endif

			 if ( TST_CompararPonteiro( pNoAux , pNoAux->pAnt->pProx ,
                 "O proximo do anterior nao é o corrente." ) != TST_CondRetOK )
            {

				#ifdef _DEBUG
			 CNT_CONTAR( "O proximo do anterior nao e o corrente" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
			 if ( TST_CompararPonteiro( pNoAux , pListaAux->pOrigemLista,
                 "No nao possui anterior mas nao é o inicial." ) != TST_CondRetOK )
            {
				#ifdef _DEBUG
			 CNT_CONTAR( "No nao possui anterior mas nao e o inicial" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verificar proximo */

         if ( pNoAux->pProx != NULL )
         {
			 #ifdef _DEBUG
			 CNT_CONTAR( "Verificar proximo" ) ;
			#endif


			 if ( TST_CompararPonteiro( pNoAux , pNoAux->pProx->pAnt ,
                 "O anterior do proximo nao e o corrente." ) != TST_CondRetOK )
            {

				 #ifdef _DEBUG
			 CNT_CONTAR( "O anterior do proximo nao e o corrente" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } else
         {
			 if ( TST_CompararPonteiro( pNoAux , pListaAux->pFimLista,
                 "No nao possui proximo mas nao é o final." ) != TST_CondRetOK )
            {

				 #ifdef _DEBUG
			 CNT_CONTAR( "No nao possui proximo mas nao e o final" ) ;
			#endif

               return LIS_CondRetErroEstrutura ;
            } /* if */
         } /* if */

		 #ifdef _DEBUG
			 CNT_CONTAR( "No OK" ) ;
			#endif

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verificar um nó de lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS &Deturpar lista
*  ****/

   void ARV_Deturpar( LIS_tppLista pLista ,
                      LIS_tpModosDeturpacao ModoDeturpar )
   {

      LIS_tppLista pListaAux = NULL ;

      if ( pLista == NULL )
      {
         return ;
      } /* if */

      pListaAux = ( LIS_tppLista  )( pLista) ;

      switch ( ModoDeturpar ) {

      /* Modifica o tipo da cabeça */

         case DeturpaTipoCabeca :
         {

            CED_DefinirTipoEspaco( pListaAux , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } /* fim ativa: Modifica o tipo da cabeça */

	  /* Modifica numero de nos */

         case DeturparNumNo :
         {

			 pListaAux->numNo++ ;

            break ;

         } /* fim ativa: Modifica numero de nos */

      /* Anula ponteiro origem */

         case DeturpaPtOrigemNulo :
         {

			 pListaAux->pOrigemLista = NULL ;

            break ;

         } /* fim ativa: Anula ponteiro origem */

	/* Anula ponteiro final */

         case DeturpaPtFimNulo :
         {

			 pListaAux->pFimLista = NULL ;

            break ;

         } /* fim ativa: Anula ponteiro final */

      /* Anula ponteiro corrente */

         case DeturpaCorrenteNulo :
         {

            pListaAux->pNoCorr = NULL ;

            break ;

         } /* fim ativa: Anula ponteiro corrente */

      /* Faz cabeca apontar para lixo */

         case DeturpaCabecaLixo :
         {

            pListaAux = ( LIS_tppLista )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz cabeca apontar para lixo */

	 /* Faz origem apontar para lixo */

         case DeturpaPtOrigemLixo :
         {

			 pListaAux->pOrigemLista = ( tpNoLista * )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz origem apontar para lixo */

	/* Faz pnteiro final para lixo */

         case DeturpaPtFimLixo :
         {

			 pListaAux->pFimLista = ( tpNoLista * )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz finnal apontar para lixo */

      /* Faz corrente apontar para lixo */

         case DeturpaCorrenteLixo :
         {

            pListaAux->pNoCorr = ( tpNoLista * )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz corrente apontar para lixo */

      /* Deturpar espaço cabeca */

         case DeturparEspacoCabeca :
         {

            memcpy( (( char * )( pListaAux )) - 10 , "????" , 4 ) ;

            break ;

         } /* fim ativa: Deturpar espaço cabeca */

      /* Deturpa nóo */

         default :

         if ( pListaAux->pNoCorr != NULL )
         {

            switch ( ModoDeturpar ) {

            /* Modifica tipo nó corrente */

               case DeturpaTipoNo :
               {

                  CED_DefinirTipoEspaco( pListaAux->pNoCorr , CED_ID_TIPO_VALOR_NULO ) ;

                  break ;

               } /* fim ativa: Modifica tipo nó corrente */

            /* Anula ponteiro cabeça */

               case DeturpaPtCabecaNulo :
               {

                  pListaAux->pNoCorr->pCabeca = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro cabeça */

            /* Anula ponteiro prox */

               case DeturpaPtProxNulo :
               {

                  pListaAux->pNoCorr->pProx = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro prox */

            /* Anula ponteiro anterior */

               case DeturpaPtAntNulo :
               {

				   pListaAux->pNoCorr->pAnt = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro anterior */

            /* Faz ponteiro cabeça apontar para lixo */

               case DeturpaPtCabecaLixo :
               {

                  pListaAux->pNoCorr->pCabeca = ( LIS_tppLista )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro cabeça apontar para lixo */

            /* Faz ponteiro prox apontar para lixo */

               case DeturpaPtProxLixo :
               {

				   pListaAux->pNoCorr->pProx = ( tpNoLista * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro prox apontar para lixo */

            /* Faz ponteiro anterior apontar para lixo */

               case DeturpaPtAntLixo :
               {

                  pListaAux->pNoCorr->pAnt = ( tpNoLista * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro anteriror apontar para lixo */

            /* Atribui valor fora do domínio do espaço */

               case DeturpaValor :
               {

                  memcpy( &( pListaAux->pNoCorr->pValor ) , "<<<<<" , 5 ) ;

                  break ;

               } /* fim ativa: Atribui valor fora do domínio do espaço */

            /* Deturpar espaço no */

               case DeturparEspacoNo :
               {

                  memcpy( (( char * )( pListaAux->pNoCorr )) - 50 , "????????" , 8 ) ;

                  break ;

               } /* fim ativa: Deturpar espaço no */

            } /* fim seleciona: Deturpa nóo */

            break ;

         } /* fim ativa: Deturpa nóo */

      } /* fim seleciona: Cabeca de lista  &Deturpar lista */

   } /* Fim função: LIS &Deturpar lista */

#endif



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


   #ifdef _DEBUG


/***********************************************************************
*
*  $FC Função: LIS  -Explorar verificando os nós de uma lista
*
*  $ED Descrição da função
*     Percorre recursivamente a lista verificando os nós à medida que forem
*     visitados. Caso seja encontrado alguma falha, a verificação será
*     suspensa. Portanto, no caso de falha, é possível que nem todos
*     os nós da lista sejam visitados.
*
***********************************************************************/

   LIS_tpCondRet VerificarNo( tpNoLista * pNo )
   {

      LIS_tpCondRet CondErro = LIS_CondRetOK ;

      if ( pNo == NULL )
      {
         return LIS_CondRetOK ;
      } /* if */

      CED_MarcarEspacoAtivo( pNo ) ;

      CondErro = LIS_VerificarNo( pNo ) ;

      if ( CondErro == LIS_CondRetOK )
      {
		  CondErro = VerificarNo( pNo->pProx) ;
      } /* if */

      if ( CondErro == LIS_CondRetOK )
      {
		  CondErro = VerificarNo( pNo->pAnt) ;
      } /* if */

      return CondErro ;

   } /* Fim função: LIS  -Explorar verificando os nós de uma álista */

#endif



/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/