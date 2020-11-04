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
			mov 	#MEMO,R5				;ASCIIs dos caracteres
			call	#ASC_W16
OK:			jc		OK						;Travar o programa com êxito
NOK:		jnc		NOK						;Travar o programa com falha.

ASC_W16:	clr		R9
			clr 	R6
			mov		#4,R8					;R8=Contador de execuções
LOOP:		call	#VERIFICA				;R6=NIB correspondente a R5
			jnc		FIM
			call 	#CONVERTE
			add		R7,R9
			mov		R9,R6
			rla		R9
			rla		R9
			rla		R9
			rla		R9
			inc		R5
			dec 	R8
			jnz		LOOP
			setc
FIM:		ret



CONVERTE:	mov.b	@R5,R7					;R7=aux para converter
			cmp.b	#0x3A,0(R5)
			jhs		CASO2
			sub		#0x30,R7
			ret
CASO2:		sub		#0x37,R7
			ret

VERIFICA:	cmp.b	#0x30,0(R5)
			jlo		NAOPODE
			cmp.b	#0x3A,0(R5)
			jlo		PODE
			cmp.b	#0x41,0(R5)
			jlo		NAOPODE
			cmp.b	#0x47,0(R5)
			jlo		PODE
NAOPODE:	clrc
			ret
PODE:		setc
			ret

			.data
MEMO:		.byte	'8','9','A','B'

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
            
