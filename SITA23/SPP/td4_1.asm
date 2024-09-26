; tp 4-1 ; interruption manuelle
PicuMask EQU 0xFF8
PicuEOI EQU 0xFF9
PPMode EQU 0xFF3
PPPortC EQU 0xFF2
masque EQU 0x05 ; pour que seule l'It manuelle soit autorisée
mode EQU 04

; première instruction
org 0
jmp init

; Table des Vecteurs
org 2 ; adresse en TdV concernant l'interruption IR2 (It Manuelle)
ad_SPIt: VAR ?

; données
org 10
valeur: VAR ? ; notre variable à afficher et incrémenter

; pile
org 20
pile: VAR 10?
fond_pile: VAR ?

; programme
org 40

; sous-programmes d'interruption
It_man: push r0 ; sauvegarde du contexte (registre à modifier)
    ldr r0,0 ;remise à 0 de valeur (par l'intermédiaire d'un registre)
    str [valeur],r0 ; valeur = 0
    ldr r0,0 ; envoi du signal de fin d'interruption (EOI)
    str [PicuEOI],r0 ; EOI ; tp 4-1 ; interruption manuelle
PicuMask EQU 0xFF8
PicuEOI EQU 0xFF9
PPMode EQU 0xFF3
PPPortC EQU 0xFF2
masque EQU 0x05 ; pour que seule l'It manuelle soit autorisée
mode EQU 04

; première instruction
org 0
jmp init

; Table des Vecteurs
org 2 ; adresse en TdV concernant l'interruption IR2 (It Manuelle)
ad_SPIt: VAR ?

; données
org 10
valeur: VAR ? ; notre variable à afficher et incrémenter

; pile
org 20
pile: VAR 10?
fond_pile: VAR ?

; programme
org 40

; sous-programmes d'interruption
It_man: push r0 ; sauvegarde du contexte (registre à modifier)
    ldr r0,0 ;remise à 0 de valeur (par l'intermédiaire d'un registre)
    str [valeur],r0 ; valeur = 0
    ldr r0,0 ; envoi du signal de fin d'interruption (EOI)
    str [PicuEOI],r0 ; EOI qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    pop r0 ; restitution du contexte (registre modifié)
    iret ; retour au programme principal

; programme principal
init: ldr r0, 0          ; CLI
    ldr fl, r0         ; init des flags
    ldr r0, fond_pile  ; init SP
    ldr sp, r0       ; init SP : pile vide
    ldr r0,It_man ;initiation de l'adresse de l'it manuelle dans le registre
    str [ad_SPIt],r0 ; met l'adresse de l'it manuelle dans le TdV (table des vecteurs)
    ldr r0, 1          ; init Port Parallèle
    str [PPMode], r0
    ldr r0, masque     ; init PICU (masque)
    str [PicuMask], r0
    ldr r0, 1          ; STI
    ldr fl, r0
    ldr r0, 0xff       ; valeur max de valeur
    ldr r1, r0         ; stockée dans R1
    ldr r0, 0          ; init valeur à zero
    str [valeur], r0

bcle: ldr r0, [valeur]
    str [PPPortC], r0
    inc r0
    str [valeur], r0
    sub r4, r0r1
    jnz bcle
    jmp bcle
    hlt