
.data
.text
.globl	main
main:
/******  prologo  */
    pushl   %ebp
    movl    %esp, %ebp
	subl	$20, %esp
/*******/

atribuicao:
	movl	8(%ebp), %ecx
	imul	-8(%ebp), %ecx
	movl	%ecx, -4(%ebp)
	
retorno:
	movl	-4(%ebp), %eax

fim:
/****** finalizacao */
	addl	$20, %esp
    movl    %ebp, %esp
    popl    %ebp
	ret			
/*******/


// gcc -m32 -c multiplicacao.s
/* objdump -d multiplicacao.o

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 14             	sub    $0x14,%esp

00000006 <atribuicao>:
   6:	8b 4d 08             	mov    0x8(%ebp),%ecx
   9:	0f af 4d f8          	imul   -0x8(%ebp),%ecx
   d:	89 4d fc             	mov    %ecx,-0x4(%ebp)

00000010 <retorno>:
  10:	8b 45 fc             	mov    -0x4(%ebp),%eax

00000013 <fim>:
  13:	83 c4 14             	add    $0x14,%esp
  16:	89 ec                	mov    %ebp,%esp
  18:	5d                   	pop    %ebp
  19:	c3                   	ret   
  
*/
