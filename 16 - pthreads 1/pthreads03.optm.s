	.file	"pthreads03.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.globl	incrementer
	.type	incrementer, @function
incrementer:
.LFB26:
	.cfi_startproc
	addl	$10000, global_counter(%rip)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE26:
	.size	incrementer, .-incrementer
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	":: waiting... ::"
.LC2:
	.string	":: DONE ::"
.LC3:
	.string	"Expected result: %d\n"
.LC4:
	.string	"Actual   result: %d\n"
	.section	.text.unlikely
.LCOLDB5:
	.section	.text.startup,"ax",@progbits
.LHOTB5:
	.globl	main
	.type	main, @function
main:
.LFB27:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$208, %rsp
	.cfi_def_cfa_offset 240
	leaq	8(%rsp), %rbx
	leaq	200(%rsp), %r12
	movq	%fs:40, %rax
	movq	%rax, 200(%rsp)
	xorl	%eax, %eax
	movq	%rbx, %rbp
.L3:
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$incrementer, %edx
	addq	$8, %rbx
	call	pthread_create
	cmpq	%rbx, %r12
	jne	.L3
	movl	$.LC1, %edi
	xorl	%ebx, %ebx
	call	puts
.L4:
	movq	0(%rbp,%rbx), %rdi
	xorl	%esi, %esi
	addq	$8, %rbx
	call	pthread_join
	cmpq	$192, %rbx
	jne	.L4
	movl	$.LC2, %edi
	call	puts
	movl	$240000, %edx
	movl	$.LC3, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	movl	global_counter(%rip), %edx
	xorl	%eax, %eax
	movl	$.LC4, %esi
	movl	$1, %edi
	call	__printf_chk
	xorl	%eax, %eax
	movq	200(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L5
	call	__stack_chk_fail
.L5:
	addq	$208, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE5:
	.section	.text.startup
.LHOTE5:
	.globl	global_counter
	.bss
	.align 4
	.type	global_counter, @object
	.size	global_counter, 4
global_counter:
	.zero	4
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
