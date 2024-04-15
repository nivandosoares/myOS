section .text
    [bits 32]
    [extern main]
    call main
    jmp $

; Assembly function to wait for a key press
wait_for_key_press:
    mov ah, 0x00  ; BIOS function to wait for a key press
    int 0x16      ; Call BIOS keyboard service
    ret
