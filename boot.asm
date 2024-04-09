BITS 16              ; Indica que é código de 16 bits
ORG 0x7C00           ; Indica o endereço de carga do bootloader

start:
    mov ah, 0x0E     ; Função teletype para interrupção de vídeo
    mov al, 'a'      ; Caractere inicial a imprimir
    mov bh, 0x00     ; Página de vídeo
    mov bl, 0x07     ; Atributos de cor (branco sobre preto)

loop:
    int 0x10         ; Chama a interrupção de vídeo para imprimir AL
    inc al           ; Incrementa AL para o próximo caractere
    cmp al, 'z' + 1  ; Compara se já passou de 'Z'
    jne loop         ; Se não, volta para o loop

hang:
    jmp hang         ; Loop infinito para manter o bootloader ativo

times 510-($-$$) db 0
dw 0xAA55           ; Assinatura do setor de boot

