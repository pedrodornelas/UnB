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
			mov		#VETOR,R5				;R5 = ponteiro , R6 = menor, R7 = maior, R8 = cont
			call	#EXTREMOS
			jmp		$
			nop

EXTREMOS:	mov.b	@R5,R8
			mov		#-31666,R7
			mov		#31666,R6

LOOP:		incd	R5
			cmp		@R5,R6
			jhs		menor
			cmp		@R5,R7
			jlo		FIM
			mov		@R5,R7

FIM:		dec		R8
			jnz		LOOP
			RET

menor:		mov		@R5,R6
			jmp 	FIM
			nop
                                            
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
            
