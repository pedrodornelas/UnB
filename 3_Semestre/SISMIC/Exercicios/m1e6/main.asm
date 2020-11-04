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
			mov		#VETOR1,R5				;R5=VETOR1,R6=VETOR2,R7=MENOS_SIGNIFICATIVOS,R8=MAIS_SIGNIFICATIVOS,R9=CONT,R10=aux
			mov 	#VETOR2,R6
			call	#SUM_TOT
			jmp 	$
			nop

SUM_TOT:	mov 	@R5,R9
			clr		R7
			clr		R8

LOOP:		incd	R5
			incd	R6
			mov		0(R6),R10
			add		0(R5),R10
			add		R10,R7
			jnc		FIM
			add		#1,R8

FIM:		dec		R9
			jnz		LOOP
			RET

            .data
VETOR1:		.word	7,65000,50054,26472,53000,60606,814,41121
VETOR2:		.word	7,226,3400,26472,470,1020,44444,12345
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
            
