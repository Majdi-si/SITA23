;programme td3-1
portA	equ		0x0FF0
portB	equ		0x0FF1
portC	equ		0x0FF2
mode	equ		0x0FF3

			org		0		;positionnement au début de la mémoire
			jmp		debut	;saut au début du programme principal
			
			org		10		;déclaration des constantes et variables
mult:		cst 	3
msg:		cst		'SimKaal IENAC'

			org 	30		
debut:		ldr r0,1
			str [mode],r0
binf:		ldr r0,0
			ldr r1,[portA]
			ldr r2,[mult]

bcle:		add r0,r1r0
			dec r2
			jnz	bcle
			str [portC],r0
			
			jmp binf