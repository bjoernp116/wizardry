	.file	"font.c"
	.text
	.globl	get_pixel
	.type	get_pixel, @function
get_pixel:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, %ecx
	movl	%edx, %eax
	movl	%ecx, %edx
	movb	%dl, -44(%rbp)
	movb	%al, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	17(%rax), %eax
	movb	%al, -29(%rbp)
	movq	-40(%rbp), %rax
	movq	32(%rax), %rcx
	movzbl	-48(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	24(%rax), %eax
	imull	%edx, %eax
	movslq	%eax, %rsi
	movzbl	-44(%rbp), %edx
	movzbl	-29(%rbp), %eax
	imull	%edx, %eax
	cltq
	addq	%rsi, %rax
	addq	%rcx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -28(%rbp)
	movb	$0, -20(%rbp)
	movb	$0, -19(%rbp)
	movb	$0, -18(%rbp)
	movb	$0, -17(%rbp)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rsi
	leaq	-20(%rbp), %rax
	leaq	3(%rax), %r8
	leaq	-20(%rbp), %rax
	leaq	2(%rax), %rdi
	leaq	-20(%rbp), %rax
	leaq	1(%rax), %rcx
	leaq	-20(%rbp), %rdx
	movl	-28(%rbp), %eax
	movq	%r8, %r9
	movq	%rdi, %r8
	movl	%eax, %edi
	call	SDL_GetRGBA@PLT
	movzbl	-20(%rbp), %eax
	movzbl	%al, %eax
	sall	$24, %eax
	movl	%eax, %edx
	movzbl	-19(%rbp), %eax
	movzbl	%al, %eax
	sall	$16, %eax
	addl	%eax, %edx
	movzbl	-18(%rbp), %eax
	movzbl	%al, %eax
	sall	$8, %eax
	addl	%eax, %edx
	movzbl	-17(%rbp), %eax
	movzbl	%al, %eax
	addl	%edx, %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	get_pixel, .-get_pixel
	.section	.rodata
.LC0:
	.string	"Loading Font!"
.LC1:
	.string	"rb"
.LC2:
	.string	"(%d, %d)\n"
.LC3:
	.string	"done"
	.text
	.globl	load_font
	.type	load_font, @function
load_font:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	leaq	-16384(%rsp), %r11
.LPSRL0:
	subq	$4096, %rsp
	orq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LPSRL0
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -16440(%rbp)
	movq	%rsi, -16448(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16448(%rbp), %rax
	leaq	.LC1(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_RWFromFile@PLT
	movl	$1, %esi
	movq	%rax, %rdi
	call	SDL_LoadBMP_RW@PLT
	movq	%rax, -16424(%rbp)
	movl	$0, -16432(%rbp)
	jmp	.L5
.L8:
	movl	$0, -16428(%rbp)
	jmp	.L6
.L7:
	movl	-16428(%rbp), %edx
	movl	-16432(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16428(%rbp), %eax
	movzbl	%al, %edx
	movl	-16432(%rbp), %eax
	movzbl	%al, %ecx
	movl	-16428(%rbp), %eax
	sall	$6, %eax
	movl	%eax, %esi
	movl	-16432(%rbp), %eax
	leal	(%rsi,%rax), %ebx
	movq	-16424(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	get_pixel
	movl	%ebx, %edx
	movl	%eax, -16416(%rbp,%rdx,4)
	addl	$1, -16428(%rbp)
.L6:
	cmpl	$62, -16428(%rbp)
	jbe	.L7
	addl	$1, -16432(%rbp)
.L5:
	cmpl	$62, -16432(%rbp)
	jbe	.L8
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-16440(%rbp), %rax
	movq	%rax, %rcx
	leaq	-16416(%rbp), %rax
	movl	$16384, %edx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	memcpy@PLT
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L10
	call	__stack_chk_fail@PLT
.L10:
	movq	-16440(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	load_font, .-load_font
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
