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
			MOV.W	#VETOR,R5
			CALL	#MAIOR16
			JMP 	$
			NOP

MAIOR16:	CLR		R6
			CLR		R7
			MOV		@R5,R8

LOOP:		INCD	R5
			CMP		@R5,R6
			JEQ		CONT
			JHS		FIM
			MOV 	@R5,R6
			MOV		#1,R7

FIM:		DEC		R8
			JNZ		LOOP
	        RET

CONT:		INC		R7
			JMP 	FIM
			NOP

			.data
VETOR:		.byte	7,0,"RAFAELDORNELAS"
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
            
