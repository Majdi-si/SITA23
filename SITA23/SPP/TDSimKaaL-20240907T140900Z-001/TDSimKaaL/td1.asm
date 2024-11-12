;programme demo td1
ad_debut 	equ		30		;directive
val_debut	equ		0		;directive

			org		0		;positionnement au début de la mémoire
			jmp	debut		;saut au début du programme principal
			org		8
taille:		cst		10 		;declaration de la constante "taille"
tableau:	var 	11?	;declaration de la variable "tableau" (10cases)

			org 	20			;début du programme principal
debut:		ldr	r0,[taille]	;recup cste taille
			ldr	r1,r0		;taille dans r1 (servira de compteur)
			ldr	r0,val_debut;recup adresse de début de tableau dans r0
			ldr	r2,r0
			ldr	r0,tableau
			ldr	r4,r0
bcle:		str	[r4],r2
			inc	r2
			inc	r4
			dec	r1
			jnz	bcle
fin:		hlt
			