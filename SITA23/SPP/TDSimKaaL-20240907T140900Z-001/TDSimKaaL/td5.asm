;tp4-2 ;interuption manuelle

PicuMask	EQU		0xFF8
PicuEOI		EQU		0xFF9
TX			equ		0x0FF4
RX			equ		0x0FF4
SSmode		equ		0x0FF5
etat		equ		0x0FF5
PPMode		EQU		0xFF3
PPPortC		EQU		0xFF2
TMPmode		EQU		0xff6
Cmpt		EQU		0xff7

masque		EQU		0x00
mode		EQU 	07		;pour que seule l'It manuelle soit autorisée

;première instruction
org 0
jmp init

;Table des Vecteurs
org 1						;adresse en Tdv concernant l'interruption IR1 (It manuelle)
ad_SPIt1:	VAR ?
ad_SPIt2:	VAR	?
ad_SPIt3:	VAR	?


;données
org 10
stop:	cst	'S'
cheni: 	VAR ?	;notre variable à afficher et incrémenter

;pile
org 20
pile:		VAR 10?
fond_pile:	VAR ?

;programme
org 40

;sous-programmes d'interruption
It_clav:	push r0
			push r1
			ldr r0,[stop]
			ldr r1,r0
			ldr r0,[RX]
			sub r1,r0r1
			jz fin
			ldr r0,0
			str [PicuEOI],r0
			pop r1
			pop r0
			iret

It_man:		jmp	fin 

It_timer:	ldr 	r0,[cheni]
			str		[PPPortC],r0
			ROL		r0,1
			str		[cheni],r0
			AND		r0,r0r1
			jnz		bcint
 	

;programme principal
init:		ldr		r0,0
			ldr		fl,r0
			ldr		r0,fond_pile		;initialiser la pile
			ldr 	sp,r0
			ldr		r0,It_clav			;init Tdv
			str		[ad_SPIt1],r0
			ldr		r0,It_man			;init Tdv
			str		[ad_SPIt2],r0
			ldr		r0,It_timer			;init Tdv
			str		[ad_SPIt3],r0
			
			ldr 	r0,mode
			str 	[SSmode],r0
			ldr		r0,1
			str		[PPMode],r0
			ldr		r0,masque
			str 	[PicuMask],r0
			ldr		r0,2
			str		[TMPmode],r0
			ldr		r0,1
			ldr		fl,r0
			ldr		r0,0x100
			ldr		r1,r0
			
bcint:		ldr 	r0,1
			str 	[cheni],r0
			
bcle:		jmp 	bcle
			
fin:		hlt