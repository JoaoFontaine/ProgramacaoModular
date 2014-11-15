
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
	addl	24(%ebp), %ecx
	movl	%ecx, -4(%ebp)
	
retorno:
	movl	-4(%ebp), %ecx
	movl	-4(%ebp), %eax

fim:
/****** finalizacao */
	addl	$20, %esp
    movl    %ebp, %esp
    popl    %ebp
	ret			
/*******/


// gcc -m32 -c adicao.s
/* objdump -d adicao.o

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 14             	sub    $0x14,%esp

00000006 <atribuicao>:
   6:	8b 4d 08             	mov    0x8(%ebp),%ecx
   9:	03 4d 18             	add    0x18(%ebp),%ecx
   c:	89 4d fc             	mov    %ecx,-0x4(%ebp)

0000000f <retorno>:
   f:	8b 4d fc             	mov    -0x4(%ebp),%ecx
  12:	8b 45 fc             	mov    -0x4(%ebp),%eax

00000015 <fim>:
  15:	83 c4 14             	add    $0x14,%esp
  18:	89 ec                	mov    %ebp,%esp
  1a:	5d                   	pop    %ebp
  1b:	c3                   	ret    
  
*/
