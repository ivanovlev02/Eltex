	.file	"bitwise_oper.c"
	.text
	.section	.rodata
.LC0:
	.string	"a = %X\n"
.LC1:
	.string	"%X\n"
.LC2:
	.string	"\nb(a_new) = %X\n"
.LC3:
	.string	"\na1 = %X\n"
.LC4:
	.string	"a1(new) = %X\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$16755387, -8(%rbp)
	movl	$11202235, -4(%rbp)
	movl	$0, -12(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L2
.L4:
	movl	-12(%rbp), %eax
	movl	-8(%rbp), %edx
	movl	%eax, %ecx
	sarl	%cl, %edx
	movl	%edx, %eax
	movb	%al, -17(%rbp)
	movzbl	-17(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpl	$16, -12(%rbp)
	jne	.L3
	movl	-8(%rbp), %eax
	andl	$15663103, %eax
	movl	%eax, -16(%rbp)
.L3:
	addl	$8, -12(%rbp)
.L2:
	cmpl	$24, -12(%rbp)
	jle	.L4
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	orl	$16711680, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
