;tp4-1 ;interuption manuelle

PicuMask	EQU		0xFF8
PicuEOI		EQU		0xFF9
PPMode		EQU		0xFF3
PPPortC		EQU		0xFF2
masque		EQU		0x05
mode		EQU 	04		;pour que seule l'It mqnuelle soit autorisée

;première instruction
org 0
jmp init

;Table des Vecteurs
org 2						;adresse en Tdv concernant l'interruption IR1 (It manuelle)
ad_SPIt:	VAR	?

;données
org 10
valeur: VAR ?	;notre variable à afficher et incrémenter

;pile
org 20
pile:		VAR 10?
fond_pile:	VAR ?

;programme
org 40

;sous-programmes d'interruption
It_man:		ldr r0,0 ; Var=0 and End Of Interrupt
			str [valeur],r0
			str [PicuEOI],r0
			iret


;programme principal
init:		ldr		r0,0
			ldr		fl,r0
			ldr		r0,fond_pile
			ldr 	sp,r0
			ldr		r0,It_man						;init Tdv
			str		[ad_SPIt],r0
			ldr		r0,1
			str		[PPMode],r0
			ldr		r0,masque
			str 	[PicuMask],r0
			ldr		r0,1
			ldr		fl,r0
			
			ldr		r0,0xFF
			ldr		r1,r0
			ldr		r0,0
			str		[valeur],r0
			
bcle:		ldr		r0,[valeur]
			str		[PPPortC],r0
			inc		r0
			str		[valeur],r0
			sub		r4,r0r1
			jnz		bcle
			jmp 	bcle
			hlt