	.file	"pthreads04.c"
	.comm	lock,40,32
	.globl	global_counter
	.bss
	.align 4
	.type	global_counter, @object
	.size	global_counter, 4
global_counter:
	.zero	4
	.text
	.globl	incrementer
	.type	incrementer, @function
incrementer:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	$lock, %edi
	call	pthread_mutex_lock
	movl	global_counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, global_counter(%rip)
	movl	$lock, %edi
	call	pthread_mutex_unlock
	addl	$1, -4(%rbp)
.L2:
	cmpl	$9999, -4(%rbp)
	jle	.L3
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	incrementer, .-incrementer
	.section	.rodata
.LC0:
	.string	":: waiting... ::"
.LC1:
	.string	":: DONE ::"
.LC2:
	.string	"Expected result: %d\n"
.LC3:
	.string	"Actual   result: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %esi
	movl	$lock, %edi
	call	pthread_mutex_init
	movl	$0, -216(%rbp)
	jmp	.L6
.L7:
	leaq	-208(%rbp), %rax
	movl	-216(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movl	$0, %ecx
	movl	$incrementer, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	addl	$1, -216(%rbp)
.L6:
	cmpl	$23, -216(%rbp)
	jle	.L7
	movl	$.LC0, %edi
	call	puts
	movl	$0, -212(%rbp)
	jmp	.L8
.L9:
	movl	-212(%rbp), %eax
	cltq
	movq	-208(%rbp,%rax,8), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	addl	$1, -212(%rbp)
.L8:
	cmpl	$23, -212(%rbp)
	jle	.L9
	movl	$.LC1, %edi
	call	puts
	movl	$240000, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	global_counter(%rip), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$lock, %edi
	call	pthread_mutex_destroy
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L11
	call	__stack_chk_fail
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
