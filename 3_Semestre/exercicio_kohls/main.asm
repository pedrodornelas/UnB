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
			mov 	#INICIO,R5
			call	#FIBINV
			jmp		$
			nop

FIBINV:		mov		@R5,R15					;R5=inicio do vetor
			mov		#1,R8
LOOP:		inc		R8
			incd	R5						;R6 e R7=numeros a somar
			mov		0(R5),R6				;R8= verificar se precisa trocar sinal
			mov 	2(R5),R7				;R15=contador de operações
			mov 	R7,4(R5)
			add		R6,4(R5)
			bit		#BIT0,R8
			jz		FIM
			inv		4(R5)
			inc		4(R5)
FIM:		dec 	R15
			jnz		LOOP
			ret

			.data
INICIO:		.word	20,1,-1
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
            
