; tp 4-1 ; interruption manuelle
PicuMask EQU 0xFF8 ; masque d'activation des interruptions
PicuEOI EQU 0xFF9 ; signal de fin d'interruption
PPMode EQU 0xFF3 ; mode du port parallèle
; PPPortC EQU 0xFF2 ; port parallèle
masque EQU 0x04 ; pour que seule l'It manuelle soit autorisée
mode EQU 04 ; mode d'activation des interruptions

SModeEtat EQU 0xFF5 ; mot d'état

SRxTx EQU 0xFF4

; première instruction
org 0
jmp init

; Table des Vecteurs


org 1 
ad_SPIclav: VAR ? ; adresse de l'it clavier

org 2 ; adresse en TdV concernant l'interruption IR2 (It Manuelle)
ad_SPIt: VAR ? ; adresse de l'it manuelle

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
    ldr r0, 1          ; init PICU (mode) qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    ldr fl, r0        ; init PICU (mode) qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    hlt ; arrêt du programme si interruption manuelle
    ldr r0,0 ;remise à 0 de valeur (par l'intermédiaire d'un registre)
    str [valeur],r0 ; valeur = 0
    ldr r0,0 ; envoi du signal de fin d'interruption (EOI)
    str [PicuEOI],r0 ; EOI qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    pop r0 ; restitution du contexte (registre modifié)
    iret ; retour au programme principal

It_clav: push r0
    ldr r2, [SRxTx]
    str [SRxTx], r2
    ldr r0,0 ; envoi du signal de fin d'interruption (EOI)
    str [PicuEOI],r0 ; EOI qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    pop r0
    iret

; programme principal
init: ldr r0, 0          ; init des flags
    ldr fl, r0         ; init des flags
    ldr r0, fond_pile  ; init SP
    ldr sp, r0       ; init SP : pile vide
    ldr r0,It_man ;initiation de l'adresse de l'it manuelle 
    str [ad_SPIt],r0 ; met l'adresse de l'it manuelle dans le TdV (table des vecteurs)
    ldr r0, It_clav
    str [ad_SPIclav], r0
    ldr r0, 1          ; init Port Parallèle
    str [PPMode], r0
    ldr r0, masque     ; init PICU (masque)
    str [PicuMask], r0
    ldr r0, 7
    str [SModeEtat], r0
    ldr r0, 1          ; init PICU (mode) qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    ldr fl, r0        ; init PICU (mode) qui permet de réactiver les interruptions (dans le cas d'une interruption manuelle)
    ldr r0, 0xff       ; valeur max de valeur
    ldr r1, r0         ; stockée dans R1
    ldr r0, 0          ; init valeur à zero
    str [valeur], r0

bcle: ldr r0, [valeur]
    inc r0
    str [valeur], r0
    sub r4, r0r1
    jmp bcle
    hlt