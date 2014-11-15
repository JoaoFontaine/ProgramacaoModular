.data
.text
.globl	main
main:
/******  prologo  */
    pushl   %ebp
    movl    %esp, %ebp
	subl	$20, %esp
/*******/

compP:
	movl	8(%ebp), %ecx
	movl	-24(%ebp), %eax
	cmpl	%ecx, %eax
	je	compV
	
	movl	24(%ebp), %ecx
	movl	$20, %eax
	cmpl	%ecx, %eax
	je	compV

	
compV:
	movl	-4(%ebp), %ecx
	movl	24(%ebp), %eax
	cmpl	%ecx, %eax
	je	compS
	
	movl	-20(%ebp), %ecx
	movl	$687, %eax
	cmpl	%ecx, %eax
	je	compS
	
	
compS:	
	movl	$3, %ecx
	movl	$20, %eax
	cmpl	%ecx, %eax
	je	fim
	
	movl	$20, %ecx
	movl	-4(%ebp), %eax
	cmpl	%ecx, %eax
	je	fim
	
	movl	$687, %ecx
	movl	24(%ebp), %eax
	cmpl	%ecx, %eax
	je	fim

fim:
/****** finalizacao */
	addl	$20, %esp
    movl    %ebp, %esp
    popl    %ebp
	ret			
/*******/


// gcc -m32 -c compGeral.s
/* objdump -d compGeral.o

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 14             	sub    $0x14,%esp

00000006 <compP>:
   6:	8b 4d 08             	mov    0x8(%ebp),%ecx
   9:	8b 45 e8             	mov    -0x18(%ebp),%eax
   c:	39 c8                	cmp    %ecx,%eax
   e:	74 0c                	je     1c <compV>
  10:	8b 4d 18             	mov    0x18(%ebp),%ecx
  13:	b8 14 00 00 00       	mov    $0x14,%eax
  18:	39 c8                	cmp    %ecx,%eax
  1a:	74 00                	je     1c <compV>

0000001c <compV>:
  1c:	8b 4d fc             	mov    -0x4(%ebp),%ecx
  1f:	8b 45 18             	mov    0x18(%ebp),%eax
  22:	39 c8                	cmp    %ecx,%eax
  24:	74 0c                	je     32 <compS>
  26:	8b 4d ec             	mov    -0x14(%ebp),%ecx
  29:	b8 af 02 00 00       	mov    $0x2af,%eax
  2e:	39 c8                	cmp    %ecx,%eax
  30:	74 00                	je     32 <compS>

00000032 <compS>:
  32:	b9 03 00 00 00       	mov    $0x3,%ecx
  37:	b8 14 00 00 00       	mov    $0x14,%eax
  3c:	39 c8                	cmp    %ecx,%eax
  3e:	74 18                	je     58 <fim>
  40:	b9 14 00 00 00       	mov    $0x14,%ecx
  45:	8b 45 fc             	mov    -0x4(%ebp),%eax
  48:	39 c8                	cmp    %ecx,%eax
  4a:	74 0c                	je     58 <fim>
  4c:	b9 af 02 00 00       	mov    $0x2af,%ecx
  51:	8b 45 18             	mov    0x18(%ebp),%eax
  54:	39 c8                	cmp    %ecx,%eax
  56:	74 00                	je     58 <fim>

00000058 <fim>:
  58:	83 c4 14             	add    $0x14,%esp
  5b:	89 ec                	mov    %ebp,%esp
  5d:	5d                   	pop    %ebp
  5e:	c3                   	ret
  
 */

