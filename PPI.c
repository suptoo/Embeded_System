DATA SEGMENT
    PORTA EQU 00H
    PORTB EQU 02H
    PORTC EQU 04H
    PORT_CON EQU 06H
DATA ENDS

CODE SEGMENT
    MOV AX, DATA
    MOV DS, AX

    ORG 0000H

START:
    MOV DX, PORT_CON
    MOV AL, 10000000B
    OUT DX, AL

blinkloop:
    MOV AL, 00000001B
    MOV DX, PORTA
    OUT DX, AL

    MOV CX, 0F424H
loopy1:loop loopy1

    MOV AL, 00000000B
    MOV DX, PORTA
    OUT DX, AL

    MOV CX, 0F424H ; Delay
loopy2:loop loopy2

    JMP blinkloop

CODE ENDS
END
