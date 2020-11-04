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
			MOV		#VETOR,R5
			CALL	#M2M4
			JMP 	$
			NOP

M2M4:		MOV.B	@R5,R8
			CLR		R6
			CLR		R7

LOOP:		INC 	R5
			MOV.B 	@R5,R9
			RRA		R9
			JC		FIM
			CLRC
			INC		R6
			RRA		R9
			JC		FIM
			CLRC
			INC		R7

FIM:		DEC 	R8
			JNZ		LOOP
			RET
                                            
			.data
VETOR:		.byte	4,1,2,3,4				;"PEDROHENRIQUE"
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
            
