;tp4-2 ;interuption manuelle

PicuMask	EQU		0xFF8
PicuEOI		EQU		0xFF9
TX			equ		0x0FF4
RX			equ		0x0FF4
PPmode		equ		0x0FF5
etat		equ		0x0FF5
masque		EQU		0x04
mode		EQU 	07		;pour que seule l'It manuelle soit autorisée

;première instruction
org 0
jmp init

;Table des Vecteurs
org 1						;adresse en Tdv concernant l'interruption IR1 (It manuelle)
ad_SPIt1:	VAR ?
ad_SPIt2:	VAR	?

;données
org 10
char: VAR ?	;notre variable à afficher et incrémenter

;pile
org 20
pile:		VAR 10?
fond_pile:	VAR ?

;programme
org 40

;sous-programmes d'interruption
It_clav:	ldr r0,[RX]
			str [TX],r0
			ldr r0,0
			str [PicuEOI],r0
			iret

It_man:		jmp	fin 

;programme principal
init:		ldr		r0,0
			ldr		fl,r0
			ldr		r0,fond_pile		;initialiser la pile
			ldr 	sp,r0
			ldr		r0,It_clav			;init Tdv
			str		[ad_SPIt1],r0
			ldr		r0,It_man			;init Tdv
			str		[ad_SPIt2],r0
			
			ldr 	r0,mode
			str 	[PPmode],r0
			ldr		r0,masque
			str 	[PicuMask],r0
			ldr		r0,1
			ldr		fl,r0
			
bcle:		jmp 	bcle
fin:		hlt