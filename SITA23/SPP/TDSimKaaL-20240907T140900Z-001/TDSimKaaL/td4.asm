;programme td4
portC	equ		0x0FF2
mode	equ		0x0FF3

			org		0		;positionnement au début de la mémoire
			jmp		debut	;saut au début du programme principal
			
			org		10		;déclaration des constantes et variables
variable:	var 	?

			org 	30		
debut:		ldr r0,1
			str [mode],r0
binf:		ldr r0,0xFF
			ldr r2,r0
			ldr r1,[variable]
bcle:		inc r1
			str [variable],r1
			str [portC],r1
			dec r2
			jnz bcle
			
			jmp binf
