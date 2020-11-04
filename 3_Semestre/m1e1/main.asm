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
			MOV.W	#VETOR,R5				;Posição de inicío do vetor.
			CALL	#MENOR					;Chamando sub-rotina
			JMP		$						;Fim do programa
			NOP

MENOR:		MOV.B	#0xFF,R6				;Maior elemento possível de 1 Byte
			CLR		R7						;Limpa
			MOV.B	@R5,R8

LOOP:		INC		R5
			CMP.B	@R5,R6
			JLO		FIM
			JEQ		LB
			MOV.B	@R5,R6
			MOV.B	#1,R7

FIM:   		DEC.B	R8
			JNZ		LOOP
			RET

LB:			INC		R7
			JMP 	FIM


			.data							;Inicio de declaração de dados
VETOR:		.byte 14,"RAFAELDORNELAS"		;Declarando vetor de tamanho 14 e o conteúdo do vetor.

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
            
