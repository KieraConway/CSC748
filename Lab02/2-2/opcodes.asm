bits 32
section .text
global _start

_start:
	; Opcodes Reference

	jmp esp                ; ff e4

	call esp               ; ff d4

	push esp               ; 54
	ret

	mov eax, esp           ; 89 e0
	jmp eax					; ff e0

	xchg eax, esp          ; 94
	call eax					;ff d0

	push esp               ; 54
	pop ebx                ; 5b
	jmp ebx				;ff e3

	