	.file	"PrefCounter.c"
	.section .rdata,"dr"
LC0:
	.ascii ".\\PrefCounter.c\0"
	.align 4
LC1:
	.ascii "iCounter && \"iCounter is NULL pointer.\"\0"
	.text
	.globl	_PrefCounter
	.def	_PrefCounter;	.scl	2;	.type	32;	.endef
_PrefCounter:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$48, %esp
	cmpl	$0, 8(%ebp)
	jne	L2
	movl	$7, 8(%esp)
	movl	$LC0, 4(%esp)
	movl	$LC1, (%esp)
	call	__assert
	jmp	L4
L2:
	nop
L4:
/APP
 # 9 ".\PrefCounter.c" 1
	rdtsc
mov %eax, %edx
mov %edx, %eax

 # 0 "" 2
/NO_APP
	movl	%edx, -12(%ebp)
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	$0, %edx
	movl	%eax, %edx
	movl	$0, %eax
	movl	%eax, -32(%ebp)
	movl	%edx, -28(%ebp)
	movl	-12(%ebp), %eax
	movl	$0, %edx
	movl	%eax, %ecx
	orl	-32(%ebp), %ecx
	movl	%ecx, %ebx
	movl	%edx, %eax
	orl	-28(%ebp), %eax
	movl	%eax, %esi
	movl	8(%ebp), %eax
	movl	%ebx, (%eax)
	movl	%esi, 4(%eax)
	addl	$48, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.ident	"GCC: (i686-posix-sjlj, built by strawberryperl.com project) 4.9.2"
	.def	__assert;	.scl	2;	.type	32;	.endef
