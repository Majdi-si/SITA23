;td 3-2 affichage message avec test mot d'état

SModeEtat EQU 0xFF5 ; mot d'état

SRxTx EQU 0xFF4 ; registre de communication

org 0 ; première instruction

jmp init

org 10 ; zone de données

message: CST 'SIMCAL IENAC-'
taille: CST 14


org 30 ; votre programme

init: ldr r0, 2
    str [SModeEtat], r0
    ldr r0, message
    ldr r4, r0
    ldr r3, [taille]
    ldr r2, r0

debut: ldr r0, [SModeEtat]
    ldr r1,r0
    ldr r0, 2
    and r0, r1r0
    jz debut

affichage: ldr r0, [r4]
    str [SRxTx], r0 ; affichage du caractère
    inc r4
    dec r3
    jnz debut
    jmp init







