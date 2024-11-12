;programme td2

			org		0		;positionnement au début de la mémoire
			jmp		debut	;saut au début du programme principal
			
			org		10		;déclaration des constantes et variables
nombre1:	cst		1	
nombre2:	cst		2	
nombre3:	cst		3	
mult:		cst 	3		
resultat1:	var 	?
resultat2:	var 	?
resultat3:	var 	?

			org 	20			;declaration de la pile
pile:		var 10?
fondpile:	var ?

			org 	40
sous-prog:	push r2
			ldr	r0,0	
bcle:		add r0,r1r0
			dec r2
			jnz	bcle
			
			pop r2
			ret

debut:		ldr r0,fondpile
			ldr sp,r0
			ldr r2,[mult]
			
			ldr r1,[nombre1]
			call sous-prog
			str [resultat1],r0
			
			ldr r1,[nombre2]
			call sous-prog
			str [resultat2],r0
			
			ldr r1,[nombre3]
			call sous-prog
			str [resultat3],r0
			
fin:		hlt
			

			