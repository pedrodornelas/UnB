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
			mov 	#SEQTRIB,R5
			call	#TRIB
			jmp 	$
			nop

TRIB:		clr		R8						;R7=elemento de provocou a parada
			add		#6,R5
			mov		#2,R6

LOOP:		mov 	-4(R5),R7
			rla		R7
			add		-2(R5),R7
			sub		-6(R5),R7
			sub		-6(R5),R7
			sub		-6(R5),R7
			mov		R7,0(R5)
			inc		R6
			incd	R5
			cmp		#500,R7
			jge		FIM
			jmp		LOOP

FIM:		ret

			.data
SEQTRIB:	.word	1,2,1
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
            
