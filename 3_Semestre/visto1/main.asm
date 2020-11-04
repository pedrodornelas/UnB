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
NUM			.equ	2019					;Número a ser convertido

			mov 	#NUM,R5					;R5=Número a ser convertido
			mov 	#RESP,R6				;R6=Ponteiro para escrever a resposta
			call	#ALG_ROM				;Chamar subrotina
			jmp		$
			nop

ALG_ROM:	mov 	#INT,R7					;R7=número inteiro para converter
			mov		#NUM_ROM,R8				;R8=número em romano para adicionar

LOOP:		cmp		R5,0(R7)
			jeq		ACHEI
			jlo		ACHEI
			incd	R7
			incd	R8
			jmp		LOOP

ACHEI:		bit.b	#BIT0,0(R8)
			jz		LB
			mov.b 	0(R8),0(R6)
			inc		R6
LB:			mov.b	1(R8),0(R6)
			sub		@R7,R5
			inc		R6
			cmp		#0,R5
			jeq		FIM
			jmp 	LOOP

FIM:		RET

			.data
RESP:		.byte	"RRRRRRRRRRRRRRRRRR",0
NUM_ROM:	.byte	0,"M","CM",0,"D","CD",0,"C","XC",0,"L","XL",0,"X","IX",0,"V","IV",0,"I",0	;Ordem dos números romanos
INT:		.word	1000,900,500,400,100,90,50,40,10,9,5,4,1,0									;Pesos dos números
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
            
