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
			mov 	#NUM_ROM,R6
			call	#ROM_ARAB
			jmp		$
			nop

ROM_ARAB:	clr 	R5						;R5=Número
INICIO:		mov		#INT,R9					;R9=contador para converter
			mov 	#NUMEROS,R7				;R7=Número em Romano
			mov		#NUMEROS,R8				;R8=Próximo número em Romano
			cmp.b	#0,0(R6)
			jeq		FIM

LOOP:		cmp.b	@R6,0(R7)
			jeq		ACHEI
			inc		R7
			incd	R9
			jmp		LOOP

ACHEI:		inc		R6
			cmp.b	#0,0(R6)
			jeq		SOMA

LOOP1:		cmp.b	@R6,0(R8)
			jeq 	ACHEI2
			inc		R8
			jmp		LOOP1

ACHEI2:		cmp		R7,R8
			jlo		PROBLEMA
SOMA:		add		@R9,R5
			jmp		INICIO

PROBLEMA:	sub		@R9,R5
			jmp 	INICIO

FIM:		RET

			.data
NUM_ROM:	.byte	"MMXIX",0
NUMEROS:	.byte	"MDCLXVI",0
INT:		.word	1000,500,100,50,10,5,1,0
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
            
