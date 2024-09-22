org 0
jmp debut ; Saut au début du programme

; Déclaration des constantes et des variables
nombre1: cst 1
nombre2: cst 2
nombre3: cst 3
mult: cst 4
resultat1: var 1?
resultat2: var 1?
resultat3: var 1?

; Pile simulée avec une adresse de base
stack_base: cst 0x1000
stack_pointer: var 0? ; Le pointeur de pile commence à 0 (sera initialisé plus tard)

org 20
debut: ldr r3, =stack_base  ; Charger l'adresse de base de la pile dans r3


; Multiplication de nombre1 par mult
ldr r1, [nombre1]
ldr r2, [mult]
call multiplication
str [resultat1], r0 ; Stocke le résultat dans resultat1

; Multiplication de nombre2 par mult
ldr r1, [nombre2]
ldr r2, [mult]
call multiplication
str [resultat2], r0 ; Stocke le résultat dans resultat2

; Multiplication de nombre3 par mult
ldr r1, [nombre3]
ldr r2, [mult]
call multiplication
str [resultat3], r0 ; Stocke le résultat dans resultat3

hlt ; Arrêt du programme

; Sous-programme de multiplication sans `push` ni `pop`
multiplication: ldr r3, [stack_pointer] ; Charge l'adresse actuelle du pointeur de pile
str r4, [r3] ; Stocke r4 à l'adresse de la pile
add r3, r3, #1 ; Incrémente le pointeur de pile
str r3, [stack_pointer] ; Met à jour le pointeur de pile

ldr r0, =0 ; Initialisation du résultat à 0
boucle: add r0, r0, r1 ; Ajout de r1 à r0 (addition répétée)
dec r2 ; Décrémentation du multiplicateur
jnz boucle ; Si r2 n'est pas zéro, continue la boucle

; Restauration manuelle de r4
ldr r3, [stack_pointer] ; Charge l'adresse actuelle du pointeur de pile
sub r3, r3, #1 ; Décrémente le pointeur de pile
ldr r4, [r3] ; Restaure r4 depuis la pile
str r3, [stack_pointer] ; Met à jour le pointeur de pile

ret ; Retour de la fonction

