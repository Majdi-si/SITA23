;programme td3-2
TX		equ		0x0FF4
mode	equ		0x0FF5
etat	equ		0x0FF5

			org		0		;positionnement au début de la mémoire
			jmp		debut	;saut au début du programme principal
			
			org		10		;déclaration des constantes et variables
taille:		cst		14
msg:		cst		'SimKaal IENAC '

			org 	30		
debut:		ldr r0,2
			str [mode],r0
			
binf:		ldr r0,msg
			ldr r4,r0
			ldr r2,[taille]
			
bcle:		ldr r0,2 		;le mask 0000 0010
			ldr r1,r0
wait:		ldr	r0,[etat]	
			and r1,r1r0		;and logic pour teste le bit TV
			jz wait
			
			ldr r0,[r4]
			str [TX],r0
			inc r4
			dec r2
			jnz	bcle
			
			jmp binf
			