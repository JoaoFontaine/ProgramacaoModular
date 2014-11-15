.data
.text
.globl	main
main:
/******  prologo  */
    pushl   %ebp
    movl    %esp, %ebp
	subl	$20, %esp
/*******/

movimentoP:
	movl	8(%ebp), %ecx
	movl	24(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	24(%ebp), %eax
	
	movl	%ecx, 8(%ebp)
	movl	%ecx, 24(%ebp)
	movl	%eax, 8(%ebp)
	movl	%eax, 24(%ebp)

movimentoV:
	movl	-8(%ebp), %ecx
	movl	-24(%ebp), %ecx
	movl	-8(%ebp), %eax
	movl	-24(%ebp), %eax
	
	movl	%ecx, -8(%ebp)
	movl	%ecx, -24(%ebp)
	movl	%eax, -8(%ebp)
	movl	%eax, -24(%ebp)
	
movimentoS:
	movl	$2, %ecx
	movl	$20, %ecx
	movl	$2, %eax
	movl	$20, %eax
	
	movl	$2, -8(%ebp)
	movl	$20, -24(%ebp)
	movl	$2, 8(%ebp)
	movl	$20, 24(%ebp)
	
fim:
/****** finalizacao */
	addl	$20, %esp
    movl    %ebp, %esp
    popl    %ebp
	ret			
/*******/


// gcc -m32 -c movimentacao.s
/* objdump -d movimentacao.o

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 14             	sub    $0x14,%esp

00000006 <movimentoP>:
   6:	8b 4d 08             	mov    0x8(%ebp),%ecx
   9:	8b 4d 18             	mov    0x18(%ebp),%ecx
   c:	8b 45 08             	mov    0x8(%ebp),%eax
   f:	8b 45 18             	mov    0x18(%ebp),%eax
  12:	89 4d 08             	mov    %ecx,0x8(%ebp)
  15:	89 4d 18             	mov    %ecx,0x18(%ebp)
  18:	89 45 08             	mov    %eax,0x8(%ebp)
  1b:	89 45 18             	mov    %eax,0x18(%ebp)

0000001e <movimentoV>:
  1e:	8b 4d f8             	mov    -0x8(%ebp),%ecx
  21:	8b 4d e8             	mov    -0x18(%ebp),%ecx
  24:	8b 45 f8             	mov    -0x8(%ebp),%eax
  27:	8b 45 e8             	mov    -0x18(%ebp),%eax
  2a:	89 4d f8             	mov    %ecx,-0x8(%ebp)
  2d:	89 4d e8             	mov    %ecx,-0x18(%ebp)
  30:	89 45 f8             	mov    %eax,-0x8(%ebp)
  33:	89 45 e8             	mov    %eax,-0x18(%ebp)

00000036 <movimentoS>:
  36:	b9 02 00 00 00       	mov    $0x2,%ecx
  3b:	b9 14 00 00 00       	mov    $0x14,%ecx
  40:	b8 02 00 00 00       	mov    $0x2,%eax
  45:	b8 14 00 00 00       	mov    $0x14,%eax
  4a:	c7 45 f8 02 00 00 00 	movl   $0x2,-0x8(%ebp)
  51:	c7 45 e8 14 00 00 00 	movl   $0x14,-0x18(%ebp)
  58:	c7 45 08 02 00 00 00 	movl   $0x2,0x8(%ebp)
  5f:	c7 45 18 14 00 00 00 	movl   $0x14,0x18(%ebp)

00000066 <fim>:
  66:	83 c4 14             	add    $0x14,%esp
  69:	89 ec                	mov    %ebp,%esp
  6b:	5d                   	pop    %ebp
  6c:	c3                   	ret    

*/
