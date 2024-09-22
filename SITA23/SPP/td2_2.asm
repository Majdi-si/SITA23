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

    org 20

debut: ldr r1, [nombre1] ; multiplication de nombre1 par mult
    ldr r2, [mult]
    call multiplication
    str [resultat1], r0

    ldr r1, [nombre2] ; multiplication de nombre2 par mult
    ldr r2, [mult]
    call multiplication
    str [resultat2], r0

    ldr r1, [nombre3] ;
    ldr r2, [mult]
    call multiplication
    str [resultat3], r0 

multiplication: push r4
    ldr r0, 0     
boucle: add r0, r1r0 
    dec r2  
        jnz boucle   
    pop r4  
    ret
