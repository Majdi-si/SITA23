val_debut equ 0 ; Définition de la valeur de l'étiquette val_debut qui sert à stocker l'adresse de début du programme
    org 0
    jmp debut

    org 8
    nombre: var ?
    mult: cst 4
    resultat: var ?

    org 20

debut: ldr r0, 1
    str [0xFF3], r0
    ldr r1,[0xFF0] ; lire la valeur en entrée
    str [nombre], r1 ; stocker la valeur dans la mémoire
    ldr r0, 0
    ldr r1, [nombre] ; charger la valeur de nombre dans r1
    ldr r2, [mult]
boucle: add r0, r1r0 
        ; r2 <-- r2 - 1
        dec r2
        ; Si r2 != 0, sauter à boucle
        jnz boucle
    ; Stocker le résultat dans la mémoire
    str [resultat], r0
    
    ldr r0, [resultat]
    str [0xFF2], r0 
    jmp debut
fin: hlt