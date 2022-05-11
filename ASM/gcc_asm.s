	.file	"gcc_asm.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "result = %d\12\0"
LC1:
	.ascii "input = %d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$0, 28(%esp)
	movl	$1, 24(%esp)
	movl	24(%esp), %eax
/APP
 # 6 ".\gcc_asm.c" 1
	mov %eax, %eax

 # 0 "" 2
/NO_APP
	movl	%eax, 28(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	24(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	leave
	ret
	.ident	"GCC: (i686-posix-sjlj, built by strawberryperl.com project) 4.9.2"
	.def	_printf;	.scl	2;	.type	32;	.endef
