;Programme demo td1


val_debutequ 0
	org 0
	jmp debut
	
	org 8
taille: cst 30
tableau:var 10?

		org 20
debut: ldr r0,[taille]
	ldr r1,r0
	ldr r0,val_debut
	ldr r2,r0
	ldr r0,tableau
	ldr r4,r0
bcle: str [r4],r2
	inc r2
	inc r4
	dec r1
	jnz bcle
fin: hlt
