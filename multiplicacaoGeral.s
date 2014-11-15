.data
.text
.globl	main
main:
/******  prologo  */
    pushl   %ebp
    movl    %esp, %ebp
	subl	$20, %esp
/*******/

multiplicacaoP:
	imul	8(%ebp), %ecx
	imul	24(%ebp), %ecx
	imul	8(%ebp), %eax
	imul	24(%ebp), %eax

multiplicacaoV:
	imul	-4(%ebp), %ecx
	imul	-20(%ebp), %ecx
	imul	-4(%ebp), %eax
	imul	-20(%ebp), %eax
	
multiplicacaoS:
	imul	$2, %ecx
	imul	$20, %ecx
	imul	$2, %eax
	imul	$20, %eax
	
fim:
/****** finalizacao */
	addl	$20, %esp
    movl    %ebp, %esp
    popl    %ebp
	ret			
/*******/

// gcc -m32 -c multiplicacaoGeral.s
/* objdump -d multiplicacaoGeral.o

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 14             	sub    $0x14,%esp

00000006 <multiplicacaoP>:
   6:	0f af 4d 08          	imul   0x8(%ebp),%ecx
   a:	0f af 4d 18          	imul   0x18(%ebp),%ecx
   e:	0f af 45 08          	imul   0x8(%ebp),%eax
  12:	0f af 45 18          	imul   0x18(%ebp),%eax

00000016 <multiplicacaoV>:
  16:	0f af 4d fc          	imul   -0x4(%ebp),%ecx
  1a:	0f af 4d ec          	imul   -0x14(%ebp),%ecx
  1e:	0f af 45 fc          	imul   -0x4(%ebp),%eax
  22:	0f af 45 ec          	imul   -0x14(%ebp),%eax

00000026 <multiplicacaoS>:
  26:	6b c9 02             	imul   $0x2,%ecx,%ecx
  29:	6b c9 14             	imul   $0x14,%ecx,%ecx
  2c:	6b c0 02             	imul   $0x2,%eax,%eax
  2f:	6b c0 14             	imul   $0x14,%eax,%eax

00000032 <fim>:
  32:	83 c4 14             	add    $0x14,%esp
  35:	89 ec                	mov    %ebp,%esp
  37:	5d                   	pop    %ebp
  38:	c3  
 
 */
