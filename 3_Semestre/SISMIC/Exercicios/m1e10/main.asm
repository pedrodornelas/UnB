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
MATR		.set	18010
			mov		#MATR,R6
			call	#W16_ASC
			jmp		$
			nop

W16_ASC:	mov		#4,R8
			mov		#0x2400,R5
LUPI:		mov		R6,R7
			and		#0x000F,R7
			call	#NIB_ASC
			mov.b	R7,0(R5)
			inc		R5
			rrc		R6
			rrc		R6
			rrc		R6
			rrc 	R6
			dec 	R8
			jnz		LUPI
			ret

NIB_ASC:	cmp.b	#10,R7
			jhs		LB
			add		#30,R7
            ret
LB:         add		#37,R7
			ret
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
            
