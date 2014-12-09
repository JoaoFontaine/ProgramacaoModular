/***************************************************************************
*  $MCI Módulo de implementação: TTAB Teste do modulo tabuleiro
*
*  Arquivo gerado:              TestTAB.c
*  Letras identificadoras:      TTAB
*
*  Projeto: INF 1301 Jogo de Xadrez
*  Autores: Guilherme Araujo e Joao Pedro Fontaine
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include "LISTA.h"

#include    "TST_ESPC.h"

#include    "GENERICO.h"
#include    "LERPARM.h"

#include "CESPDIN.h"
#include	"TAB.h"

static const char RESET_TAB_CMD				  [ ] = "=resetteste"     ;
static const char CRIAR_TAB_CMD				  [ ] = "=criartab"     ;
static const char DESTRUIR_TAB_CMD            [ ] = "=destruirtab"  ;
static const char OBTER_PECA_CMD              [ ] = "=obterpeca"   ;
static const char INS_PECA_CMD		          [ ] = "=inspeca"        ;
static const char RETIRAR_PECA_CMD            [ ] = "=retirarpeca" ;
static const char MOVER_PECA_CMD              [ ] = "=moverpeca"    ;
static const char OBTER_LST_AMEACANTES_CMD    [ ] = "=obterlistaameacantes"    ;
static const char OBTER_LST_AMEACADOS_CMD     [ ] = "=obterlistaameacados"    ;

/* os comandos a seguir somente operam em modo _DEBUG */

const char VER_TAB_CMD[ ] = "=verificartabuleiro" ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TAB  10


TAB_tppTab   vtTab[ DIM_VT_TAB ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxTab( int inxTab , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas até 10 tabuleiros, identificados pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de tabuleiros. Provoca vazamento de memória
*     =criartab                   inxLista  
*     =destruirtab                inxLista  CondRetEsp
*     =obterpeca                 inxLista  string 
*     =inspeca						inxLista  string  
*     =moverpeca						inxLista  string  CondretEsp
*     =excluirpeca                inxLista  
*     =obterlistaameacantes						inxLista  CondretEsp
*     =obterlistaameacados         inxLista  CondretEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxTab  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   CharDado1 = '?';
	  char   CharDado2 = '!';
	  char   CharDado3 = '\0';

	  TAB_tppPeca pPeca;
  
	  int ValDado1 = -1;
	  int ValDado2 = -1;

      int i ;

     
      /* Efetuar reset de teste de tab */

         if ( strcmp( ComandoTeste , RESET_TAB_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_TAB; i++ )
            {
               vtTab[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de tab */

		 /* Testar ObterPeca */

		 else if ( strcmp( ComandoTeste , OBTER_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iic" ,
                       &inxTab , &ValDado1, &CharDado1  ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pPeca =  TAB_ObterPeca( ValDado1, CharDado1, vtTab[ inxTab ] ) ;

            if ( pPeca == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pPeca ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CondRetOK;

         } /* fim ativa: Testar obter peca*/

      /* Testar CriarTab */

         else if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxTab );

            if ( ( numLidos != 1 )
              || ( ! ValidarInxTab( inxTab , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			vtTab[inxTab] = TAB_CriarTab();

			if( vtTab[ inxTab ] == NULL)
			{
				return TST_CompararInt( CondRetEsp , TST_CondRetNaoExecutou,
                     "Condicao de retorno errada ao inserir." ) ; 
			}

			return TST_CompararPonteiroNulo( 1 , vtTab[inxTab]  , "Dado tipo um deveria existir." ) ;

         } /* fim ativa: Testar CriarTab */

      /* Testar mover peca */

         else if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iicici" , &inxTab, &ValDado1, &CharDado1,
				                         &ValDado2, &CharDado2,  &CondRetEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxTab( inxTab, NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = TAB_MoverPeca (ValDado1, CharDado1,
				                         ValDado2, CharDado2, vtTab[inxTab]);
			

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao mover." ) ; 

         } /* fim ativa: Testar mover peca */

      /* Testar Destruir tab */

         else if ( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxTab, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      TAB_DestruirTab( vtTab[ inxTab ]  ) ,
                      "Condicao de retorno errada ao destruir tabuleiro" ) ;

         } /* fim ativa: Testar Destruir tab */

      /* Testar inserir peca */

         else if ( strcmp( ComandoTeste , INS_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiccci" ,
                       &inxTab , &ValDado1 ,&CharDado1, &CharDado2, &CharDado3,  &CondRetEsp ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */


            CondRet = TAB_InserirPeca(ValDado1 ,CharDado1, CharDado2, CharDado3, vtTab[ inxTab ]) ;
			
            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir." ) ;

         } /* fim ativa: Testar inserir peca */

      /* Testar retirar peca */

         else if ( strcmp( ComandoTeste , RETIRAR_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iici" ,
                  &inxTab, &ValDado1, &CharDado1, &CondRetEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

          CondRet = TAB_RetirarPeca(ValDado1 ,CharDado1, vtTab[ inxTab ]) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao retirar." ) ;

         } /* fim ativa: Testar retirar peca */

      /* Testar obter lista ameacantes */

         else if ( strcmp( ComandoTeste , OBTER_LST_AMEACANTES_CMD ) == 0 )
         {

           numLidos = LER_LerParametros( "iici" ,
                  &inxTab, &ValDado1, &CharDado1, &CondRetEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararPonteiroNulo( 1 , TAB_ObterListaAmeacantes( ValDado1, CharDado1 , vtTab[inxTab])  
				                            , "Dado tipo um deveria existir." ) ;

         } /* fim ativa: Testar obter lista de ameacantes */

      /* Testar obter lista ameacados */

         else if ( strcmp( ComandoTeste , OBTER_LST_AMEACADOS_CMD ) == 0 )
         {

           numLidos = LER_LerParametros( "iici" ,
                  &inxTab, &ValDado1, &CharDado1, &CondRetEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararPonteiroNulo( 1 , TAB_ObterListaAmeacados( ValDado1, CharDado1 , vtTab[inxTab])  
				                            , "Dado tipo um deveria existir." ) ;

         } /* fim ativa: Testar obter lista de ameacados */

		#ifdef _DEBUG

		 /* Testar verificador do tabuleiro */

         else if ( strcmp( ComandoTeste , VER_TAB_CMD ) == 0 )
         {

           numLidos = LER_LerParametros( "ii" ,
                  &inxTab, &ValDado1) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxTab( inxTab , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( TAB_VerificarTab(vtTab[inxTab]) , ValDado1 ,
                     "Numero de falhas esperado errado." ) ;

         } /* fim ativa: Testar verificador do tabuleiro*/

		#endif

      return TST_CondRetNaoConhec ;

   } /* Fim função: TTAB &Testar tabuleiro */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TTAB -Destruir valor */


/***********************************************************************
*
*  $FC Função: TTAB -Validar indice de tab
*
***********************************************************************/

   int ValidarInxTab( int inxTab , int Modo )
   {

      if ( ( inxTab <  0 )
        || ( inxTab >= DIM_VT_TAB ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtTab[ inxTab ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtTab[ inxTab ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TTab -Validar indice de tab */

/********** Fim do módulo de implementação: TTAB Teste tabuleiro **********/
