;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
			mov 	#VETOR,R5
			call	#EXTREMOS
			jmp		$
			nop

EXTREMOS:	mov		@R5+,R8					;R6=menor elemento
			mov		0(R5),R6				;R7=maior elemento
            mov     2(R5),R7                ;R8=contador de operações
            cmp 	R6,R7					;R9=aux para fazer a troca inicial
            jge		LOOP
            mov		R6,R9					;Verificar se os 2 primeiros estão nas posições corretas
            mov		R7,R6
            mov		R9,R7

LOOP:		cmp		0(R5),R6
			jl		MAIOR
			mov		0(R5),R6
            jmp		FINAL
MAIOR:		cmp		0(R5),R7
			jge		FINAL
			mov		0(R5),R7

FINAL:		incd 	R5
			dec		R8
			jnz		LOOP
            ret
                                            
			.data
VETOR:		.word	4,180,108,140,-2000
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
