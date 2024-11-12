section .data
    led_pattern db 0b00000001 ; Initial LED pattern
    direction db 1            ; 1 for left, 0 for right
    delay_count dw 0          ; Counter for delay

section .bss
    ; Reserve space for variables if needed

section .text
    global _start

_start:
    ; Initial setup
    mov dx, 0x378         ; Parallel port address
    mov al, [led_pattern]
    out dx, al            ; Output initial LED pattern

main_loop:
    ; Check for manual interrupt (ITM) to change direction
    in al, dx
    test al, 0x01         ; Check if ITM is pressed
    jz no_itm             ; If not pressed, skip
    call change_direction ; Change direction if pressed

no_itm:
    ; Check for keyboard interrupt to stop the program
    in al, 0x60           ; Keyboard port address
    cmp al, 'S'
    je stop_program       ; Stop if 'S' is pressed

    ; Delay loop
    call delay

    ; Update LED pattern
    call update_leds

    jmp main_loop         ; Repeat the loop

change_direction:
    ; Toggle direction
    mov al, [direction]
    xor al, 1
    mov [direction], al
    ret

update_leds:
    ; Update LED pattern based on direction
    mov al, [led_pattern]
    mov bl, [direction]
    cmp bl, 1
    je rotate_left
    ror al, 1             ; Rotate right
    jmp update_done

rotate_left:
    rol al, 1             ; Rotate left

update_done:
    mov [led_pattern], al
    mov dx, 0x378
    out dx, al            ; Output updated LED pattern
    ret

delay:
    ; Simple delay loop
    mov cx, 0xFFFF
delay_loop:
    loop delay_loop
    ret

stop_program:
    ; Exit the program
    mov ax, 0x4C00
    int 0x21