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
			call	#FIB16					;R6(MSB),R5(LSB) = primeiro número
			call	#FIB32					;R8(MSB),R7(LSB) = segundo número
			jmp 	$						;R9 = soma menos significativos
			nop								;R12 = soma mais significativos
											;RESP: R11(MSB)R10(LSB)

FIB32:		mov		#1,R8
			mov		R6,R5
			clr 	R6

LOOP2:		mov		R7,R9
			mov 	R8,R12
			add		R5,R9
			addc	R6,R12
			jc		FIM2
			mov		R8,R6
			mov		R7,R5
			mov		R9,R7
			mov 	R12,R8
			jmp		LOOP2

FIM2:		mov 	R8,R11
			mov		R7,R10
			RET


FIB16:		clr 	R7
			mov 	#1,R5
			mov 	#1,R6

LOOP:       mov 	R6,R7
            add		R5,R7
            jc		FIM
        	mov		R6,R5
        	mov 	R7,R6
        	jmp		LOOP

FIM:		mov 	R6,R10
            RET
                                            

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
            
