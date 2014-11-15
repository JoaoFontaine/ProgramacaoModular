.data
.text
.globl	main
main:
/******  prologo  */
    pushl   %ebp
    movl    %esp, %ebp
	subl	$20, %esp
/*******/

subtracaoP:
	subl	8(%ebp), %ecx
	subl	24(%ebp), %ecx
	subl	8(%ebp), %eax
	subl	24(%ebp), %eax
	
	subl	%ecx, 8(%ebp)
	subl	%ecx, 24(%ebp)
	subl	%eax, 8(%ebp)
	subl	%eax, 24(%ebp)

subtracaoV:
	subl	-4(%ebp), %ecx
	subl	-20(%ebp), %ecx
	subl	-4(%ebp), %eax
	subl	-20(%ebp), %eax
	
	subl	%ecx, -4(%ebp)
	subl	%ecx, -20(%ebp)
	subl	%eax, -4(%ebp)
	subl	%eax, -20(%ebp)
	
subtracaoS:
	subl	$2, %ecx
	subl	$20, %ecx
	subl	$2, %eax
	subl	$20, %eax
	
	subl	$2, -4(%ebp)
	subl	$20, -20(%ebp)
	subl	$2, 4(%ebp)
	subl	$20, 20(%ebp)
	
fim:
/****** finalizacao */
	addl	$20, %esp
    movl    %ebp, %esp
    popl    %ebp
	ret			
/*******/

// gcc -m32 -c adicaoGeral.s
/* objdump -d adicaoGeral.o

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 14             	sub    $0x14,%esp

00000006 <subtracaoP>:
   6:	2b 4d 08             	sub    0x8(%ebp),%ecx
   9:	2b 4d 18             	sub    0x18(%ebp),%ecx
   c:	2b 45 08             	sub    0x8(%ebp),%eax
   f:	2b 45 18             	sub    0x18(%ebp),%eax
  12:	29 4d 08             	sub    %ecx,0x8(%ebp)
  15:	29 4d 18             	sub    %ecx,0x18(%ebp)
  18:	29 45 08             	sub    %eax,0x8(%ebp)
  1b:	29 45 18             	sub    %eax,0x18(%ebp)

0000001e <subtracaoV>:
  1e:	2b 4d fc             	sub    -0x4(%ebp),%ecx
  21:	2b 4d ec             	sub    -0x14(%ebp),%ecx
  24:	2b 45 fc             	sub    -0x4(%ebp),%eax
  27:	2b 45 ec             	sub    -0x14(%ebp),%eax
  2a:	29 4d fc             	sub    %ecx,-0x4(%ebp)
  2d:	29 4d ec             	sub    %ecx,-0x14(%ebp)
  30:	29 45 fc             	sub    %eax,-0x4(%ebp)
  33:	29 45 ec             	sub    %eax,-0x14(%ebp)

00000036 <subtracaoS>:
  36:	83 e9 02             	sub    $0x2,%ecx
  39:	83 e9 14             	sub    $0x14,%ecx
  3c:	83 e8 02             	sub    $0x2,%eax
  3f:	83 e8 14             	sub    $0x14,%eax
  42:	83 6d fc 02          	subl   $0x2,-0x4(%ebp)
  46:	83 6d ec 14          	subl   $0x14,-0x14(%ebp)
  4a:	83 6d 04 02          	subl   $0x2,0x4(%ebp)
  4e:	83 6d 14 14          	subl   $0x14,0x14(%ebp)

00000052 <fim>:
  52:	83 c4 14             	add    $0x14,%esp
  55:	89 ec                	mov    %ebp,%esp
  57:	5d                   	pop    %ebp
  58:	c3                   	ret    
 
 */
