.data
.text
.globl	main
main:
/******  prologo  */
    pushl   %ebp
    movl    %esp, %ebp
	subl	$20, %esp
/*******/

adicaoP:
	addl	8(%ebp), %ecx
	addl	24(%ebp), %ecx
	addl	8(%ebp), %eax
	addl	24(%ebp), %eax
	
	addl	%ecx, 8(%ebp)
	addl	%ecx, 24(%ebp)
	addl	%eax, 8(%ebp)
	addl	%eax, 24(%ebp)

adicaoV:
	addl	-4(%ebp), %ecx
	addl	-20(%ebp), %ecx
	addl	-4(%ebp), %eax
	addl	-20(%ebp), %eax
	
	addl	%ecx, -4(%ebp)
	addl	%ecx, -20(%ebp)
	addl	%eax, -4(%ebp)
	addl	%eax, -20(%ebp)
	
adicaoS:
	addl	$2, %ecx
	addl	$20, %ecx
	addl	$2, %eax
	addl	$20, %eax
	
	addl	$2, -4(%ebp)
	addl	$20, -20(%ebp)
	addl	$2, 4(%ebp)
	addl	$20, 20(%ebp)
	
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

00000006 <adicaoP>:
   6:	03 4d 08             	add    0x8(%ebp),%ecx
   9:	03 4d 18             	add    0x18(%ebp),%ecx
   c:	03 45 08             	add    0x8(%ebp),%eax
   f:	03 45 18             	add    0x18(%ebp),%eax
  12:	01 4d 08             	add    %ecx,0x8(%ebp)
  15:	01 4d 18             	add    %ecx,0x18(%ebp)
  18:	01 45 08             	add    %eax,0x8(%ebp)
  1b:	01 45 18             	add    %eax,0x18(%ebp)

0000001e <adicaoV>:
  1e:	03 4d fc             	add    -0x4(%ebp),%ecx
  21:	03 4d ec             	add    -0x14(%ebp),%ecx
  24:	03 45 fc             	add    -0x4(%ebp),%eax
  27:	03 45 ec             	add    -0x14(%ebp),%eax
  2a:	01 4d fc             	add    %ecx,-0x4(%ebp)
  2d:	01 4d ec             	add    %ecx,-0x14(%ebp)
  30:	01 45 fc             	add    %eax,-0x4(%ebp)
  33:	01 45 ec             	add    %eax,-0x14(%ebp)

00000036 <adicaoS>:
  36:	83 c1 02             	add    $0x2,%ecx
  39:	83 c1 14             	add    $0x14,%ecx
  3c:	83 c0 02             	add    $0x2,%eax
  3f:	83 c0 14             	add    $0x14,%eax
  42:	83 45 fc 02          	addl   $0x2,-0x4(%ebp)
  46:	83 45 ec 14          	addl   $0x14,-0x14(%ebp)
  4a:	83 45 04 02          	addl   $0x2,0x4(%ebp)
  4e:	83 45 14 14          	addl   $0x14,0x14(%ebp)

00000052 <fim>:
  52:	83 c4 14             	add    $0x14,%esp
  55:	89 ec                	mov    %ebp,%esp
  57:	5d                   	pop    %ebp
  58:	c3                   	ret
 
 */
