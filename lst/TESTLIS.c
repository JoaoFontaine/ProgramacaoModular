/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.h"

#include    "GENERICO.h"
#include    "LERPARM.h"

#include    "LISTA.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char OBTER_ID_CMD            [ ] = "=obteridlista"   ;
static const char INS_NO_CMD		      [ ] = "=insno"        ;
static const char OBTER_NO_CMD            [ ] = "=obterno" ;
static const char EXC_NO_CMD              [ ] = "=excluirnocorr"    ;
static const char IR_PROX_CMD             [ ] = "=irprox"    ;
static const char ALTERAR_NO_CMD          [ ] = "=alterarnocorr"    ;
static const char IR_ANT_CMD              [ ] = "=irant"    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista  string  CondRetEsp
*     =destruirlista                inxLista  CondRetEsp
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

		 /* Testar ObterIdLista */

		 else if ( strcmp( ComandoTeste , OBTER_ID_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "is" ,
                       &inxLista , StringDado ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) LIS_ObterIdLista( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , &inxLista, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;
            
			vtListas[ inxLista ] = LIS_CriarLista ( pDado );

			if( vtListas[ inxLista ] == NULL)
			{
				return TST_CompararInt( CondRetEsp , TST_CondRetNaoExecutou,
                     "Condicao de retorno errada ao inserir." ) ; 
			}

			return TST_CompararPonteiroNulo( 1 , pDado , "Dado tipo um deveria existir." ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar alterar no corrente */

         else if ( strcmp( ComandoTeste , ALTERAR_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , &inxLista, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;

            CondRet = LIS_AlterarNoCorr( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir." ) ; 

         } /* fim ativa: Testar alterar no corrente */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_DestruirLista( vtListas[ inxLista ]  ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = LIS_InserirNo( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir." ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                  &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

          LIS_ExcluirNoCorr( vtListas[ inxLista ] );

		  return TST_CondRetOK;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRet ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) LIS_ObterNo( vtListas[ inxLista ] ) ;

            if ( pDado == NULL )
            {
               return TST_CondRetOK;

            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* LIS  &Ir para o elemento anterior */

         else if ( strcmp( ComandoTeste , IR_ANT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

           return TST_CompararInt( CondRetEsp ,
                      LIS_IrAnt( vtListas[ inxLista ]  ) ,
                      "Condicao de retorno errada ao retroceder" ) ;

         } /* fim ativa: LIS  &Ir para o elemento anterior */

      /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_IrProx( vtListas[ inxLista ]  ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/
