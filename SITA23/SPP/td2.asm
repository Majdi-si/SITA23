val_debut equ 0 ; Définition de la valeur de l'étiquette val_debut qui sert à stocker l'adresse de début du programme
    org 0
    jmp debut

    org 8
    nombre: cst 3
    mult: cst 4
    resultat: var 1?

    org 20

debut: ldr r0, 0
    ldr r1, [nombre]
    ldr r2, [mult]
boucle: add r0, r1r0
        ; r2 <-- r2 - 1
        dec r2
        ; Si r2 != 0, sauter à boucle
        jnz boucle
    ; Stocker le résultat dans la mémoire
    str [resultat], r0
    ; Terminer le programme
fin: hlt

    ;ecrire un programme qui effectue la multiplication d'une constante "nombre" (fixée à 3) par une constante "mult" (fixée à 4) puis range le résultat dans une variable "résultat"