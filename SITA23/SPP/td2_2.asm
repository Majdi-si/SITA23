val_debut equ 0
    org 0
    jmp debut

    org 8
    nombre1: cst 1
    nombre2: cst 2
    nombre3: cst 3
    mult: cst 4
    resultat1: var 1?
    resultat2: var 1?
    resultat3: var 1?

    org 30
    stack_base: var 0?      ; Simuler la pile avec une adresse de base (ajoutez une ligne pour la pile)
    org 40
debut: ldr r3, [stack_base] ; Initialiser l'adresse de base de la pile dans r3
    ldr r1, [nombre1]      ; multiplication de nombre1 par mult
    ldr r2, [mult]
    call multiplication
    str [resultat1], r0

    ldr r1, [nombre2]      ; multiplication de nombre2 par mult
    ldr r2, [mult]
    call multiplication
    str [resultat2], r0

    ldr r1, [nombre3]      ; multiplication de nombre3 par mult
    ldr r2, [mult]
    call multiplication
    str [resultat3], r0 

    hlt                    ; Fin du programme

multiplication: push r4                ; Sauvegarde de r4 dans la pile
    ldr r0, 0              ; Initialisation de r0 à 0
boucle: add r0, r1r0          ; Ajouter r1 à r0
    dec r2                ; Décrémenter r2
    jnz boucle            ; Reboucler tant que r2 n'est pas 0
    pop r4                ; Restaurer r4 depuis la pile
    ret                    ; Retour à l'appelant
