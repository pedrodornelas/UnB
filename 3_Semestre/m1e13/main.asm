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
			mov		#NUM_ROM,R6				;início do número
			call	#ROM_ARAB
			jmp 	$
			nop

ROM_ARAB:	clr		R5						;R5=Num_rom, R7=ordem dos numeros
			mov 	#INT,R10				;R10=converte
			clr 	R8						;R8=aux, R9=CONT
			clr		R7
			mov.b 	#0,R11

LOOP1:		cmp.b	@R6,#0
			jeq		FIM
			mov		R7,R8
			mov		#NUMEROS,R7
			call	#PROCURA
			cmp		R8,R7
			jlo		SUB
			add		R9,R10
			add		@R10,R5
			mov		#INT,R10
			inc 	R6
			jmp		LOOP1

FIM:		RET

SUB:		add		R9,R10
			sub		@R10,R5
			mov		#INT,R10
			inc		R6
			jmp		LOOP1

PROCURA:	clr 	R9
LOOP:		cmp.b	@R6,0(R7)
			jeq		RETORNA
			inc		R7
			incd	R9
			jmp		LOOP
RETORNA:	RET

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
            
