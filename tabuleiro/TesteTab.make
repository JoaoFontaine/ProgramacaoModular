##################################################
###
### Diretivas de MAKE para o construto: TesteTab
### Gerado a partir de: testetab.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteTab


### Nomes de paths

Pobj                 = .
Perr                 = .
PDEFAULT             = .
Pc                   = .

### Nomes de diretórios para geração

Fobj                 = .
Ferr                 = .
FDEFAULT             = .
Fc                   = .

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\TestTab.obj   $(Fobj)\Tab.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\TestTab.obj :  {$(Pc)}\TestTab.c \
    {$(PDEFAULT)}GENERICO.h           {$(PDEFAULT)}LERPARM.h            {$(PDEFAULT)}LISTA.h              \
    {$(PDEFAULT)}TST_ESPC.h           {$(PDEFAULT)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\Tab.obj :  {$(Pc)}\Tab.c \
    {$(Pc)}LISTA.c              {$(PDEFAULT)}LISTA.h              {$(PDEFAULT)}TAB.h               
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\TestTab.obj   $(Fobj)\Tab.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteTab
###
##################################################

