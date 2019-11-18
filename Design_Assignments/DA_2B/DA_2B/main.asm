
; AssemblerApplication1.asm
; Created: 10/5/2019 6:21:20 PM
; Author : Worku Tafara
;

.org 0
jmp START
.org 0x02
jmp TARGET

START:
ldi R20, HIGH(RAMEND)
out SPH, R20
ldi R20, LOW(RAMEND)
out SPL, R20
ldi R20, 2
sts EICRA, R20
sbi DDRB, 3
sbi PORTB, 3
sbi PORTD, 2
cbi DDRC, 3
sbi PORTC, 3
ldi R20, 1<<INT0
out EIMSK, R20
sei

here:
jmp	here

TARGET:
in	R21, PORTB
ldi R22, (1<<3)
eor R21, R22
out	PORTB, R21

; Delay 6 000 000 cycles
; 375ms at 16.0 MHz

    ldi  R18, 31
    ldi  R19, 113
    ldi  R20, 31

L1: 
	dec  R20
    brne L1
    dec  R19
    brne L1
    dec  R18
    brne L1
    nop