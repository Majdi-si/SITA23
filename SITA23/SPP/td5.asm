; Constantes
PICU_MASK   EQU 0xFF8
PICU_EOI    EQU 0xFF9
PP_MODE     EQU 0xFF3
PP_PORT_A   EQU 0xFF0 ; Barrière
PP_PORT_B   EQU 0xFF1 
PP_PORT_C   EQU 0xFF2 ; Affichage sur 7 segments
MASQUE      EQU 0x00
PP_MODE_VAL EQU 7
TIMER_MODE  EQU 0xFF6
TIMER_BUFF  EQU 0xFF7
SERIAL_MODE EQU 0xFF5
SERIAL_RXTX EQU 0xFF4

; Début du programme
org 0
jmp init

; Vecteurs d'interruption
org 1
vecteur_int_0: var ? ; Niveau d'interruption 1
vecteur_int_1: var ? ; Niveau d'interruption 2
vecteur_int_2: var ? ; Niveau d'interruption 3

; Section des données
org 10
tseg: CST 0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f
barriere: VAR ?
led: VAR ?
direction: VAR ?

; Section de la pile
org 50
pile: VAR 19?
base_pile: VAR ?

; Section du programme
org 72

; Gestionnaire d'interruption pour interruption manuelle
int_manuel: push r0
            push r1
            ldr r0, [direction]  ; Charger la variable direction
            not r0               ; Inverser la direction
            ldr r1, r0           ; Masque
            ldr r0, 1            ; Charger 1
            and r0, r0r1       ; Isoler le bit 0
            str [direction], r0  ; Stocker la direction
            ldr r0, 0
            str [PICU_EOI], r0   ; Envoyer EOI
            pop r1
            pop r0
            iret

; Gestionnaire d'interruption pour interruption de minuterie
int_minuterie: push r0
               push r1
               push r2
               push fl
               ldr r1, [direction]
               ldr r0, 1
               sub r0, r0r1
               ldr r0, [barriere]
               ldr r2, r0           ; Sauvegarder la rotation
               ldr r1, r0           ; Sauvegarder la rotation
               ldr r0, 0x100        ; Masque 0100h
               and r1, r1r0       ; Tester le débordement dans les bits élevés
               inc r2               ; Débordement, ajouter 1 aux bits bas
               ldr r0, 0xff         ; Masque bits élevés
               and r2, r2r0       ; Réinitialiser les bits élevés
     
; Gestionnaire d'interruption pour interruption clavier
int_clavier: push r0
             push r1
             push fl
             ldr r0, [SERIAL_RXTX] ; Charger le caractère du clavier
             ldr r1, r0
             ldr r0, 0x53
             sub r0, r0r1
             jnz pas_ok
             hlt

pas_ok: ldr r0, 0            ; Envoyer EOI
        str [PICU_EOI], r0
        pop fl
        pop r1
        pop r0
        iret

; Routine d'initialisation
init: ldr r0, 0            ; CLI
      ldr fl, r0
      ldr r0, base_pile    ; Initialiser SP
      ldr sp, r0
      ldr r0, 7            ; Initialiser le port série
      str [SERIAL_MODE], r0
      ldr r0, int_clavier  ; Initialiser le vecteur d'interruption pour le clavier
      str [vecteur_int_0], r0
      ldr r0, int_manuel   ; Initialiser le vecteur d'interruption pour interruption manuelle
      str [vecteur_int_1], r0
      ldr r0, int_minuterie ; Initialiser le vecteur d'interruption pour la minuterie
      str [vecteur_int_2], r0
      ldr r0, PP_MODE_VAL  ; Initialiser le port parallèle
      str [PP_MODE], r0
      ldr r0, MASQUE       ; Initialiser le PICU (masque)
      str [PICU_MASK], r0
      ldr r0, 1            ; Initialiser la direction à droite
      str [direction], r0
      ldr r0, 5
      str [barriere], r0
      ldr r0, 0x55         ; Tester la minuterie
      str [led], r0
      ldr r0, 2            ; Initialiser la minuterie en mode périodique
      str [TIMER_MODE], r0
      ldr r0, 0x05F        ; Charger/démarrer la minuterie
      str [TIMER_BUFF], r0
      ldr r0, 1            ; STI
      ldr fl, r0
      ldr r0, [PP_PORT_A]
      str [barriere], r0
      ldr r0,tseg ; Adresse de base du tableau
      ldr r1,r0
      ldr r0,9 ; Offset dans le tableau
      add r4,r1r0 ; Calcul de l’adresse du ’2’
      ldr r2,[r4] ; Code du ’2’ : 0x5b
      str [PP_PORT_C],r2 ; Affichage sur 7 segments
      
      ldr r0, 0xFF        ; Afficher toutes les LEDs sur le port A
      str [PP_PORT_A], r0

boucle: ldr r0, [barriere]
        str [PP_PORT_B], r0
        jmp boucle
        hlt
