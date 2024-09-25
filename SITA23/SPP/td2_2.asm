org 0
jmp debut

org 10 ; déclaration des constantes et variables
mult: CST 4
nombre1: CST 1
nombre2: CST 2
nombre3: CST 3
resultat1: VAR ?
resultat2: VAR ?
resultat3: VAR ?

org 20 ; déclaration de la pile
pile: VAR 5?
fond_pile: VAR ?

org 30 ; zone de code (S/P et PPAL)
SousP: 
    push r2
    push fl
bcle: 
    add r0, r1r0
    dec r2
    jnz bcle
    pop fl
    pop r2
    ret

debut: 
    ldr r0, fond_pile
    ldr sp, r0
    ldr r2, [mult]
    ldr r1, [nombre1]
    ldr r0, 0
    call SousP
    str [resultat1], r0

    ldr r0, 0
    ldr r1, [nombre2]
    call SousP
    str [resultat2], r0

    ldr r1, [nombre3]
    ldr r0, 0
    call SousP
    str [resultat3], r0