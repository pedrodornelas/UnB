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
			mov		#VETOR,R5
			call 	#ORDENA
			jmp		$
			nop

ORDENA:		mov.b 	0(R5),R6				;R6=contador de operações
			dec		R6						;Fazer n-1 vezes
			inc		R5						;R8=ponteiro para fazer operações no vetor
LOOP:		mov		R5,R8					;Posição inicial do vetor
			mov.b 	R6,R9					;R9=passagens dentro do vetor
LUPI:		cmp.b	0(R8),1(R8)				;R7=Registrador aux para fazer a troca de posições
			jhs		NAOTROCA
			call	#ORD
NAOTROCA:	inc 	R8
			dec		R9
			jnz		LUPI

			dec		R6
			jz		FIM
			jmp		LOOP
FIM:		ret

ORD:		mov.b	0(R8),R7
			mov.b	1(R8),0(R8)
			mov.b	R7,1(R8)
FINAL:		ret

			.data
VETOR:		.byte	10,"PEDROLUCAS"
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
            
